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
FText GetValidGuess();
void EndGame();
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
  while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
  {
    std::cout << "You have " << MaxTries-BCGame.GetCurrentTry()+1 << " tries remaining\n";
    FText Guess = GetValidGuess(); // Get Player guess (keep asking until valid guess given)
    
    // Submit Valid guess and display Bulls and Cows
    FBullCowCount result = BCGame.GetBullCowCount(Guess);
    std::cout << Guess << " contains Bulls: " << result.Bulls << "  Cows: " << result.Cows << std::endl << std::endl;
  }
  EndGame();
}

FText GetValidGuess()
{
  EGuessStatus Status = EGuessStatus::Invalid_Status;
  FText Guess = "";
  do{
    std::cout << "Enter your guess: ";
    std::getline(std::cin, Guess);

    // Check validity of guess and prompt again if not valid
    Status = BCGame.CheckGuessValidity(Guess);
    switch (Status)
    {
    case EGuessStatus::IncorrectLength:
      std::cout << "Invalid guess. It must be a " << BCGame.HiddenWordLength() << " letter word.\n\n";
      break;
    case EGuessStatus::NotLowerCase:
      std::cout << "Invalid guess. It must be all lower case.\n\n";
      break;
    case EGuessStatus::NotIsogram:
      std::cout << "Invalid guess. It must be an isogram (no repeating letters)\n\n";
      break;
    default:
      break;
    }
  } while (Status != EGuessStatus::OK); // Loop until valid guess is made
  return Guess;
}

void EndGame()
{
  if (BCGame.IsGameWon())
  {
    std::cout << "Well Done! " << BCGame.GetHiddenWord() << " is the hidden word.\n";
  }
  else
  {
    std::cout << "Unlucky. You ran out of tries\n";
  }
}

bool AskToPlayAgain()
{
  std::cout << "Play Again with the same word? (Y/N): ";
  FText Response = "";
  std::getline(std::cin, Response);
  return (Response[0] == 'Y') || (Response[0] == 'y');
}