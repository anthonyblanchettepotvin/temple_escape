// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "GrabberComponent.h"

#define DEBUG false
#define TICK_DEBUG false
#define VISUAL_DEBUG false

void UGrabberComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!FindPhysicsHandleComponent()) { return; }
}

bool UGrabberComponent::FindPhysicsHandleComponent()
{
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("GrabberComponent on %s : PhysicsHandle component required."), *GetOwner()->GetName());
		
		return false;
	}
	else
	{
		#if DEBUG
		UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : PhysicsHandle component found."), *GetOwner()->GetName());
		#endif

		return true;
	}
}

void UGrabberComponent::SetupInputComponent()
{
	if (!InputComponent) { return; }

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabberComponent::Interact_Implementation);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabberComponent::Interact_Implementation);
}

void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandleComponent) { return; }

	if (PhysicsHandleComponent->GrabbedComponent)
	{	
		#if VISUAL_DEBUG
		DrawDebugSphere(GetWorld(), InteractLocation, 10.0f, 16, FColor::Cyan, false, 0.0f, 1);
		#endif

		PhysicsHandleComponent->SetTargetLocation(InteractLineEnd);
	}
}

void UGrabberComponent::Interact_Implementation()
{	
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : Interaction attempt."), *GetOwner()->GetName());
	#endif

	if (!PhysicsHandleComponent) { return; }
    
    PhysicsHandleComponent->GrabbedComponent ? Release() : Grab();
}

void UGrabberComponent::Grab_Implementation()
{	
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : Grabbing attempt."), *GetOwner()->GetName());
	#endif

	if (!PhysicsHandleComponent) { return; }

    if (PhysicsHandleComponent->GrabbedComponent) { return; }

	if (FocusedActor)
	{	
		UPrimitiveComponent* FocusedActorPrimitive = FocusedActor->FindComponentByClass<UPrimitiveComponent>();
		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(
			FocusedActorPrimitive,
			NAME_None,
			FocusedActor->GetActorLocation(),
			FocusedActor->GetActorRotation()
		);

		GrabbedActor = FocusedActor;

		if (OnGrab.IsBound()) { OnGrab.Broadcast(); }
	}
}

void UGrabberComponent::Release_Implementation()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : Releasing attempt."), *GetOwner()->GetName());
	#endif

	if (!PhysicsHandleComponent) { return; }

    if (!PhysicsHandleComponent->GrabbedComponent) { return; }

	PhysicsHandleComponent->ReleaseComponent();

	GrabbedActor = nullptr;

	if (OnRelease.IsBound()) { OnRelease.Broadcast(); }
}
