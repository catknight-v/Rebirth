// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionComponent.h"
#include "Interaction/InteractionInterface.h"
#include "Interaction/CapsuleActor.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}


void UInteractionComponent::InteractWithInteractingActor()
{
	CapsuleActor->InteractWithInteractingActor();
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	CapsuleActor = GetWorld()->SpawnActor<ACapsuleActor>();
	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, true);
	CapsuleActor->AttachToComponent(this, Rules);
	CapsuleActor->CapsuleComponent->SetCapsuleHalfHeight(CapsuleHalfHeight);
	CapsuleActor->CapsuleComponent->SetCapsuleRadius(CapsuleRadius);
	CapsuleActor->SetOwner(GetOwner());
}

//void UInteractionComponent::EnterInteractableArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
//	{
//		//bool bA = IInteractionInterface::Execute_CanInteract(OtherActor, GetOwner());
//		if (InteractingActor)
//		{
//			IInteractionInterface::Execute_LeaveInteractableArea(InteractingActor, GetOwner());
//		}
//		InteractingActor = OtherActor;
//		IInteractionInterface::Execute_EnterInteractableArea(OtherActor, GetOwner());
//	}
//}
//
//void UInteractionComponent::LeaveInteractableArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
//	{
//		if (InteractingActor == OtherActor)
//		{
//			IInteractionInterface::Execute_LeaveInteractableArea(OtherActor, GetOwner());
//			InteractingActor = nullptr;
//		}
//	}
//}
//
//void UInteractionComponent::InteractWith(AActor* OtherActor)
//{
//	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
//	{
//		return IInteractionInterface::Execute_InteractWith(OtherActor, GetOwner());
//	}
//
//}
//
//void UInteractionComponent::InteractWithInteractingActor()
//{
//	if (InteractingActor)
//	{
//		InteractWith(InteractingActor);
//		if (InteractingActor)
//		{
//			IInteractionInterface::Execute_LeaveInteractableArea(InteractingActor, GetOwner());
//			InteractingActor = nullptr;
//		}
//	}
//}
