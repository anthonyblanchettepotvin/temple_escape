// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Interactable.h"
#include "InteractComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interact Component")
	float MinReach = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interact Component")
	float MaxReach = 150.0f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> Channel = ECollisionChannel::ECC_WorldDynamic;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interact Component")
	AActor* FocusedActor = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interact Component")
	FVector PlayerViewPointLocation = {0.0f, 0.0f, 0.0f};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interact Component")
	FRotator PlayerViewPointRotation = {0.0f, 0.0f, 0.0f};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interact Component")
	FVector InteractLineStart = {0.0f, 0.0f, 0.0f};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interact Component")
	FVector InteractLineEnd = {0.0f, 0.0f, 0.0f};

	UInputComponent* InputComponent = nullptr;

public:	
	// Sets default values for this component's properties
	UInteractComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Check if the owner has an Input component. */
	virtual bool FindInputComponent();

	/** Bind the Input component's actions to the corresponding member functions. */
	virtual void SetupInputComponent();

	/** Calls GetPlayerViewPoint and stores the result in to PlayerViewPointLocation and PlayerViewPointRotation.
	 * Gets called each tick.
	 */
	virtual void FetchPlayerViewPoint();

	/** Calculate the farthest location, perpendicular to the player's view point, at which an interaction can occur.
	 * Gets called each tick.
	 * @return The interaction line's end location
	 */
	UFUNCTION(BlueprintCallable, Category="Interact Component")
	FVector GetInteractLineEnd() const;

	/** Calculate the closest location, perpendicular to the player's view point, at which an interaction can occur.
	 * Gets called each tick.
	 * @return The interaction line's start location
	 */
	UFUNCTION(BlueprintCallable, Category="Interact Component")
	FVector GetInteractLineStart() const;

	/** Check if there's a interactable actor within reach.
	 * Gets called each tick.
	 * @return TRUE if any hit on an actor is found
	 */
	UFUNCTION(BlueprintCallable, Category="Interact Component")
	AActor* GetFocusedActor() const;

	/** Interact with the focused actor. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact Component")
	void Interact();

	// TODO: OnInteract()
};
