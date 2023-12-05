// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TopSideView/TopSideViewTypes.h"
#include "TopSideViewTargetActor.generated.h"

class UCapsuleComponent;

UCLASS()
class REBIRTH_API ATopSideViewTargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATopSideViewTargetActor();
	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopSideViewInfo")
	FTopSideViewInfo TopSideViewInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopSideViewInfo")
	UCapsuleComponent* CapsuleComponent;

	UFUNCTION()
	void SetViewInfo(const FTopSideViewInfo& ViewInfo);

};
