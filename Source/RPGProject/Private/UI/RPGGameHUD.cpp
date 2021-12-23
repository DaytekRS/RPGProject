// Training project created by Daytek


#include "UI/RPGGameHUD.h"

#include "Blueprint/UserWidget.h"

void ARPGGameHUD::BeginPlay()
{
	Super::BeginPlay();
	const auto PlayerWidget = CreateWidget(GetWorld(), PlayerWidgetClass);
	PlayerWidget->AddToViewport();
}
