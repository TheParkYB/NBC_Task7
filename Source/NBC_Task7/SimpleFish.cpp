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
}

void ASimpleFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
}

// Called to bind functionality to input
void ASimpleFish::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//플레이어의 입력에 따라 적절한 함수에 대응한다.
	if (TObjectPtr<UEnhancedInputComponent> enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//이동
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ASimpleFish::PlayerMove);
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
	AddMovementInput(GetActorRightVector(), moveValue.X * deltaSpeed);

	//앞뒤 이동
	AddMovementInput(GetActorForwardVector(), moveValue.Y * deltaSpeed);
}

void ASimpleFish::PlayerMouseMove(const FInputActionValue& value)
{	
	//입력된 값을 Vector2D로 변경
	const FVector2D moveValue = value.Get<FVector2D>();

	//회전 속도 * 델타 타임
	float deltaSpeed = lookSpeed * deltaTime;

	//마우스 횡 이동
	AddControllerYawInput(moveValue.X * deltaSpeed);

	//마우스 종 이동 (마우스가 위로 이동하면 시점이 위로가야함)
	AddControllerPitchInput(moveValue.Y * deltaSpeed);
}

