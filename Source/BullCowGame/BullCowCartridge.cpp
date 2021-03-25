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
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame()
{
    TArray<FString> Isograms = GetValidWords(Words);
    const int32 RandomIndex = FMath::RandRange(0, Isograms.Num() - 1);
    HiddenWord = Isograms[RandomIndex];
    Lives = HiddenWord.Len()*2;
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

void UBullCowCartridge::ProcessGuess(const FString &Guess)
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
    if (Lives <= 0)
    {
        PrintLine(TEXT("Hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
    int32 Bulls, Cows;
    GetBullCows(Guess,Bulls,Cows);
    PrintLine(TEXT("You have %i Bulls and %i Cows"),Bulls,Cows);
    PrintLine(TEXT("Try Again! You have %i lives left"), Lives);
    
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordList) const
{
    TArray<FString> ValidWords;
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount=0;
    CowCount=0;
    for (int32 GuessIndex=0; GuessIndex<Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex]==HiddenWord[GuessIndex]){
            BullCount++;
            continue;
        }
        for (int32 HiddenIndex=0; HiddenIndex<HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex]==HiddenWord[HiddenIndex])
            {
                CowCount++;
                break;
            }
        }
    }
}