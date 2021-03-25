// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWords.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        InitGame();
    }
    else
    {
        ProcessGuess(Input, Lives);
    }
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Welcome to my Bull-Cow Game"));
    PrintLine(TEXT("You have %i number lives"), Lives);
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess"));
    PrintLine(TEXT("Press enter to continue ...."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess, int32 Counter)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!!"));
        EndGame();
        return;
    }
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Length of the character should be %i"), HiddenWord.Len());
        return;
    }
    if (!IsIsogram(Guess))
    {
        PrintLine("No repeating letters, try again!!");
        return;
    }
    --Lives;
    PrintLine("You lost a life");
    if (Lives > 0)
    {
        PrintLine(TEXT("Try Again! You have %i lives left"), Lives);
    }
    else
    {
        PrintLine(TEXT("Hidden word was: %s"), *HiddenWord);
        EndGame();
    }
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> Words) const
{
    TArray<FString> ValidWords;
    for (int32 Index = 0; Index < Words.Num(); Index++)
    {
        if (Words[Index].Len() >= 4 && Words[Index].Len() <= 8 && IsIsogram(Words[Index]))
        {
            ValidWords.Emplace(Words[Index]);
        }
    }
    return ValidWords;
}