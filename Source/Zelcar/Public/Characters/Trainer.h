// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Trainer.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UStaminaComponent;
class UTrainerWidget;

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

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void RunStart();
	void RunEnd();
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
	
	UTrainerWidget* TrainerWidget;
	bool IsRunning;
	bool CanRun();
};
