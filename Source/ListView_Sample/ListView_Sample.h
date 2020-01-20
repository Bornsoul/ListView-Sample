// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Engine/GameEngine.h"

DECLARE_LOG_CATEGORY_EXTERN(PHLog, Log, All);

#define ULOG_INFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ULOG_WARNING() UE_LOG(PHLog, Warning, TEXT("%s"), *ULOG_INFO)
#define ULOG(Format, ...) UE_LOG(PHLog, Warning, TEXT("%s %s"), *ULOG_INFO, *FString::Printf(Format, ##__VA_ARGS__))

#define UDIALOG(Format, ...) FPlatformMisc::MessageBoxExt(EAppMsgType::Ok, *FString::Printf(TEXT("%s\n\n%s"), *FString::Printf(Format, ##__VA_ARGS__), *ULOG_INFO), *ULOG_INFO)