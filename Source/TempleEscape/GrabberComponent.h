// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "InteractComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"

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

	UPhysicsHandleComponent* PhysicsHandleComponent = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
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

	// TODO: OnGrab()

	// TODO: OnRelease()
};
