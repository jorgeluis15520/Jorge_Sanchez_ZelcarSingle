// Fill out your copyright notice in the Description page of Project Settings.


#include "Zelcar/Public/Characters/Trainer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/HealthComponent.h"
#include "Components/PetInventoyComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaminaComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/GameHUD.h"
#include "HUD/TrainerWidget.h"
#include "PetInventory/PetInventoryWidget.h"
#include "Pets/AllyPet.h"
#include "Pets/EnemyPet.h"

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

	PetSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("PetSpawnPoint"));
	PetSpawnPoint->SetupAttachment(GetRootComponent());
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(FName("StaminaComponent"));

	PetInventoryComponent = CreateDefaultSubobject<UPetInventoyComponent>(FName("PetInventoryComponent"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());
	
	AutoPossessPlayer = EAutoReceiveInput::Type::Player0;
}

// Called when the game starts or when spawned
void ATrainer::BeginPlay()
{
	Super::BeginPlay();

	InitializeInputSubsystem();
	InitializeHUD();
	InitializeInventory();
	SpawnAllyPet(DefaultPet);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrainer::OnSphereOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATrainer::OnSphereEndOverlap);
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
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Completed, this, &ATrainer::TogglePetInventory);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &ATrainer::Attack);
		EnhancedInputComponent->BindAction(CaptureAction, ETriggerEvent::Completed, this, &ATrainer::Capture);
		EnhancedInputComponent->BindAction(CloseInventoryAction, ETriggerEvent::Completed, this, &ATrainer::TogglePetInventory);
	}
}

void ATrainer::Move(const FInputActionValue& Value)
{
	if (bIsInventoryOpen) return;
	
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
	if (bIsInventoryOpen) return;
	
	if (!CanRun()) return;
	
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = RunSpeed;
		IsRunning = true;
	}
}

void ATrainer::RunEnd()
{
	if (bIsInventoryOpen) return;
	
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = WalkSpeed;
		IsRunning = false;
	}
}

void ATrainer::Jump()
{
	if (bIsInventoryOpen) return;
	Super::Jump();
}

void ATrainer::Attack()
{
	if (TargetEnemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageEnemy"));
		TargetEnemy->TakeDamage(10.f);
	}
}

void ATrainer::Capture()
{
	if (TargetEnemy)
	{
		float HealthRatio = TargetEnemy->GetHealth();
		float CaptureChance = FMath::Clamp(1.f - HealthRatio, 0.05f, 0.95f);
		float RandomRoll = FMath::FRand();
		bool bCaptured = RandomRoll <= CaptureChance;
		if (bCaptured)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pet Captured Success (Chance: %2f / Roll: %2f)"), CaptureChance, RandomRoll);
			PetInventoryComponent->AddPet(TargetEnemy->GetData());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pet Captured Fail (Chance: %2f / Roll: %2f)"), CaptureChance, RandomRoll);
		}
	}
}

bool ATrainer::CanRun()
{
	return StaminaComponent->GetStaminaPercentage() > MinStaminaForRunPercent;
}

void ATrainer::SpawnAllyPet(UPetDataAsset* PetDataToSpawn)
{
	if (CurrentAllyPet == nullptr)
	{
		FVector SpawnPoint = PetSpawnPoint->GetComponentLocation();
		CurrentAllyPet = GetWorld()->SpawnActor<AAllyPet>(AllyPetToSpawn, SpawnPoint, FRotator::ZeroRotator);
	}
	
	CurrentAllyPet->SetData(PetDataToSpawn);
	CurrentAllyPet->ApplyPetData();
}

void ATrainer::InitializeInputSubsystem()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (InputSubsystem)
		{
			if (TrainerMappingContext)
			{
				InputSubsystem->AddMappingContext(TrainerMappingContext, 0);
			}
		}
	}
}

void ATrainer::InitializeHUD()
{
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
			
			PetInventoryWidget = GameHUD->GetPetInventoyWidget();
		}
	}
}

void ATrainer::InitializeInventory()
{
	if (PetInventoryComponent && DefaultPet)
	{
		PetInventoryComponent->AddPet(DefaultPet);
	}

	UpdateInventory();
}

void ATrainer::UpdateInventory()
{
	if (PetInventoryWidget)
	{
		PetInventoryWidget->PopulateInventory(PetInventoryComponent->OwnedPets);
		PetInventoryWidget->OnPetSelected.RemoveDynamic(this, &ATrainer::SpawnAllyPet);
		PetInventoryWidget->OnPetSelected.AddDynamic(this, &ATrainer::SpawnAllyPet);
	}
}

void ATrainer::TogglePetInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("Toggle Pet Inventory"));
	
	if (!PetInventoryWidget) return;
	
	if (bIsInventoryOpen)
	{
		PetInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		SetInputModeUI(false);
		bIsInventoryOpen = false;
	}
	else
	{
		PetInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		UpdateInventory();
		SetInputModeUI(true);
		RunEnd();
		bIsInventoryOpen = true;
	}
}

void ATrainer::SetInputModeUI(bool EnabledUI)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController || !InputSubsystem) return;
	
	if (EnabledUI)
	{
		PlayerController->SetShowMouseCursor(true);
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
		InputSubsystem->AddMappingContext(TrainerUIMappingContext, 1);
	}
	else
	{
		InputSubsystem->RemoveMappingContext(TrainerUIMappingContext);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void ATrainer::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFrownSweep, const FHitResult& SweepResult)
{
	if (AEnemyPet* EnemyPet = Cast<AEnemyPet>(OtherActor))
	{
		TargetEnemy = EnemyPet;
	}
}

void ATrainer::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemyPet* EnemyPet = Cast<AEnemyPet>(OtherActor);
	if (EnemyPet && TargetEnemy != nullptr)
	{
		TargetEnemy = nullptr;
	}
}
