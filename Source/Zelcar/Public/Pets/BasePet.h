// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Characters/CharacterTypes.h"
#include "BasePet.generated.h"

class UPetAbilitySystemComponent;
class UGameplayAbility_Montage;
class UHealthBarWidgetComponent;
class AAIController;
class UHealthComponent;
class UPetDataAsset;
class UAnimMontage;

UCLASS()
class ZELCAR_API ABasePet : public ACharacter, public IAbilitySystemInterface
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

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TObjectPtr<UPetAbilitySystemComponent> PetAbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TSubclassOf<UGameplayAbility_Montage> BasicAttackAbility;

	UPROPERTY(EditAnywhere, Category = "Attack Montage")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	ECharacterState PetState = ECharacterState::ECS_Unoccupied;

	bool bInCombat = false;
public:
	void ApplyPetData();
	void ApplyDamage(float DamageAmount);
	void ShowHealthBar();
	void HideHealthBar();
	
	FORCEINLINE void SetData(UPetDataAsset* Data) { PetData = Data; }
	FORCEINLINE UPetDataAsset* GetData() { return PetData; }
	FORCEINLINE float GetHealth() { return HealthComponent->GetHealthPercentage();}

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void Attack(ABasePet* PetTarget);
	UPROPERTY()
	ABasePet* PetEnemyTarget;
	
	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	FORCEINLINE ECharacterState GetPetState() { return PetState; }

	virtual void StartCombat();
	virtual void EndCombatByEscape();
	virtual void EndCombatByCapture();
};
