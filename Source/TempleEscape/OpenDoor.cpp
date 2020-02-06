// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define DEBUG true

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// InitialRotation = GetOwner()->GetActorRotation();
	// TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	// if (!Trigger)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s has the OpenDoor component, but the Trigger property is not set."), *GetOwner()->GetName());
	// }

	// if (!TriggeringActor)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s has the OpenDoor component, but the TriggeringActor property couldn't be set."), *GetOwner()->GetName());
	// }
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (!Trigger || !TriggeringActor)
	// {
	// 	return;
	// }

	// if (ElapsedTime > TimeToOpen)
	// {
	// 	ElapsedTime = 0.0f;
	// 	bIsOpen = !bIsOpen;
	// 	bIsMoving = false;
	// 	InitialRotation = GetOwner()->GetActorRotation();
	// 	return;
	// }

	// if (bIsOpen && !bIsMoving)
	// {
	// 	ElapsedTimeOpened += DeltaTime;

	// 	if (ElapsedTimeOpened > TimeLastOpen)
	// 	{
	// 		ElapsedTimeOpened = 0.0f;
	// 		bIsMoving = true;
	// 	}
	// }

	// if (Trigger->IsOverlappingActor(TriggeringActor) && !bIsMoving)
	// {
	// 	bIsMoving = true;
	// }

	// if (bIsMoving && !bIsOpen)
	// {
	// 	OpenDoor(DeltaTime);
	// }
	// else if (bIsMoving && bIsOpen)
	// {
	// 	CloseDoor(DeltaTime);
	// }

	if (!bIsOpening && !bIsClosing) { return; }

	if (bIsOpening)
	{
		OpenDoorMovement(DeltaTime);

		if (ElapsedTime > OpenDuration)
		{
			bIsOpening = false;
			bIsOpen = true;
			ElapsedTime = 0.0f;
			InitialRotation = GetOwner()->GetActorRotation();

			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Door opened."), *GetOwner()->GetName());
			#endif
		}

		// TODO : OnDoorOpened event ?

		return;
	}

	if (bIsClosing)
	{
		CloseDoorMovement(DeltaTime);

		if (ElapsedTime > CloseDuration)
		{
			bIsClosing = false;
			bIsOpen = false;
			ElapsedTime = 0.0f;
			InitialRotation = GetOwner()->GetActorRotation();

			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Door closed."), *GetOwner()->GetName());
			#endif
		}

		// TODO : OnDoorClosed event ?

		return;
	}
}


void UOpenDoor::Interact()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Interaction attempt."), *GetOwner()->GetName());
	#endif
	
	ElapsedTime = 0.0f;
	InitialRotation = GetOwner()->GetActorRotation();

	if (bIsOpening) // Door opening, so we close the door
	{
		bIsOpening = false;
		CloseDoor();
	}
	else if (bIsClosing) // Door closing, so we open the door
	{
		bIsClosing = false;
		OpenDoor();
	}
	else if (!bIsOpening && !bIsClosing && bIsOpen) // Door is open, so we close it
	{
		CloseDoor();
	}
	else // Door is close, se we open it
	{
		OpenDoor();
	}
}


void UOpenDoor::OpenDoor()
{

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Open door."), *GetOwner()->GetName());
	#endif

	bIsOpening = true;
}


void UOpenDoor::OpenDoorMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	CurrentRotation = FMath::Lerp(InitialRotation, OpenRotation, ElapsedTime / OpenDuration);

	GetOwner()->SetActorRotation(CurrentRotation);
}


void UOpenDoor::CloseDoor()
{
	InitialRotation = GetOwner()->GetActorRotation();

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Close door."), *GetOwner()->GetName());
	#endif

	bIsClosing = true;
}


void UOpenDoor::CloseDoorMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	CurrentRotation = FMath::Lerp(InitialRotation, CloseRotation, ElapsedTime / CloseDuration);

	GetOwner()->SetActorRotation(CurrentRotation);
}
