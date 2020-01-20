// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "InventoryStruct.generated.h"

USTRUCT(BlueprintType)
struct FInventoryTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		FText ItemText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UTexture2D* ItemIcon;

};