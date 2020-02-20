// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleDoor.h"

#define DEBUG false

void APuzzleDoor::BeginPlay()
{
    Super::BeginPlay();

    for (const auto &Condition : Conditions)
    {
        if (Condition->GetClass()->ImplementsInterface(UPuzzleConditionInterface::StaticClass()))
        {
            ValidConditions.Add(Condition);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("APuzzleDoor [%s]: AActor [%s] doesn't implement IPuzzleConditionInterface. It will be ignored."), *GetName(), *Condition->GetName());
        }
    }

    #if DEBUG
    UE_LOG(LogTemp, Error, TEXT("APuzzleDoor [%s]: Number of valid AActors: %i."), *GetName(), ValidConditions.Num());
    #endif
}

void APuzzleDoor::Tick(float DeltaTime)
{   

    Execute_ConditionsMet(this);

    if (bIsUnlocked || bIsOpening || bIsClosing)
    {
        Super::Tick(DeltaTime);
    }
}

bool APuzzleDoor::Interact_Implementation()
{
    if (bIsUnlocked)
    {
        return Super::Interact_Implementation();
    }

    return false;
}

bool APuzzleDoor::ConditionsMet_Implementation()
{
    bool bConditionsMet = true;

    for (const auto &Condition : ValidConditions)
    {
        #if DEBUG
        UE_LOG(LogTemp, Warning, TEXT("APuzzleDoor [%s]: AActor [%s] evaluation..."), *GetName(), *Condition->GetName());
        #endif

        if (Condition->GetClass()->ImplementsInterface(UPuzzleConditionInterface::StaticClass()))
        {
            #if DEBUG
            UE_LOG(LogTemp, Warning, TEXT("APuzzleDoor [%s]: AActor [%s] implements IPuzzleConditionInterface."), *GetName(), *Condition->GetName());
            #endif

            if (!IPuzzleConditionInterface::Execute_Evaluate(Condition))
            {
                bConditionsMet = false;
                break;
            }
        }
    }

    if (bConditionsMet && !bIsUnlocked) { Execute_OnConditionsMet(this); }

    if (!bConditionsMet && bIsUnlocked) { Execute_OnConditionsUnmet(this); }

    return bConditionsMet;
}

void APuzzleDoor::OnConditionsMet_Implementation()
{
    bIsUnlocked = true;

    #if DEBUG
    UE_LOG(LogTemp, Warning, TEXT("PuzzleDoor [%s]: OnConditionsMet event invoked."), *GetName());
    #endif

    OpenDoor();
}

void APuzzleDoor::OnConditionsUnmet_Implementation()
{
    bIsUnlocked = false;

    #if DEBUG
    UE_LOG(LogTemp, Warning, TEXT("PuzzleDoor [%s]: OnConditionsUnmet event invoked."), *GetName());
    #endif

    CloseDoor();
}
