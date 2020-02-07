// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "PuzzleDoorComponent.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UPuzzleDoorComponent::UPuzzleDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;
}

// void UPuzzleDoorComponent::Interact()
// {
// 	if (Unlocked)
// 	{
// 		UOpenDoor::Interact();
// 	}
// }

void UPuzzleDoorComponent::Unlock()
{
	if (!Door) { return; }

	UOpenDoor* test = Door->FindComponentByClass<UOpenDoor>();

	if (test)
	{
		Unlocked = true;
		
		test->OpenDoor();
	}
}

void UPuzzleDoorComponent::Lock()
{
	if (!Door) { return; }

	UOpenDoor* test = Door->FindComponentByClass<UOpenDoor>();

	if (test)
	{
		Unlocked = false;
		
		test->CloseDoor();
	}
}
