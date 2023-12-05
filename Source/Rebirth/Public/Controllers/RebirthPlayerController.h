// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopSideView/TopSideViewTypes.h"
#include "Perform/PerformTypes.h"
#include "RebirthPlayerController.generated.h"

class ATopSideViewTargetActor;
class AActActor;
class UGameplayLevelInfo;
class UDefaultTag;

/**
 * 
 */


UCLASS()
class REBIRTH_API ARebirthPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraSetting)
	TSubclassOf<ATopSideViewTargetActor> FollowActorClass;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	ATopSideViewTargetActor* ViewTargetActor;

	UFUNCTION(BlueprintCallable)
	ATopSideViewTargetActor* GetViewTargetActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	ATopSideViewTargetActor* AnimTargetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	int32 bUsingAnimaTargetActor;

	UFUNCTION(BlueprintCallable)
	ATopSideViewTargetActor* EnterAnimView();

	UFUNCTION(BlueprintCallable)
	void QuitAnimView();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSetting)
	FTopSideViewInfo TopSideViewInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	int32 bActionControllable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
	AActor* Target;

	UFUNCTION(BlueprintCallable)
	AActor* GetTarget();

	UFUNCTION(BlueprintCallable)
	void FindTarget(int32 Mode = 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	EGameModeType CurrentMode;

	UFUNCTION(BlueprintCallable, Category = Player)
	void SetActionControllable(bool bControllable);

	UFUNCTION(BlueprintCallable, Category = Player)
	void SetGameMode(EGameModeType NewMode);

	UFUNCTION(BlueprintCallable)
	int32 PlayAnAct(TSubclassOf<AActActor> ActClass);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameModeType)
	AActActor* CurrentAct;

	UFUNCTION(BlueprintCallable)
	void PushForwardInteraction();

	UFUNCTION(BlueprintImplementableEvent)
	void PushForwardLevel();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Save)
	UGameplayLevelInfo* CurrentLevel;

	UFUNCTION(BlueprintCallable)
	UDefaultTag* GetDefaultTag();

protected:

	void UpdateViewTarget();
	void UpdateTarget();


	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Rate);
	void Jump();
	void Melee();
	void Dodge();
	void Interact();
	void SearchTarget();
	void SearchTargetX(float Value);

};
