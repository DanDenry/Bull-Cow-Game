#pragma once
#include <string>

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
	void reset(); //TODO make a more rich return value,

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};