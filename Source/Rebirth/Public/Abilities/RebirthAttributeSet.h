// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RebirthAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class REBIRTH_API URebirthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	URebirthAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URebirthAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URebirthAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS(URebirthAttributeSet, Energy)

	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS(URebirthAttributeSet, MaxEnergy)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(URebirthAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(URebirthAttributeSet, MoveSpeed)

};
