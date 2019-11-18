/*
This is the console executable and makes use of the FBullCowGame class
It acts as the View in the MVC pattern and is responsible for all user interaction
For execution (Controller) and state (Model) see FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCGame;

int main();
void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

int main() 
{
  do
  {
    BCGame.Reset();
    PrintIntro();
    PlayGame();
  } 
  while (AskToPlayAgain());

  return 0;
}


void PrintIntro()
{
  const int32 HIDDEN_WORD_LENGTH = BCGame.HiddenWordLength();
  std::cout << "Welcome To Bulls And Cows: A fun word game!\n";
  std::cout << "Can you guess the " << HIDDEN_WORD_LENGTH << "-letter Isogram I'm thinking of?\n";
  std::cout << std::endl;
}

void PlayGame()
{
  int32 MaxTries = BCGame.GetMaxTries();

  //for (int32 count = 0; count < MaxTries; count++)
  while(BCGame.GetCurrentTry() <= MaxTries)
  {
    std::cout << "You have " << MaxTries-BCGame.GetCurrentTry()+1 << " tries remaining\n";
    FText Guess = GetGuess();    // Get Player guess

    // If guess is correct, break loop and win game    
    if (Guess == BCGame.GetHiddenWord())
    {
      std::cout << "Well Done! " << BCGame.GetHiddenWord() << " is the hidden word.\n";
      break;
    }

    // Check validity of guess and prompt again if not valid
    EGuessStatus GuessValidity = BCGame.CheckGuessValidity(Guess);
    if (GuessValidity != EGuessStatus::OK)
    {
      switch (GuessValidity)
      {
        case EGuessStatus::IncorrectLength:
          std::cout << "Invalid guess. It must be a " << BCGame.HiddenWordLength() << " letter word.";
          break;
        case EGuessStatus::NotIsogram:
          std::cout << "Invalid guess. It must be an isogram (no repeating letters)";
          break;
      default:
        break;
      }
      std::cout << "\n\n";
      continue;
    }
   // Otherwise, submit Valid guess and display Bulls and Cows

      FBullCowCount result = BCGame.SubmitGuess(Guess);
      std::cout << Guess << " contains Bulls: " << result.Bulls << "  Cows: " << result.Cows << std::endl << std::endl;
      continue;
    

    // If not, display try again message

  }
}

FText GetGuess()
{
  int32 CurrentTry = BCGame.GetCurrentTry();
  std::cout << "Enter your guess: ";
  FText Guess = "";

  std::getline(std::cin, Guess);
  return Guess;
}

bool AskToPlayAgain()
{
  std::cout << "Play Again? (Y/N): ";
  FText Response = "";
  std::getline(std::cin, Response);
  return (Response[0] == 'Y') || (Response[0] == 'y');
}