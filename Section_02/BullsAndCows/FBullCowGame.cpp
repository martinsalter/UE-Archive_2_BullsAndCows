#include "FBullCowGame.h"
#include <map>
#define TMap std::map
#define int32 int

using FString = std::string;
// using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetMaxTries() const
{
  /*  ALTERNATIVE
    TMap<int32, int32> MaxTries = { {3,4}, {4,7}, {5,10}, {6,15}, {7,18}, {8,20} };
    return MaxTries[HiddenWordLength()];
  */
  return (int32)((HiddenWordLength() * HiddenWordLength()) / 2);
}

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
  return bGameWon;
}

void FBullCowGame::Reset()
{
  const FString MY_HIDDEN_WORD = "plane";  // TODO Choose new word randomly from list
  MyHiddenWord = MY_HIDDEN_WORD;

  MyCurrentTry = 1;

  bGameWon = false;
}

// Check Length matches hidden word
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
  if (Guess.length() != MyHiddenWord.length()) return EGuessStatus::IncorrectLength;
  if (!IsLowercase(Guess)) return EGuessStatus::NotLowerCase;
  if (!IsIsogram(Guess)) return EGuessStatus::NotIsogram;
  return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::GetBullCowCount(FString Guess)
{
  MyCurrentTry++;
  FBullCowCount result;
  for (int32 GuessChar = 0; GuessChar < (int32)Guess.length(); GuessChar++)
  {
    if (Guess[GuessChar] == MyHiddenWord[GuessChar])
    {
      result.Bulls++;
      continue;
    }
    for (int32 HiddenWordChar = 0; HiddenWordChar < (int32)MyHiddenWord.length(); HiddenWordChar++)
    {
      if (MyHiddenWord[HiddenWordChar] == Guess[GuessChar])
      {
        result.Cows++;
        break;
      }
    }
  }
  if (result.Bulls == Guess.length()) bGameWon = true;
  return result;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
  if (Word.length() < 2) return true;

  TMap<char, bool> LetterSeen;
  for (char Letter: Word)
  {
    Letter = tolower(Letter);
    if (LetterSeen[Letter]) return false;
    else LetterSeen[Letter] = true;
  }

  return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
  if (Word.length() < 2) return true;
  for (auto Letter : Word)
  {
    if (!islower(Letter)) return false;
  }

  return true;
}