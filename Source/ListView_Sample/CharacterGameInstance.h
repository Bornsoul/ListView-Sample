// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/HudEnums.h"

#include "ListView_Sample.h"
#include "Engine/GameInstance.h"
#include "CharacterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LISTVIEW_SAMPLE_API UCharacterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCharacterGameInstance();

	UFUNCTION(BlueprintPure)
		class AListView_SampleCharacter* GetLocalCharacter() const;
	void SetLocalCharacter(class AListView_SampleCharacter* CharacterTarget);

	UFUNCTION(BlueprintPure)
		class APlayerController* GetLocalController() const;
	void SetLocalController(class APlayerController* ControllerTarget);

public:
	TWeakObjectPtr<class AListView_SampleCharacter> LocalCharacter;
	TWeakObjectPtr<class APlayerController> LocalController;

private:
	EHudState CurrentHudState = EHudState::E_NONE;

public:
	UFUNCTION(BlueprintCallable)
		void ChangeHudState(EHudState NewTarget);
	UFUNCTION(BlueprintCallable)
		void ReadHudState(EHudState& OutHudState) const;
	UFUNCTION(BlueprintPure)
		EHudState IsHudState() const;

};
