// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "Engine/Datatable.h"
#include "PerformTypes.generated.h"

USTRUCT(BluePrintType)
struct REBIRTH_API FDialogueRow :public FTableRowBase
{
	GENERATED_BODY()

public:
	FDialogueRow()
		: Content("")
		, ReplayRowIndex(-1)
		, NextRowIndex(-1)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	FString Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	int32 ReplayRowIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	int32 NextRowIndex;
};

UENUM(BlueprintType)
enum class EGameModeType : uint8
{
	None = 0,
	Free UMETA(DisplayName = Free),
	Director UMETA(DisplayName = Director),
	Level UMETA(DisplayName = Level),

};

