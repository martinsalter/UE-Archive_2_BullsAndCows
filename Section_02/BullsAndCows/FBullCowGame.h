#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
  int32 Bulls = 0;
  int32 Cows = 0;
};

enum class EGuessStatus
{
  OK,
  IncorrectLength,
  NotIsogram
};

class FBullCowGame
{
public:
  FBullCowGame();

  int32 GetMaxTries() const;
  int32 GetCurrentTry() const;
  FString GetHiddenWord() const;
  int32 HiddenWordLength() const;

  bool IsGameWon() const;
  void Reset();
  EGuessStatus CheckGuessValidity(FString) const;

  FBullCowCount SubmitGuess(FString);

private:
  int32 MyCurrentTry;
  int32 MyMaxTries;
  FString MyHiddenWord;
};