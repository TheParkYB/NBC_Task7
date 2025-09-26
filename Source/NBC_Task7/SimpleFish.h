#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "SimpleFish.generated.h"

UCLASS()
class NBC_TASK7_API ASimpleFish : public APawn
{
	GENERATED_BODY()

public:
	ASimpleFish();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//이동
	void PlayerMove(const struct FInputActionValue& value);

	//마우스 이동
	void PlayerMouseMove(const FInputActionValue& value);

private:
	//이동 입력
	UPROPERTY(EditAnywhere, Category = "Input Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> moveAction;

	//마우스 이동 입력
	UPROPERTY(EditAnywhere, Category = "Input Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> lookAction;

	//이동 속도
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float moveSpeed;
	
	//회전 속도
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float lookSpeed;
	
	//루트가 될 캡슐 컴포넌트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBoxComponent* rootBox;
	
	//이 폰이 사용할 스켈레탈 메시
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* skeletalMesh;

	//카메라용 스프링 암
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	USpringArmComponent* springArm;

	//카메라
	UPROPERTY(editAnywhere, meta = (AllowPrivateAccess = true))
	UCameraComponent* camera;

	//매 Tick마다 기록된 DeltaTime;
	float deltaTime;
};
