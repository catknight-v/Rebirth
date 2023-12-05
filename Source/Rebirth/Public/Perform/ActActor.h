// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Perform/PerformTypes.h"
#include "ActActor.generated.h"

class UDialogueUserWidget;
class UDataTable;
class ARebirthPlayerController;

/**
* 
* 
*/

USTRUCT(BluePrintType)
struct REBIRTH_API FActorInPlaceInfo
{
	GENERATED_BODY()

public:

	FActorInPlaceInfo() :bInPlace(false) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorInPlaceInfo)
	FGameplayTag ActorTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorInPlaceInfo)
	AActor* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorInPlaceInfo)
	int32 bInPlace;
};

UCLASS()
class REBIRTH_API AActActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Act)
	ARebirthPlayerController* PlayerController;

	UFUNCTION(BlueprintCallable)
	void SetDirector(ARebirthPlayerController* Controller);

	UFUNCTION(BlueprintCallable)
	ARebirthPlayerController* GetDirector();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Act)
	UDialogueUserWidget* DialogueUserWidget;

	UFUNCTION(BlueprintCallable)
	UDialogueUserWidget* GetDialogueUserWidget();

	UFUNCTION(BlueprintCallable)
	void SetPlayerControllable(bool bControllable);

	UFUNCTION(BlueprintCallable)
	void SetControllerGameMode(EGameModeType Mode);

	UFUNCTION(BlueprintCallable)
	void ControllerPreAct();

	UFUNCTION(BlueprintCallable)
	void ControllerActCut();

	UFUNCTION(BlueprintImplementableEvent)
	void ActPrepare();

	UFUNCTION(BlueprintImplementableEvent)
	void ActAction();

	UFUNCTION(BlueprintImplementableEvent)
	int32 PushForward();

	UFUNCTION(BlueprintCallable)
	virtual FActorInPlaceInfo FindActor(FGameplayTag ActorTag);

	UFUNCTION(BlueprintCallable)
	UDialogueUserWidget* BeginDialogue(TSubclassOf<UDialogueUserWidget> Widget, UDataTable* DataTable, int32 StartIndex);

};
