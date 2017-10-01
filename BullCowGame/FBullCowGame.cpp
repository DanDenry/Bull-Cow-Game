#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() {
	reset();
}

bool FBullCowGame::IsGameWon() const {
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowercase(Guess)) { // if the guess isn't all lowercase 
		return EGuessStatus::Not_Lowercase; //TODO write a function
	} else if (Guess.length() != GetHiddenWordLenght()) {
		return EGuessStatus::Wrong_Lenght;
	} else {
		return EGuessStatus::ok;
	}
		
}

int32 FBullCowGame::GetMaxTries() const {
	return MyMaxTries;
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
	constexpr int32 MAX_TRIES = 4;
	MyMaxTries = MAX_TRIES;
	const FString HIDDEN_WORD = "dwarfs";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) { return true; } //treat 0 and 1 letter word as isogram
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
		if (!islower(Letter)) { // if not a lowercase letter
			return false;
		}
	}
	return true;
}
