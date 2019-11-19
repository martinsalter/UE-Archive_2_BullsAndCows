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
  Invalid_Status,
  OK,
  IncorrectLength,
  NotLowerCase,
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

  FBullCowCount GetBullCowCount(FString);

private:
  int32 MyCurrentTry;
  FString MyHiddenWord;
  bool bGameWon;
  bool IsIsogram(FString) const;
  bool IsLowercase(FString) const;
};