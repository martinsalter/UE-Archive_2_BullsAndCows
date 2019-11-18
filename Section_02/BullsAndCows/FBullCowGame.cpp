#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

FString FBullCowGame::GetHiddenWord() const
{
  return MyHiddenWord;
}

int32 FBullCowGame::HiddenWordLength() const
{
  return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
  return false;
}

void FBullCowGame::Reset()
{
  constexpr int32 MAX_TRIES = 8;
  MyMaxTries = MAX_TRIES;

  const FString MY_HIDDEN_WORD = "planet";
  MyHiddenWord = MY_HIDDEN_WORD;

  MyCurrentTry = 1; // FIXME cannot set private member
}

// Check Length matches hidden word
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
  if (Guess.length() != MyHiddenWord.length()) return EGuessStatus::IncorrectLength;
  if (false) return EGuessStatus::NotIsogram;
  return EGuessStatus::OK;
}

// counts bulls and cows in submitted word, and inceases try# assuming it's a valid guess
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
  MyCurrentTry++;
  FBullCowCount result;
  for (int32 GuessChar = 0; GuessChar < Guess.length(); GuessChar++)
  {
    if (Guess[GuessChar] == MyHiddenWord[GuessChar])
    {
      result.Bulls++;
      continue;
    }
    for (int32 HiddenWordChar = 0; HiddenWordChar < MyHiddenWord.length(); HiddenWordChar++)
    {
      if (MyHiddenWord[HiddenWordChar] == Guess[GuessChar])
      {
        result.Cows++;
        break;
      }
    }
  }
  return result;
}
