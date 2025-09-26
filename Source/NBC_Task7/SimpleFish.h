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

	//수평 이동
	void PlayerMove(const struct FInputActionValue& value);

	//수직 이동
	void PlayerVerticalMove(const struct FInputActionValue& value);

	//기울이기
	void PlayerRolling(const struct FInputActionValue& value);

	//마우스 이동
	void PlayerMouseMove(const FInputActionValue& value);

private:
	//수평 이동 입력
	UPROPERTY(EditAnywhere, Category = "Input Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> moveAction;

	//수직 이동 입력
	UPROPERTY(EditAnywhere, Category = "Input Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UInputAction> upAndDownAction;
	
	//마우스 이동 입력
	UPROPERTY(EditAnywhere, Category = "Input Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> lookAction;

	//기울기 입력
	UPROPERTY(EditAnywhere, Category = "Input Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> rollingAction;

	//이동 속도
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float moveSpeed;
	
	//회전 속도
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float lookSpeed;

	//구르기 속도
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float rollingSpeed;
	
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

	//시작 높이
	float startZ;
	
	//매 Tick마다 기록된 DeltaTime;
	float deltaTime;
};