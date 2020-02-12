// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractComponent.h"
#include "Door.generated.h"

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

	virtual void OpenDoorMovement(const float DeltaTime);
	virtual void CloseDoorMovement(const float DeltaTime);
	
	UFUNCTION(BlueprintCallable, Category="Door")
		virtual void OpenDoor();
	UFUNCTION(BlueprintCallable, Category="Door")
		virtual void CloseDoor();

	UFUNCTION(BlueprintCallable, BlueprintGetter, Category="Door")
		virtual bool IsOpen() const;
	UFUNCTION(BlueprintCallable, BlueprintGetter, Category="Door")
		virtual bool IsOpening() const;
	UFUNCTION(BlueprintCallable, BlueprintGetter, Category="Door")
		virtual bool IsClosing() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Door")
		void OnDoorOpened();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Door")
		void OnDoorClosed();

	virtual bool Interact_Implementation() override;

protected:
	FRotator InitialRotation;
	FRotator CurrentRotation;
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere)
		FRotator OpenRotation = {0.0f, 90.0f, 0.0f};
	UPROPERTY(EditAnywhere)
		FRotator CloseRotation = {0.0f, 0.0f, 0.0f};
	UPROPERTY(EditAnywhere)
		float OpenDuration = 1.5f;
	UPROPERTY(EditAnywhere)
		float CloseDuration = 1.5f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter=IsOpen)
		bool bIsOpen = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter=IsOpening)
		bool bIsOpening = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter=IsClosing)
		bool bIsClosing = false;
};
