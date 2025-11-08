// Fill out your copyright notice in the Description page of Project Settings.


#include "Zelcar/Public/Characters/Trainer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/HealthComponent.h"
#include "Components/StaminaComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/GameHUD.h"
#include "HUD/TrainerWidget.h"

// Sets default values
ATrainer::ATrainer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		MovementComponent->MaxWalkSpeed = WalkSpeed;
	}

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(FName("CameraArm"));
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(CameraArm);
	Camera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(FName("StaminaComponent"));
	
	AutoPossessPlayer = EAutoReceiveInput::Type::Player0;
}

// Called when the game starts or when spawned
void ATrainer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (TrainerMappingContext)
			{
				InputSubsystem->AddMappingContext(TrainerMappingContext, 0);
			}
		}
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		AGameHUD* GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());
		if (GameHUD)
		{
			TrainerWidget = GameHUD->GetTrainerWidget();
			if (TrainerWidget && HealthComponent)
			{
				TrainerWidget->SetHealthBar(HealthComponent->GetHealthPercentage());
				TrainerWidget->SetStaminaBar(StaminaComponent->GetStaminaPercentage());
			}
		}
	}
}

void ATrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsRunning)
	{
		StaminaComponent->LoseStamina(DeltaTime);
		if (StaminaComponent->GetStaminaPercentage() == 0.f)
		{
			RunEnd();
		}
	}
	else
	{
		StaminaComponent->RegenStamina(DeltaTime);
	}
	TrainerWidget->SetStaminaBar(StaminaComponent->GetStaminaPercentage());
}

void ATrainer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATrainer::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATrainer::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATrainer::Jump);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ATrainer::RunStart);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ATrainer::RunEnd);
	}
}

void ATrainer::Move(const FInputActionValue& Value)
{
	FVector2D MoveAxis = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Forward, MoveAxis.Y);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Right, MoveAxis.X);
}

void ATrainer::Look(const FInputActionValue& Value)
{
	FVector2D MouseAxis = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerPitchInput(MouseAxis.Y);
		AddControllerYawInput(MouseAxis.X);
	}
}

void ATrainer::RunStart()
{
	if (!CanRun()) return;
	
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = RunSpeed;
		IsRunning = true;
	}
}

void ATrainer::RunEnd()
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = WalkSpeed;
		IsRunning = false;
	}
}

bool ATrainer::CanRun()
{
	return StaminaComponent->GetStaminaPercentage() > MinStaminaForRunPercent;
}
