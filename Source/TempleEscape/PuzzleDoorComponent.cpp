// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "PuzzleDoorComponent.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UPuzzleDoorComponent::UPuzzleDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UPuzzleDoorComponent::Interact()
{
	if (Unlocked)
	{
		UOpenDoor::Interact();
	}
}

bool UPuzzleDoorComponent::Unlock_Implementation()
{
	Unlocked = true;
	
	OpenDoor();
	
	UE_LOG(LogTemp, Warning, TEXT("PuzzleDoorComponent on %s : Unlocked."), *GetOwner()->GetName());

	return true;
}

bool UPuzzleDoorComponent::Lock_Implementation()
{
	Unlocked = false;
	
	CloseDoor();

	UE_LOG(LogTemp, Warning, TEXT("PuzzleDoorComponent on %s : Unlocked."), *GetOwner()->GetName());

	return true;
}
