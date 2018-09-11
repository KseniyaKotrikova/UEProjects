#pragma once
#include<iostream>
#include<string>
#include "FBullCowGame.h"
#include "main.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;
//function prototypes
void PlayGame();
void PrintIntro();
FText GetValidGuess();
bool AskToPlayAgain();
void printGameSummary();
FBullCowGame BCGame;//instantiate a new game, whih we re-use across plays

void PrintIntro() {
	//introduce the game
	
	std::cout << "Welcome to Bulls and Cows, a fun word game.";
	int32 WordLength = BCGame.GetHiddenWordLength();
	std::cout << " Can you guess the  " << WordLength;
	std::cout << " letter isogram\n" << std::endl;
	std::cout << std::endl;
	return;
}
//loop continually untill user gives a valid guess
FText GetValidGuess() //TODO change to GetValid guess
{
	FText Guess = "";
	EGuessStatus Status=EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry<<" of " << BCGame.GetMaxTries()<<". Enter your guess: ";
		
		getline(std::cin, Guess);

		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an non-repeating letter WORD.\n\n";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;

		default:
			//assume the guess is valid
			break;
		}
		
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);//keep looping untill we get valid input
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0]=='y')|| (Response[0] == 'Y');


	
}

void printGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Well Done! YOU WIN! Congratulations!" << std::endl;
	}
	else {
		std::cout << "Try you luck again later!" << std::endl;
	}
}

void PlayGame()
{
	//BCGame.Reset();
	int32 MaxTries=BCGame.GetMaxTries();
	

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries)
	 {
		FText Guess =GetValidGuess();//TODO make loop checking valid

		

		//submit valid guess to the game
	 FBullCowCount BullCowCount=BCGame.SubmitGuess(Guess);
		//print number of bulls & cows

	 std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows <<"\n\n";
	

		
	}
	printGameSummary();
	//TODO game summary
}
int main() {
	//std::cout << BCGame.GetCurrentTry();

	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		//TODO game summary
		bPlayAgain= AskToPlayAgain();
	} while (bPlayAgain);


	return 0;
}