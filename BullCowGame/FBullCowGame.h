/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	ok,
	Not_Isogram,
	Wrong_Lenght,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor
	
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 HowManyBulls() const;
	int32 HowManyCows() const;
	int32 GetHiddenWordLenght() const;

	FBullCowCount SubmitValidGuesss(FString);
	void reset(); 

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
