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

	AudioComponent = FindAudioComponent();
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
			UE_LOG(LogTemp, Warning, TEXT("Door %s : Door opened."), *GetName());
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
			UE_LOG(LogTemp, Warning, TEXT("Door %s : Door closed."), *GetName());
			#endif

			OnDoorClosed();
		}

		return;
	}
}

UAudioComponent* ADoor::FindAudioComponent() const
{
	UAudioComponent* Component = FindComponentByClass<UAudioComponent>();
	
	if (!Component)
	{
		UE_LOG(LogTemp, Error, TEXT("Door %s : Audio Component missing."), *GetName());
	}

	return Component;
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
	UE_LOG(LogTemp, Warning, TEXT("Door %s : Open door."), *GetName());
	#endif

	bIsOpening = true;
	bIsClosing = false;

	PlayOpenSound();
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
	UE_LOG(LogTemp, Warning, TEXT("Door %s : Close door."), *GetName());
	#endif

	bIsClosing = true;
	bIsOpening = false;

	PlayCloseSound();
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

void ADoor::PlayOpenSound() const
{
	if (!AudioComponent) { return; }

	if (!OpenDoorSound) 
	{
		UE_LOG(LogTemp, Error, TEXT("Door %s : Open Door Sound missing."), *GetName());
	}

	AudioComponent->SetSound(OpenDoorSound);
	AudioComponent->Play();
}

void ADoor::PlayCloseSound() const
{
	if (!AudioComponent) { return; }

	if (!CloseDoorSound) 
	{
		UE_LOG(LogTemp, Error, TEXT("Door %s : Close Door Sound missing."), *GetName());
	}

	AudioComponent->SetSound(CloseDoorSound);
	AudioComponent->Play();
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
