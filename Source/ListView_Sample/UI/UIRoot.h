// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Input/Reply.h"
#include "ListView_Sample/ListView_Sample.h"
#include "Blueprint/UserWidget.h"
#include "UIRoot.generated.h"

/**
 * 
 */
UCLASS()
class LISTVIEW_SAMPLE_API UUIRoot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:

	class APlayerController* PlayerController;

	UUIRoot* ParentWidget = nullptr;
	UUIRoot* ReturnWidget = nullptr;

	FVector2D MousePos;

	bool bIsParentVisible = false;
	bool bIsParentDestroy = false;

	bool bIsKeyDown = false;

protected:
	
	void Enter();

	UFUNCTION(BlueprintPure)
		FString GetInputKeyToAction(FKey Key) const;


	UFUNCTION(BlueprintNativeEvent)
		void OnPressKey(FName KeyName, FKey Key);	
	UFUNCTION(BlueprintNativeEvent)
		void OnReleaseKey(FName KeyName, FKey Key);
	UFUNCTION(BlueprintNativeEvent)
		void OnMouseMoveUpdate(FVector2D Pos);
	UFUNCTION(BlueprintNativeEvent)
		void OnMouseMoveDetect(FVector2D Pos);

	UFUNCTION(BlueprintCallable)
		bool ExecutePressKey(FKey KeyAction, FKey Key);
	UFUNCTION(BlueprintCallable)
		bool ExecuteReleaseKey(FKey KeyAction, FKey Key);


public:
	UFUNCTION(BlueprintCallable)
		UWidget* GoToWidget(TSubclassOf<UUIRoot> NewWidgetClass, bool bParentVisible = false, bool bParentDestroy = false, int32 ZOrder = 0);

	UFUNCTION(BlueprintCallable)
		virtual void ReturnToParent();

	UWidget* ExecuteBuiltWidget(class UUIRoot* NewWidget, bool bVisible = false, bool bDestroy = false, int32 ZOrder = 0);
};
