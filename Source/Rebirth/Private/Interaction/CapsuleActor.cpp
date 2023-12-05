// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/CapsuleActor.h"
#include "Components/CapsuleComponent.h"
#include "Interaction/InteractionInterface.h"

// Sets default values
ACapsuleActor::ACapsuleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleRoot"));
	SetRootComponent(CapsuleComponent);

	//OnActorBeginOverlap
	OnActorBeginOverlap.AddDynamic(this, &ACapsuleActor::EnterInteractableArea);
	OnActorEndOverlap.AddDynamic(this, &ACapsuleActor::LeaveInteractableArea);

}

void ACapsuleActor::EnterInteractableArea(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		//bool bA = IInteractionInterface::Execute_CanInteract(OtherActor, GetOwner());
		if (InteractingActor)
		{
			IInteractionInterface::Execute_LeaveInteractableArea(InteractingActor, GetOwner());
		}
		InteractingActor = OtherActor;
		IInteractionInterface::Execute_EnterInteractableArea(OtherActor, GetOwner());
	}
}

void ACapsuleActor::LeaveInteractableArea(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		if (InteractingActor == OtherActor)
		{
			IInteractionInterface::Execute_LeaveInteractableArea(OtherActor, GetOwner());
			InteractingActor = nullptr;
		}
	}
}

void ACapsuleActor::InteractWith(AActor* OtherActor)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		return IInteractionInterface::Execute_InteractWith(OtherActor, GetOwner());
	}
}

void ACapsuleActor::InteractWithInteractingActor()
{
	if (InteractingActor)
	{
		InteractWith(InteractingActor);
		if (InteractingActor)
		{
			IInteractionInterface::Execute_LeaveInteractableArea(InteractingActor, GetOwner());
			InteractingActor = nullptr;
		}
	}
}
