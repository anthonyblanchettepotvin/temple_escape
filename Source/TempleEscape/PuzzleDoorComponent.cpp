// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "PuzzleDoorComponent.h"
#include "DoorComponent.h"


// Sets default values for this component's properties
UPuzzleDoorComponent::UPuzzleDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPuzzleDoorComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPuzzleDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ConditionsMet_Implementation();
	this->Execute_ConditionsMet(this);
}


void UPuzzleDoorComponent::Interact()
{
	if (bUnlocked)
	{
		Super::Interact();
	}
}


bool UPuzzleDoorComponent::ConditionsMet_Implementation()
{
	if (Conditions.Num() == 0) { return true; }

	for (int32 i = 0; i < Conditions.Num(); i++)
	{
		if (!Conditions[i]->Execute_Evaluate(Conditions[i]))
		{
			if (bConditionsMet)
			{
				bConditionsMet = false;
				this->Execute_OnConditionsUnmet(this);
			}
			return false;
		}
	}
	
	if (!bConditionsMet)
	{
		bConditionsMet = true;
		this->Execute_OnConditionsMet(this);
	}
	return true;
}


void UPuzzleDoorComponent::OnConditionsMet_Implementation()
{
	bUnlocked = true;

	OpenDoor();
}


void UPuzzleDoorComponent::OnConditionsUnmet_Implementation()
{
	bUnlocked = false;

	CloseDoor();
}
