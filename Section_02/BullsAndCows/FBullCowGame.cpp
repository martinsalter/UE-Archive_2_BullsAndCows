#include "FBullCowGame.h"
#include <map>
#define TMap std::map
#define int32 int

using FString = std::string;
// using int32 = int;

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
  return bGameWon;
}

void FBullCowGame::Reset()
{
  const FString MY_HIDDEN_WORD = "planet";  // TODO Choose new word randomly from list
  MyHiddenWord = MY_HIDDEN_WORD;

  constexpr int32 MAX_TRIES = 8;  // TODO Set number of tries relative to word length
  MyMaxTries = MAX_TRIES;

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

// counts bulls and cows in submitted word, and inceases try# assuming it's a valid guess
FBullCowCount FBullCowGame::GetBullCowCount(FString Guess)
{
  MyCurrentTry++;
  FBullCowCount result;
  for (int GuessChar = 0; GuessChar < Guess.length(); GuessChar++)
  {
    if (Guess[GuessChar] == MyHiddenWord[GuessChar])
    {
      result.Bulls++;
      continue;
    }
    for (int HiddenWordChar = 0; HiddenWordChar < MyHiddenWord.length(); HiddenWordChar++)
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