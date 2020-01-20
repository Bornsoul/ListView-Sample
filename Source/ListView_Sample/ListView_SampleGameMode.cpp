// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ListView_SampleGameMode.h"
#include "ListView_SampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AListView_SampleGameMode::AListView_SampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FObjectFinder<UClass> Const_MainHud(TEXT("/Game/Blueprints/UI/GameHUD.GameHUD_C"));
	if (Const_MainHud.Succeeded())
	{
		HUDClass = Const_MainHud.Object;
	}
}
