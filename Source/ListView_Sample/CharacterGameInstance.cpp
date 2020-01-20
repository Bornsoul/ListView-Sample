// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterGameInstance.h"
#include "ListView_SampleCharacter.h"

UCharacterGameInstance::UCharacterGameInstance()
{
	
}

class AListView_SampleCharacter* UCharacterGameInstance::GetLocalCharacter() const
{
	if (LocalCharacter.IsValid())
		return LocalCharacter.Get();

	return nullptr;
}

void UCharacterGameInstance::SetLocalCharacter(class AListView_SampleCharacter* CharacterTarget)
{
	if (CharacterTarget == nullptr)
	{
		UDIALOG(TEXT(""));
		return;
	}

	LocalCharacter = CharacterTarget;
}

class APlayerController* UCharacterGameInstance::GetLocalController() const
{
	if ( LocalController.IsValid())
		return LocalController.Get();

	return nullptr;
}

void UCharacterGameInstance::SetLocalController(class APlayerController* ControllerTarget)
{
	if (ControllerTarget == nullptr)
	{
		UDIALOG(TEXT(""));
		return;
	}

	LocalController = ControllerTarget;
}

void UCharacterGameInstance::ChangeHudState(EHudState NewTarget)
{
	CurrentHudState = NewTarget;
}

void UCharacterGameInstance::ReadHudState(EHudState& OutHudState) const
{
	OutHudState = CurrentHudState;
}

EHudState UCharacterGameInstance::IsHudState() const
{
	return CurrentHudState;
}
