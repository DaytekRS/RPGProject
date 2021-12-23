#include "RPGGameModeBase.h"

#include "Player/RPGBaseCharacter.h"
#include "Player/RPGPlayerController.h"
#include "UI/RPGGameHUD.h"

ARPGGameModeBase::ARPGGameModeBase()
{
	DefaultPawnClass = ARPGBaseCharacter::StaticClass();
	PlayerControllerClass = ARPGPlayerController::StaticClass();
	HUDClass = ARPGGameHUD::StaticClass();
}
