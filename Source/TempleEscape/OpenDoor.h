// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "InteractableComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UOpenDoor : public UInteractableComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Interact();
	virtual void OpenDoor();
	virtual void CloseDoor();
	virtual void OpenDoorMovement(const float DeltaTime);
	virtual void CloseDoorMovement(const float DeltaTime);

private:
	// UPROPERTY(EditAnywhere)
	// ATriggerVolume* Trigger;
	// UPROPERTY(EditAnywhere)
	// AActor* TriggeringActor;

	FRotator InitialRotation;
	FRotator CurrentRotation;
	UPROPERTY(EditAnywhere)
	FRotator OpenRotation = {0.0f, 90.0f, 0.0f};
	UPROPERTY(EditAnywhere)
	FRotator CloseRotation = {0.0f, 0.0f, 0.0f};
	
	UPROPERTY(EditAnywhere)
	float OpenDuration = 1.5f;
	UPROPERTY(EditAnywhere)
	float CloseDuration = 1.5f;
	float ElapsedTime = 0.0f;

	// UPROPERTY(EditAnywhere)
	// float TimeLastOpen = 3.0f;
	// float ElapsedTimeOpened = 0.0f;

	bool bIsOpen = false;
	bool bIsOpening = false;
	bool bIsClosing = false;
	//bool bIsMoving = false;
};
