// Fill out your copyright notice in the Description page of Project Settings.

#include "IW1.h"
#include "Player/HUD/Slate/SGameUIWidget.h"
#include "Player/HUD/Slate/SMenuUIWidget.h"
#include "IWGameMode.h"
#include "IWSaveGame.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "IWHUD.h"

void AIWHUD::BeginPlay()
{
	Super::BeginPlay();


	if (HealthBarMaterialBrush.GetResourceObject()->IsA(UMaterialInterface::StaticClass()))
	{
		UMaterialInterface* HealthBarMaterialInterface = Cast<UMaterialInterface>(HealthBarMaterialBrush.GetResourceObject());
		HealthBarMaterialD = UMaterialInstanceDynamic::Create(HealthBarMaterialInterface, this);
		HealthBarMaterialBrush.SetResourceObject(HealthBarMaterialD);

		HealthBarMaterialD->SetScalarParameterValue("LifeRatio", 100 / 100-0.001);
	}

	CreateGameUI();

	UIWSaveGame* ScoreSave = Cast<UIWSaveGame>(UGameplayStatics::CreateSaveGameObject(UIWSaveGame::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist(TEXT("ScoreSaveSlot"), 0))
	{
		ScoreSave = Cast<UIWSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("ScoreSaveSlot"), 0));
		HighestScore = ScoreSave->HighestScore;
	}
	else
	{
		HighestScore = 0;
	}

	GameScore = 0;	

	bDisplayStartText = true;

	FTimerHandle HideStartTextHandle;
	GetWorld()->GetTimerManager().SetTimer(HideStartTextHandle, this, &AIWHUD::HideStartText, 4.5, false);
}

void AIWHUD::DrawHUD()
{
	Super::DrawHUD();

	if (GetWorld()->GetAuthGameMode() && GetWorld()->GetAuthGameMode()->IsA(AIWGameMode::StaticClass()))
	{
		AIWGameMode* GameMode = Cast<AIWGameMode>(GetWorld()->GetAuthGameMode());
		GameScore = GameMode->GameScore;
	}

	if (bDisplayStartText == true)
	{
		FCanvasTextItem NewText1(
			FVector2D(20, 50),
			FText::FromString("Press [P] to pause game"),
			UE4Font,
			FColor(50, 100, 255)
			);
		
		Canvas->DrawItem(NewText1);

		FCanvasTextItem NewText2(
			FVector2D(10, 70),
			FText::FromString("Press ArrowKeys [->] and [<-] to strafe"),
			UE4Font,
			FColor::Cyan
			);

		Canvas->DrawItem(NewText2);

		FCanvasTextItem NewText3(
			FVector2D(10, 90),
			FText::FromString("Press [SpaceBar] and [MouseClick] to Fire"),
			UE4Font,
			FColor::Cyan
			);

		Canvas->DrawItem(NewText3);
	}
}

void AIWHUD::HideStartText()
{
	bDisplayStartText = false;
}

void AIWHUD::CreateGameUI()
{
	if (GEngine && GEngine->GameViewport)
	{
		Viewport = GEngine->GameViewport;

		SAssignNew(GameUI, SGameUIWidget)
		.HUDPtr(this);

		Viewport->AddViewportWidgetContent(
		SNew(SWeakWidget)
		.PossiblyNullContent(GameUI.ToSharedRef()));
	}
}

void AIWHUD::OpenMenu(EMenuOpenType MenuOpenType)
{
	if (bIsMenuOpen == false)
	{
			GameUI.Get()->GameUIOverlay.Get()->AddSlot()// Creating the quick slots
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.Padding(FMargin(0,0,0,140))
			[
				SAssignNew(MenuWidget, SMenuUIWidget)
				.HUDPtr(this)
				.MenuType(MenuOpenType)
			];
		bIsMenuOpen = true;
	}
}

void AIWHUD::CloseMenu()
{
	if (bIsMenuOpen == true)
	{
		GameUI.Get()->GameUIOverlay.Get()->RemoveSlot(MenuWidget.ToSharedRef());
		bIsMenuOpen = false;
	}
}

void AIWHUD::RestartGameClicked()
{
	GetWorld()->GetFirstPlayerController()->RestartLevel();
}

void AIWHUD::ExitGameClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}