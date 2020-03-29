// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleButton.h"

// ABaseButton overrides
void APuzzleButton::Press()
{
    Super::Press();

    Trigger_Implementation();
}

bool APuzzleButton::Interact_Implementation()
{
    Super::Interact_Implementation();
    
    // TODO: This bit of code is repeated in ABaseButton, should probably be a function by itseft
    for (APuzzleButton* AdjacentButton : AdjacentButtons)
    {
        if (AdjacentButton->bIsPressing)
        {
            AdjacentButton->Unpress();
        }
        else if (AdjacentButton->bIsUnpressing)
        {
            AdjacentButton->Press();
        }
        else if (AdjacentButton->bIsPressed)
        {
            AdjacentButton->Unpress();
        }
        else if (!AdjacentButton->bIsPressed)
        {
            AdjacentButton->Press();
        }
    }
    
    return true;
}

void APuzzleButton::SetIsPressed(bool Value)
{
    Super::SetIsPressed(Value);

    NotifyPuzzleStateChanged_Implementation();
}

// IPuzzleCondition implementation
bool APuzzleButton::Evaluate_Implementation()
{
    return bIsPressed;
}

bool APuzzleButton::NotifyPuzzleStateChanged_Implementation()
{
    for (AActor* Puzzle : RegisteredPuzzles)
    {
        IPuzzle::Execute_ConditionStateChanged(Puzzle, this, bIsPressed);

        if (bDebug)
        {
            UE_LOG(LogTemp, Warning, TEXT("APuzzleButton %s: Puzzle %s notified"), *GetName(), *Puzzle->GetName())
        }
    }

    return true;
}

bool APuzzleButton::RegisterPuzzle_Implementation(AActor* Puzzle)
{
    bool bImplementsInterface = Puzzle->GetClass()->ImplementsInterface(UPuzzle::StaticClass());
    if (!bImplementsInterface) { return false; }

    if (!RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Add(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzleButton %s: Puzzle %s registered"), *GetName(), *Puzzle->GetName())
    }

    return true;
}

bool APuzzleButton::UnregisterPuzzle_Implementation(AActor* Puzzle)
{
    bool bImplementsInterface = Puzzle->GetClass()->ImplementsInterface(UPuzzle::StaticClass());
    if (!bImplementsInterface) { return false; }

    if (RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Remove(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzleButton %s: Puzzle %s Unregistered"), *Puzzle->GetName())
    }

    return true;
}

// IPuzzleTrigger implementation
bool APuzzleButton::Trigger_Implementation()
{
    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzleButton %s: Trigger"), *GetName())
    }

    for (AActor* Puzzle : SubscribedPuzzles)
    {
        IPuzzle::Execute_ReactToTrigger(Puzzle); // If the puzzle is subscribed, it implements IPuzzle
    }
    
    return true;
}

bool APuzzleButton::Subscribe_Implementation(AActor* Puzzle)
{
    IPuzzle* PuzzleInterface = Cast<IPuzzle>(Puzzle);
    if (PuzzleInterface)
    {
        SubscribedPuzzles.Add(Puzzle);
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("APuzzleButton %s: Puzzle %s doesn't implement IPuzzle"), *GetName(), *Puzzle->GetName())
        return false;
    }
}

bool APuzzleButton::Unsubscribe_Implementation(AActor* Puzzle)
{
    if (SubscribedPuzzles.Contains(Puzzle))
    {
        SubscribedPuzzles.Remove(Puzzle);
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("APuzzleButton %s: Puzzle %s not subscribed"), *GetName(), *Puzzle->GetName())
        return false;
    }
}
