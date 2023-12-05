// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RebirthCombatCharacterBase.h"
#include "RebirthCombatNPC.generated.h"

class UWidgetComponent;

/**
 *
 */
UCLASS()
class REBIRTH_API ARebirthCombatNPC : public ARebirthCombatCharacterBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	ARebirthCombatNPC();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy)
	static TSet<ARebirthCombatNPC*> Enemies;

	UFUNCTION(BlueprintCallable, Category = Enemy)
	static void GetAllEnemies(TArray<ARebirthCombatNPC*>& OutEnemies);

	UFUNCTION(BlueprintCallable, Category = Enemy)
	void AddSelfToEnemies();

	UFUNCTION(BlueprintCallable, Category = Enemy)
	void RemoveSelfFromEnemies();

	UFUNCTION(BlueprintCallable, Category = Enemy)
	void SetSelfTarget();

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy)
	int32 bTargeted;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy)
		UWidgetComponent* TargetWidget;

	UFUNCTION(BlueprintCallable, Category = Enemy)
		void RemoveSelfTarget();

	virtual void HandleDeath(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ARebirthCombatCharacterBase* InstigatorCharacter, AActor* DamageCauser) override;

};
