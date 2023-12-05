// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueUserWidget.generated.h"

class UDataTable;
class UTextBlock;
class UWidgetAnimation;

UCLASS()
class REBIRTH_API UDialogueUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dialogue)
	UDataTable* DialogueDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dialogue)
	int32 CurrentDialogueIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dialogue)
	int32 NextDialogueIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dialogue)
	int32 CurrentReplayIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dialogue)
	int32 bCurrentDialogueEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dialogue)
	int32 bAddedToViewport = false;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ContentTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ReplayTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim))
	UWidgetAnimation* ContentFadeInAnim;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim))
	UWidgetAnimation* ContentFadeOutAnim;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim))
	UWidgetAnimation* ReplayFadeInAnim;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim))
	UWidgetAnimation* ReplayFadeOutAnim;

	UFUNCTION(BlueprintCallable)
	void BeginDialogue(UDataTable* DataTable, int32 StartIndex);

	UFUNCTION(BlueprintCallable)
	void ShowDialogueWidget();

	UFUNCTION(BlueprintCallable)
	void HideDialogueWidget();

	UFUNCTION(BlueprintCallable)
	int32 NextDialogue();

	UFUNCTION(BlueprintCallable)
	void EndDialogue();

	UFUNCTION(BlueprintCallable)
	void LoadCurrentDialogue();

	UFUNCTION()
	void EndCurrentDialogue();

	UFUNCTION()
	void ReplayFadeIn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dialogue)
	int32 bReplayVisible = false;

	UFUNCTION()
	void ReplayFadeOut();

	UFUNCTION()
	void HandleRemoveFromParent();
};
