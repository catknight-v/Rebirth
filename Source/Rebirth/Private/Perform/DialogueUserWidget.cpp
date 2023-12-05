// Fill out your copyright notice in the Description page of Project Settings.


#include "Perform/DialogueUserWidget.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "Perform/PerformTypes.h"

void UDialogueUserWidget::BeginDialogue(UDataTable* DataTable, int32 StartIndex)
{
	DialogueDataTable = DataTable;
	bCurrentDialogueEnd = true;
	CurrentDialogueIndex = StartIndex;
	/*if (!bAddedToViewport)
	{
		AddToViewport();
		bAddedToViewport = true;
	}*/
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	LoadCurrentDialogue();
	ShowDialogueWidget();
	ReplayTextBlock->SetRenderOpacity(0.f);
}

void UDialogueUserWidget::ShowDialogueWidget()
{
	PlayAnimation(ContentFadeInAnim);
}

void UDialogueUserWidget::HideDialogueWidget()
{
	PlayAnimation(ContentFadeOutAnim);
}

int32 UDialogueUserWidget::NextDialogue()
{
	if (bCurrentDialogueEnd)
	{
		CurrentDialogueIndex = NextDialogueIndex;
		if (CurrentDialogueIndex != -1)
		{
			ReplayFadeOut();
			LoadCurrentDialogue();
		}
		else
		{
			EndDialogue();
		}
	}
	return CurrentDialogueIndex;
}

void UDialogueUserWidget::EndDialogue()
{
	HideDialogueWidget();
	FTimerHandle RemoveHandle;
	GetWorld()->GetTimerManager().SetTimer(RemoveHandle, this, &UDialogueUserWidget::HandleRemoveFromParent, 0.25f, false);
}

void UDialogueUserWidget::LoadCurrentDialogue()
{
	bCurrentDialogueEnd = false;
	//读数据表
	if (DialogueDataTable)
	{
		FString RowString = FString::FromInt(CurrentDialogueIndex);
		FName RowName = *RowString;
		FDialogueRow* Row = DialogueDataTable->FindRow<FDialogueRow>(RowName, RowString);
		//如果找到行
		if (Row)
		{
			NextDialogueIndex = Row->NextRowIndex;
			CurrentReplayIndex = Row->ReplayRowIndex;
			//向内容框写入
			if (ContentTextBlock)
			{
				ContentTextBlock->SetText(FText::FromString(Row->Content));
			}
			//如果有回答
			if (Row->ReplayRowIndex != -1)
			{
				FString ReplayRowString = FString::FromInt(Row->ReplayRowIndex);
				FName ReplayRowName = *ReplayRowString;
				FDialogueRow* ReplayRow = DialogueDataTable->FindRow<FDialogueRow>(ReplayRowName, ReplayRowString);
				//向回答内容框
				if (ReplayRow)
				{
					ReplayTextBlock->SetText(FText::FromString(ReplayRow->Content));
				}
			}
		}
	}

	//设置延迟
	float DelayTime = CurrentReplayIndex == -1 ? 1.f : 1.5f;
	FTimerHandle EndTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(EndTimerHandle, this, &UDialogueUserWidget::EndCurrentDialogue, DelayTime, false);

	if (CurrentReplayIndex != -1)
	{
		FTimerHandle ReplayTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ReplayTimerHandle, this, &UDialogueUserWidget::ReplayFadeIn, 1.f, false);
	}
}

void UDialogueUserWidget::EndCurrentDialogue()
{
	bCurrentDialogueEnd = true;
}

void UDialogueUserWidget::ReplayFadeIn()
{
	if (!bReplayVisible)
	{
		bReplayVisible = true;
		PlayAnimation(ReplayFadeInAnim);
	}
}

void UDialogueUserWidget::ReplayFadeOut()
{
	if (bReplayVisible)
	{
		bReplayVisible = false;
		ReplayTextBlock->SetRenderOpacity(0.f);
		//PlayAnimation(ReplayFadeOutAnim);
	}
}

void UDialogueUserWidget::HandleRemoveFromParent()
{
	RemoveFromParent();
}

