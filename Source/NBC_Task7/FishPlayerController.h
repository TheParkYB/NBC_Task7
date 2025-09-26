#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FishPlayerController.generated.h"

UCLASS()
class NBC_TASK7_API AFishPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	//플레이어 입력에 대한 InputMappingContext
	UPROPERTY(EditAnywhere, Category = "Input Action", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<class UInputMappingContext> playerMappingContext;
};
