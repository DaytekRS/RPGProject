#include "RPGGameModeBase.h"

#include "Player/RPGBaseCharacter.h"
#include "Player/RPGPlayerController.h"

ARPGGameModeBase::ARPGGameModeBase()
{
	DefaultPawnClass = ARPGBaseCharacter::StaticClass();
	PlayerControllerClass = ARPGPlayerController::StaticClass();
}
