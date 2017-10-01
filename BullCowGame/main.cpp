/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class. 
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCGame; //instantiate a new game

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

//the entry point for the application
int main() {
	
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	} while (bPlayAgain);
	return 0;
 }

//introduce the game
void PrintIntro() {
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//Play the game
void PlayGame() {
	BCGame.reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//loop asking for guesses while the game is NOT won
	//and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 

		//Submit valid guess to the game
		FBullCowCount BullCowCount=BCGame.SubmitValidGuesss(Guess);
		
		std::cout << "Bulls =  " << BullCowCount.Bulls;
		std::cout << ".Cows =  " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

//loop continually until the user the user gives a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//Get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
			case EGuessStatus::Wrong_Lenght:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word. \n\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word witout repeating and letters. \n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Make sure you are using lowercase letters. \n\n";
				break;
			default:
				//assume the guess is valid
				break;
		}
	} while (Status != EGuessStatus::ok); // Keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << std::endl;
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y') || (response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well Done! You Win!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}
