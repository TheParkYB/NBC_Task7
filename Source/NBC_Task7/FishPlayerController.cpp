#include "FishPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

void AFishPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//블루프린트를 통해 동록한 InputMappingContext를 적용
	if (UEnhancedInputLocalPlayerSubsystem *subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (!playerMappingContext.IsNull())
		{
			UInputMappingContext *mappingContext = playerMappingContext.LoadSynchronous();
			subsystem->AddMappingContext(mappingContext,0);
		}
	}
}