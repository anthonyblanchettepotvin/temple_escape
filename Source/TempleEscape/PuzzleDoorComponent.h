// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.h"
#include "PuzzleObjective.h"
#include "PuzzleDoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleDoorComponent : public UPuzzleObjective
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleDoorComponent();

public:
	virtual void Unlock() override;
	virtual void Lock() override;

private:
	UPROPERTY(EditAnywhere)
	AActor* Door = nullptr;

	bool Unlocked = false;
};
