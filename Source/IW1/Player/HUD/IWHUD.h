// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "IWHUD.generated.h"

UENUM(BlueprintType)
enum class EMenuOpenType : uint8
{
	Won UMETA(DisplayName = "Right"),
	Lost UMETA(DisplayName = "Left"),
	None UMETA(DisplayName = "None")
};


UCLASS()
class IW1_API AIWHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void DrawHUD() override;

	void CreateGameUI();

	int32 GameScore;

	int32 HighestScore;

	/** Store the view port where the slate widgets are drawn */
	UPROPERTY()
	UGameViewportClient* Viewport;

	/** Border for the scoreboard */
	UPROPERTY(EditAnywhere, Category = UI)
	FSlateBrush ScoreBorder;

	/** Border for the scoreboard */
	UPROPERTY(EditAnywhere, Category = UI)
	FSlateBrush HighestScoreBorder;

	/** Border for the scoreboard */
	UPROPERTY(EditAnywhere, Category = UI)
	FSlateBrush RoundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Font)
	FSlateFontInfo ScoreFont;

	UPROPERTY(EditAnywhere, Category = UI)
	UMaterial *HealthBarMaterial;

	UPROPERTY(EditAnywhere, Category = UI)
	UMaterialInstanceDynamic* HealthBarMaterialD;

	/** Border for the scoreboard */
	UPROPERTY(EditAnywhere, Category = UI)
	FSlateBrush HealthBarMaterialBrush;

	/** Border for the scoreboard */
	UPROPERTY(EditAnywhere, Category = UI)
	FSlateBrush WinningMenuFrame;

	/** Border for the scoreboard */
	UPROPERTY(EditAnywhere, Category = UI)
	FSlateBrush LosingMenuFrame;

	/** Border for the scoreboard */
	UPROPERTY(EditAnywhere, Category = UI)
	FSlateBrush NoneMenuFrame;

	UPROPERTY(EditAnywhere, Category = UI)
	FButtonStyle RestartButtonStyle;

	UPROPERTY(EditAnywhere, Category = UI)
	FButtonStyle ExitButtonStyle;

	void OpenMenu(EMenuOpenType MenuOpenType = EMenuOpenType::None);

	void CloseMenu();

	bool bIsMenuOpen = false;

	void RestartGameClicked();

	void ExitGameClicked();

	bool bDisplayStartText = true;

	void HideStartText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Font)
	FSlateFontInfo UE4Font;


private:

	/** pointer storing the game slate UI */
	TSharedPtr<class SGameUIWidget> GameUI;

	/** pointer storing the game slate UI */
	TSharedPtr<class SMenuUIWidget> MenuWidget;


};
