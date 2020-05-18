// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "InteractComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGrabSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReleaseSignature);

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UGrabberComponent : public UInteractComponent
{

	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grabber Component")
	AActor* GrabbedActor = nullptr;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandleComponent = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrabberComponent)
	float GrabDistance = 75.0f;

	// Called when the game starts
	virtual void BeginPlay() override;

	/** Check if the owner has a PhysicsHandle component. */
	virtual bool FindPhysicsHandleComponent();

	/** Bind the Input component's actions to the corresponding member functions. */
	virtual void SetupInputComponent() override;

	/** Interact with the focused actor. */
	virtual void Interact_Implementation() override;

	/** Grab the focused actor. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Grabber Component")
	void Grab();

	/** Release the grabbed actor. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Grabber Component")
	void Release();

	/** Calculate the grab location, perpendicular to the player's view point.
	 * Gets called each tick.
	 * @return The grab location
	 */
	UFUNCTION(BlueprintCallable, Category = GrabberComponent)
	FVector GetGrabLocation() const;

	/** Event that happens when an actor has been grabbed. */
	UPROPERTY(BlueprintAssignable, Category="GrabberComponent")
	FOnGrabSignature OnGrab;

	/** Event that happens when an actor has been released. */
	UPROPERTY(BlueprintAssignable, Category="GrabberComponent")
	FOnReleaseSignature OnRelease;
};
