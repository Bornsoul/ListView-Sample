// Fill out your copyright notice in the Description page of Project Settings.


#include "UIRoot.h"
#include "GameFramework/InputSettings.h"

void UUIRoot::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUIRoot::NativeConstruct()
{
	Super::NativeConstruct();

	if (ParentWidget != nullptr)
	{
		/*if (bParentVisible)
		{
			ParentWidget->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (bParentDestroy)
		{
			ParentWidget->Destruct();
			ParentWidget = nullptr;			
		}*/
	}
	
	if (ReturnWidget != nullptr)
	{

		ReturnWidget = nullptr;
	}

	bIsFocusable = true;
	if (PlayerController == nullptr)
	{
		PlayerController = Cast<APlayerController>(GetOwningPlayer());		
	}

	Enter();
}

void UUIRoot::Enter()
{
	if (PlayerController != nullptr)
	{
		SetUserFocus(PlayerController);
		SetKeyboardFocus();
	}

	if (ReturnWidget != nullptr)
	{
		if (!ReturnWidget->bIsParentVisible)
			ReturnWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		ReturnWidget = nullptr;
	}
}

void UUIRoot::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUIRoot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

//FReply UUIRoot::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
//{
//	Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
//	return FReply::Handled();
//}

FReply UUIRoot::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (!bIsKeyDown)
	{
		FKey NewKey = InKeyEvent.GetKey();
		ExecutePressKey(NewKey, NewKey);

		bIsKeyDown = true;
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UUIRoot::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyUp(InGeometry, InKeyEvent);

	FKey NewKey = InKeyEvent.GetKey();
	ExecuteReleaseKey(NewKey, NewKey);
	bIsKeyDown = false;

	return FReply::Handled();
}

FReply UUIRoot::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	FVector2D Pos = InMouseEvent.GetCursorDelta();
	OnMouseMoveUpdate(Pos);

	if (MousePos != Pos)
	{
		MousePos = Pos;
		OnMouseMoveDetect(MousePos);
		FReply::Handled();
	}

	return FReply::Unhandled();
}

void UUIRoot::OnMouseMoveUpdate_Implementation(FVector2D Pos)
{
	
}

void UUIRoot::OnMouseMoveDetect_Implementation(FVector2D Pos)
{

}

bool UUIRoot::ExecutePressKey(FKey KeyAction, FKey Key)
{
	FString KeyName = GetInputKeyToAction(KeyAction);
	if (KeyName.IsEmpty())
	{
		OnPressKey(NAME_None, Key);
		return false;
	}

	OnPressKey(FName(*KeyName), Key);
	return true;
}

bool UUIRoot::ExecuteReleaseKey(FKey KeyAction, FKey Key)
{
	FString KeyName = GetInputKeyToAction(KeyAction);
	if (KeyName.IsEmpty())
	{
		OnReleaseKey(NAME_None, Key);
		return false;
	}

	OnReleaseKey(FName(*KeyName), Key);
	return true;
}

UWidget* UUIRoot::GoToWidget(TSubclassOf<UUIRoot> NewWidgetClass, bool bParentVisible /*= false*/, bool bParentDestroy /*= false*/, int32 ZOrder /*= 0*/)
{
	if (NewWidgetClass == nullptr)
	{
		UDIALOG(TEXT("Empty"));
		return nullptr;
	}

	APlayerController* Con = Cast<APlayerController>(PlayerController);
	UUIRoot* NewWidget = CreateWidget<UUIRoot>(Con, NewWidgetClass);

	return ExecuteBuiltWidget(NewWidget, bParentVisible, bParentDestroy, ZOrder);
}

void UUIRoot::ReturnToParent()
{
	if (ParentWidget == nullptr)
	{
		RemoveFromParent();
		return;
	}

	/*if (!ParentWidget->bParentVisible)
	{
		ParentWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}*/

	ParentWidget->ReturnWidget = this;
	ParentWidget->Enter();

	RemoveFromParent();
	Destruct();
}

UWidget* UUIRoot::ExecuteBuiltWidget(class UUIRoot* NewWidget, bool bVisible /*= false*/, bool bDestroy /*= false*/, int32 ZOrder)
{
	if (NewWidget == nullptr)
	{
		return nullptr;
	}

	APlayerController* Con = Cast<APlayerController>(PlayerController);
	if (Con == nullptr)
		return nullptr;


	if (bVisible)
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}

	if (bDestroy)
	{
		RemoveFromParent();
		Destruct();
	}
	else
	{
		NewWidget->ParentWidget = this;
	}

	NewWidget->AddToViewport(ZOrder);
	NewWidget->SetUserFocus(Con);
	NewWidget->SetKeyboardFocus();

	return NewWidget;
}

FString UUIRoot::GetInputKeyToAction(FKey Key) const
{
	const UInputSettings* KeySetting = GetDefault<UInputSettings>();
	if (KeySetting == nullptr)
		return TEXT("");

	FName ResultAction = NAME_None;

	for (const FInputActionKeyMapping& ActionMapping : KeySetting->GetActionMappings())
	{
		FString KeyName = ActionMapping.ActionName.ToString();
		if (KeyName.Left(3) == TEXT("UI_"))
		{
			if (ActionMapping.Key == Key)
			{
				ResultAction = ActionMapping.ActionName;
				break;
			}
		}
	}
	if (ResultAction == NAME_None)
	{
		for (const FInputAxisKeyMapping& AxisMapping : KeySetting->GetAxisMappings())
		{
			FString KeyName = AxisMapping.AxisName.ToString();
			if (KeyName.Left(3) == TEXT("UI_"))
			{
				if (AxisMapping.Key == Key)
				{

					ResultAction = AxisMapping.AxisName;
					break;
				}
			}
		}
	}

	return ResultAction.ToString();
}

void UUIRoot::OnPressKey_Implementation(FName KeyName, FKey Key)
{

}

void UUIRoot::OnReleaseKey_Implementation(FName KeyName, FKey Key)
{

}