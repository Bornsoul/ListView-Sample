// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ListView_SampleCharacter.h"
#include "CharacterGameInstance.h"
#include "Misc/MessageDialog.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AListView_SampleCharacter

AListView_SampleCharacter::AListView_SampleCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AListView_SampleCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameInst = GetGameInstance<UCharacterGameInstance>();
	if (GameInst != nullptr)
	{
		GameInst->SetLocalCharacter(this);
		GameInst->SetLocalController(GetController<APlayerController>());
		GameInst->ChangeHudState(EHudState::E_MAIN);
	}

}

void AListView_SampleCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);	
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AListView_SampleCharacter::InventoryAction);

	PlayerInputComponent->BindAxis("MoveForward", this, &AListView_SampleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AListView_SampleCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AListView_SampleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AListView_SampleCharacter::LookUpAtRate);


}

void AListView_SampleCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AListView_SampleCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AListView_SampleCharacter::InventoryAction()
{
	if (GameInst == nullptr && GameInst->GetLocalController() == nullptr)
	{
		return;
	}

	EHudState NewState;
	GameInst->ReadHudState(NewState);

	if (NewState == EHudState::E_MAIN)
	{
		GameInst->ChangeHudState(EHudState::E_INVENTORY);
		GameInst->GetLocalController()->bShowMouseCursor = true;
		
	}
	else if ( NewState == EHudState::E_INVENTORY)
	{
		GameInst->ChangeHudState(EHudState::E_MAIN);
		GameInst->GetLocalController()->bShowMouseCursor = false;
	}
}

void AListView_SampleCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AListView_SampleCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
