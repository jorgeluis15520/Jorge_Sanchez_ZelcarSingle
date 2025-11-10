// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Trainer.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UPetInventoryWidget;
class UPetInventoyComponent;
class AAllyPet;
class UPetDataAsset;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UStaminaComponent;
class UTrainerWidget;
class USphereComponent;
class AEnemyPet;

UCLASS()
class ZELCAR_API ATrainer : public ACharacter
{
	GENERATED_BODY()

public:
	ATrainer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> TrainerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> RunAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InventoryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> CaptureAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> TrainerUIMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> CloseInventoryAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void RunStart();
	void RunEnd();
	virtual void Jump() override;
	void Attack();
	void Capture();
private:	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraArm;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaminaComponent> StaminaComponent;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 500.f;
	UPROPERTY(EditAnywhere)
	float RunSpeed = 800.f;
	UPROPERTY(EditAnywhere)
	float MinStaminaForRunPercent = 0.1f;
	
	bool IsRunning;
	bool CanRun();
	
	UPROPERTY()
	UTrainerWidget* TrainerWidget;

	UPROPERTY(EditAnywhere, Category = "Pet")
	TObjectPtr<UPetDataAsset> DefaultPet;
	UPROPERTY(EditAnywhere, Category = "Pet")
	TSubclassOf<AAllyPet> AllyPetToSpawn;
	UPROPERTY(VisibleAnywhere, Category = "Pet")
	USceneComponent* PetSpawnPoint;
	UPROPERTY()
	AAllyPet* CurrentAllyPet;

	UFUNCTION()
	void SpawnAllyPet(UPetDataAsset* PetDataToSpawn);
	
	UPROPERTY(VisibleAnywhere)
	UPetInventoyComponent* PetInventoryComponent;
	UPROPERTY()
	UPetInventoryWidget* PetInventoryWidget;
	
	bool bIsInventoryOpen = false;
	void InitializeInventory();
	void UpdateInventory();
	void TogglePetInventory();
	void InitializeHUD();

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem;
	
	void InitializeInputSubsystem();
	void SetInputModeUI(bool EnabledUI);

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere)
	AEnemyPet* TargetEnemy;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFrownSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
