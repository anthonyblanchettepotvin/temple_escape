// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLEESCAPE_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/**
	 * Create the door's open movement using linear interpolation.
	 * @param DeltaTime coming from the Tick member function
	 */
	virtual void OpenDoorMovement(const float DeltaTime);

	/**
	 * Create the door's close movement using linear interpolation.
	 * @param DeltaTime coming from the Tick member function 
	 */
	virtual void CloseDoorMovement(const float DeltaTime);
	
	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void OpenDoor();
	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void CloseDoor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Door")
	void OnDoorOpened();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Door")
	void OnDoorClosed();

	virtual bool Interact_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator OpenRotation = {0.0f, 90.0f, 0.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator CloseRotation = {0.0f, 0.0f, 0.0f};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator InitialRotation = {0.0f, 0.0f, 0.0f};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator CurrentRotation = {0.0f, 0.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpenDuration = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CloseDuration = 1.5f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ElapsedTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsOpen = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsOpening = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsClosing = false;
};
