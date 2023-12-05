// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Rebirth/RebirthAssetManager.h"
#include "GameplayLevelInfo.generated.h"

/**
 * 
 */
UCLASS()
class REBIRTH_API UGameplayLevelInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UGameplayLevelInfo()
	{
		LevelType = URebirthAssetManager::LevelInfoType;
		LevelName = TEXT("Map_1_Plain_Gameplay");
		PlayerStart = FVector(-80.f, 60.f, 210.f);
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LevelInfo)
	FPrimaryAssetType LevelType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LevelInfo)
	FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LevelInfo)
	FVector PlayerStart;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

};
