// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleButton.h"

bool APuzzleButton::Evaluate_Implementation()
{
    return bIsPressed;
}

void APuzzleButton::Press()
{
    Super::Press();

    Trigger_Implementation();
}

bool APuzzleButton::Interact_Implementation()
{
    Super::Interact_Implementation();
    
    for (auto &&AjdacentButton : AdjacentButtons)
    {
        if (AjdacentButton->bIsPressed)
        {
            AjdacentButton->Unpress();
        }
        else
        {
            AjdacentButton->Press();
        }
    }
    
    return true;
}

bool APuzzleButton::Trigger_Implementation()
{
    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzleButton %s: Triggered."), *GetName())
    }

    for (AActor* Puzzle : SubscribedPuzzles)
    {
        IPuzzle::Execute_Trigger(Puzzle); // If the puzzle is subscribed, it implements IPuzzle
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
        UE_LOG(LogTemp, Error, TEXT("APuzzleButton %s: Puzzle %s doesn't implement IPuzzle."), *GetName(), *Puzzle->GetName());
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
        UE_LOG(LogTemp, Error, TEXT("APuzzleButton %s: Puzzle %s not subscribed."), *GetName(), *Puzzle->GetName());
        return false;
    }
}
