#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map // to make syntax Unreal friendly

FBullCowGame::FBullCowGame() {
	reset();
}

bool FBullCowGame::IsGameWon() const {
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowercase(Guess)) { 
		return EGuessStatus::Not_Lowercase; 
	} else if (Guess.length() != GetHiddenWordLenght()) {
		return EGuessStatus::Wrong_Lenght;
	} else {
		return EGuessStatus::ok;
	}
		
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,16}, {6,16} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 FBullCowGame::HowManyBulls() const {
	return 0;
}

int32 FBullCowGame::HowManyCows() const {
	return 0;
}

int32 FBullCowGame::GetHiddenWordLenght() const {
	return MyHiddenWord.length();
}

// receives a VALID guess, incriments turn. and returns count.
FBullCowCount FBullCowGame::SubmitValidGuesss(FString Guess) {
	
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); //assuming same lenght as guess

	//loop throgh all letters in the hidden word

	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLenght; GChar++) {
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
			//if they're in the same place
				if (MHWChar == GChar) {
					//incriment bulls 
					BullCowCount.Bulls++;
				} else {
					//incriment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLenght) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon == false;
	}
	return BullCowCount;
}


void FBullCowGame::reset() {
	const FString HIDDEN_WORD = "dwarfs"; // This must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) { return true; } 
	TMap <char, bool> LetterSeen; //setup our map
	for (auto Letter : Word) { //for all letter of the word
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) { //if the letter is in the map
			return false;
		}
		else {
			LetterSeen[Letter] = true; //add the letter to the map as seen
		}
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) { 
		if (!islower(Letter)) { 
			return false;
		}
	}
	return true;
}
