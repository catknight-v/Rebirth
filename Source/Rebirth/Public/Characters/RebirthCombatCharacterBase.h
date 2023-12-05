// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Items/ItemTypes.h"
#include "Abilities/RebirthAbilitySystemComponent.h"
#include "Abilities/RebirthAttributeSet.h"
#include "RebirthCombatCharacterBase.generated.h"

UCLASS()
class REBIRTH_API ARebirthCombatCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARebirthCombatCharacterBase();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/*ASC*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	URebirthAbilitySystemComponent* AbilitySystemComponent;

	/*AS*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	URebirthAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	int32 bAbilitiesInitialized;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Knapsack)
	FKnapsack Knapsack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	int32 bActionable;

	UFUNCTION(BlueprintCallable, Category = Movement)
	bool IsActionable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	int32 bDead;

	UFUNCTION(BlueprintCallable, Category = Movement)
	virtual	void SetActionable(bool bCharacterActionable);

	UFUNCTION(BlueprintCallable, Category = Item)
	virtual	void LoadDefaultItems();

	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual	void InitAbilities();

	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual void ActivateInitAbilities();

	UFUNCTION(BlueprintCallable, Category = Character)
	virtual void CombatCharacterInit();

	UFUNCTION(BlueprintCallable)
	virtual void CombatReset();

	UFUNCTION(BlueprintCallable)
	void FaceToInstantly(FVector Location);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetEnergy() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxEnergy() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMoveSpeed() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ARebirthCombatCharacterBase* InstigatorCharacter, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath(float DamageAmount, const FHitResult& HitInfo, const FGameplayTagContainer& DamageTags, ARebirthCombatCharacterBase* InstigatorCharacter, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnergyChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ARebirthCombatCharacterBase* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleDeath(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ARebirthCombatCharacterBase* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleEnergyChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
};
