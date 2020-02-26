// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "Door.h"

#define DEBUG false

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsOpening && !bIsClosing) { return; }

	if (bIsOpening)
	{
		OpenDoorMovement(DeltaTime);

		if (ElapsedTime > OpenDuration)
		{
			bIsOpening = false;
			bIsOpen = true;
			ElapsedTime = 0.0f;
			InitialRotation = GetActorRotation();

			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Door opened."), *GetName());
			#endif

			OnDoorOpened();
		}

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
			InitialRotation = GetActorRotation();

			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Door closed."), *GetName());
			#endif

			OnDoorClosed();
		}

		return;
	}
}

void ADoor::OpenDoor()
{
	InitialRotation = GetActorRotation();

	// TODO: Refactor this bit of code.
	float Distance = FVector::Distance(OpenRotation.Vector(), CloseRotation.Vector());
	float DistanceLeft = FVector::Distance(InitialRotation.Vector(), CloseRotation.Vector());
	float Delta = DistanceLeft / Distance * OpenDuration; // TODO: Also, that variable name doesn't mean anything
	ElapsedTime = Delta;

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Open door."), *GetName());
	#endif

	bIsOpening = true;
	bIsClosing = false;
}

void ADoor::OpenDoorMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	CurrentRotation = FMath::Lerp(CloseRotation, OpenRotation, ElapsedTime / OpenDuration);

	SetActorRotation(CurrentRotation);
}

void ADoor::CloseDoor()
{
	InitialRotation = GetActorRotation();

	// TODO: Refactor this bit of code.
	float Distance = FVector::Distance(CloseRotation.Vector(), OpenRotation.Vector());
	float DistanceLeft = FVector::Distance(InitialRotation.Vector(), OpenRotation.Vector());
	float Delta = DistanceLeft / Distance * CloseDuration; // TODO: Also, that variable name doesn't mean anything
	ElapsedTime = Delta;

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Close door."), *GetName());
	#endif

	bIsClosing = true;
	bIsOpening = false;
}

void ADoor::CloseDoorMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	CurrentRotation = FMath::Lerp(OpenRotation, CloseRotation, ElapsedTime / CloseDuration);

	SetActorRotation(CurrentRotation);
}

void ADoor::OnDoorOpened_Implementation()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Door %s : Door opened event."), *GetName());
	#endif
}

void ADoor::OnDoorClosed_Implementation()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Door %s : Door closed event."), *GetName());
	#endif
}

bool ADoor::Interact_Implementation()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Door %s : Interaction attempt."), *GetName());
	#endif

	if (bIsOpening)
	{
		CloseDoor();
	}
	else if (bIsClosing)
	{
		OpenDoor();
	}
	else if (bIsOpen)
	{
		CloseDoor();
	}
	else
	{
		OpenDoor();
	}

	return true;
}
