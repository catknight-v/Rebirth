// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopSideViewTypes.generated.h"


USTRUCT(BlueprintType)
struct REBIRTH_API FTopSideViewInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopSideViewInfo")
	float CurrentRate = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopSideViewInfo")
	float MaxTopRate = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopSideViewInfo")
	float MinTopRate = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopSideViewInfo")
	float CameraDistance = 1800.0f;
};

UENUM(BlueprintType)
enum class ECameraModeType : uint8
{
	None = 0,
	Follow UMETA(DisplayName = "Follow"),
	Target UMETA(DisplayName = "Target"),
	Adsorption UMETA(DisplayName = "Adsorption"),
	Animation UMETA(DisplayName = "Animation"),
};