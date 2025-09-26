#include "SimpleFish.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

ASimpleFish::ASimpleFish()
{
	PrimaryActorTick.bCanEverTick = true;

	//컴포넌트 세팅
	//루트가 될 박스 컴포넌트
	rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root Capsule"));
	rootBox->SetSimulatePhysics(false);
	RootComponent = rootBox;
	//스켈레탈 메시
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	skeletalMesh->SetSimulatePhysics(false);
	skeletalMesh->SetupAttachment(rootBox);
	//스프링 암
	springArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	springArm->SetupAttachment(rootBox);
	//카메라
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(springArm);
}

void ASimpleFish::BeginPlay()
{
	Super::BeginPlay();
	startZ = GetActorLocation().Z;
	innerRotationVector = FVector::ZeroVector;
}

void ASimpleFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//델타 타임 기록
	deltaTime = DeltaTime;

	//Z높이는 시작 위치보다 밑으로 허용하지 않는다.
	FVector currentPos = GetActorLocation();
	if (currentPos.Z < startZ)
	{
		currentPos.Z = startZ;
		SetActorLocation(currentPos);
	}
}

// Called to bind functionality to input
void ASimpleFish::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//플레이어의 입력에 따라 적절한 함수에 대응한다.
	if (TObjectPtr<UEnhancedInputComponent> enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//수평 이동
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ASimpleFish::PlayerMove);
		//수직 이동
		enhancedInputComponent->BindAction(upAndDownAction, ETriggerEvent::Triggered, this, &ASimpleFish::PlayerVerticalMove);
		//기울이기
		enhancedInputComponent->BindAction(rollingAction, ETriggerEvent::Triggered, this, &ASimpleFish::PlayerRolling);
		//마우스 이동
		enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &ASimpleFish::PlayerMouseMove);
	}
}

void ASimpleFish::PlayerMove(const struct FInputActionValue& value)
{	
	//입력된 값을 Vector2D로 변경
	const FVector2D moveValue = value.Get<FVector2D>();

	//이동 속도 * 델타 타임
	float deltaSpeed = moveSpeed * deltaTime;
	
	//좌우 이동
	AddActorLocalOffset(FVector::RightVector * moveValue.X * deltaSpeed);

	//앞뒤 이동
	AddActorLocalOffset(FVector::ForwardVector * moveValue.Y * deltaSpeed);
}

void ASimpleFish::PlayerVerticalMove(const struct FInputActionValue& value)
{
	//입력된 값을 float로 변경하고 델타 타임과 곱하기
	const float deltaSpeed = value.Get<float>() * moveSpeed * deltaTime;
	//수직 이동
	AddActorLocalOffset(FVector::UpVector * deltaSpeed);
}

void ASimpleFish::PlayerRolling(const struct FInputActionValue& value)
{
	//입력된 값을 float로 변경하고 델타 타임과 곱하기
	const float deltaSpeed = value.Get<float>() * rollingSpeed * deltaTime;
	
	//각도 제한
	innerRotationVector += FVector(0, 0, deltaSpeed);
	innerRotationVector.Z = FMath::Clamp(innerRotationVector.Z, MIN_ANGLE, MAX_ANGLE);
	//기울이기
	SetActorRelativeRotation(FRotator(innerRotationVector.X, innerRotationVector.Y, innerRotationVector.Z));
}

void ASimpleFish::PlayerMouseMove(const FInputActionValue& value)
{	
	//입력된 값을 Vector2D로 변경
	const FVector2D moveValue = value.Get<FVector2D>();

	//회전 속도 * 델타 타임
	float deltaSpeed = lookSpeed * deltaTime;

	//회전 방향 (수직 각도 제한)
	innerRotationVector += FVector(moveValue.Y * deltaSpeed, moveValue.X * deltaSpeed, 0);
	innerRotationVector.X = FMath::Clamp(innerRotationVector.X, MIN_ANGLE, MAX_ANGLE);

	//마우스 이동을 따른다.
	SetActorRelativeRotation(FRotator(innerRotationVector.X, innerRotationVector.Y, innerRotationVector.Z));
}

