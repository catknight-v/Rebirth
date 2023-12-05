// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "TopSideView/TopSideViewTypes.h"
#include "RebirthPlayerCameraManager.generated.h"

class ATopSideViewTargetActor;

/**
 * 
 */
UCLASS()
class REBIRTH_API ARebirthPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:

	virtual void UpdateCamera(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LookUp(float Rate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	ECameraModeType CameraMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	FTopSideViewInfo TopSideViewInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	ATopSideViewTargetActor* CurrentViewActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	ATopSideViewTargetActor* FollowViewActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	ATopSideViewTargetActor* TargetViewActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	AActor* FollowActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	AActor* TargetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	ATopSideViewTargetActor* AdsorptionViewActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	ATopSideViewTargetActor* AnimationViewActor;

	UFUNCTION(BlueprintCallable)
	void SetTargetActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void SetFollowActor(AActor* Actor);

	/*UFUNCTION(BlueprintCallable)
	void SetModeFollow();

	UFUNCTION(BlueprintCallable)
	void SetModeTarget(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void SetModeAdsorption(FVector Location);

	UFUNCTION(BlueprintCallable)
	ATopSideViewTargetActor* SetModeAnimation();*/

};
