// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HudEnums.generated.h"

UENUM(BlueprintType)
enum class EHudState : uint8
{
	E_NONE			UMETA(DisplayName = "None"),
	E_MAIN			UMETA(DisplayName = "MainHud"),
	E_INVENTORY	UMETA(DisplayName = "Inventory"),

	E_MAX
};