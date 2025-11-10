// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "BasePet.generated.h"

class UHealthBarWidgetComponent;
class AAIController;
class UHealthComponent;
class UPetDataAsset;

UCLASS()
class ZELCAR_API ABasePet : public ACharacter
{
	GENERATED_BODY()

public:
	ABasePet();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void MoveToTarget(AActor* Target, float AcceptanceRadius);
	virtual void InitializePet();
	
	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;
	UPROPERTY(visibleAnywhere)
	UHealthBarWidgetComponent* HealthBarWidgetComponent;
	UPROPERTY()
	AAIController* PetAIController;
	UPROPERTY(EditAnywhere, Category = "PetData")
	TObjectPtr<UPetDataAsset> PetData;
	
public:
	void ApplyPetData();
	void TakeDamage(float DamageAmount);
	
	FORCEINLINE void SetData(UPetDataAsset* Data) { PetData = Data; }
	FORCEINLINE UPetDataAsset* GetData() { return PetData; }
	FORCEINLINE float GetHealth() { return HealthComponent->GetHealthPercentage();}
};
