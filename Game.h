//header file for the different classes

#pragma once
#include <iostream>
#include <ctime>
class Game {
protected:
	//universal variables
	char Board[3][3];                             //the board
	char CurrentPlayerCharacter = 'X';            //contains the character associated with the current player
	bool Game_Over = false;                       //Game state

	//universal functions
	void CreateBoard();                           //creates default board setup i.e all 0;
	void DrawBoard();                             //draws board
	void PlayerInput();                           //input system. does: 1. Ask for location 2. Confirm if input is valid 3. Based on that ask for another input or make the change to the board
	bool CheckWinner(char Player_To_Check);       //returns whether the given character has won
	void EndingMessage();                         //prints out default ending message
};

//PvE class, functions specifically required for player versus comptuer
class PvE : public Game {
public:
	void PvELoop();                                                                         //pve game
	void EvELoop();                                                                         //eve game
private:
	char PlayerCharacter = 'X';                                                             //standard character for the player
	char AiCharacter = 'O';                                                                 //standard character for the ai
	void AIChoose(char Character_Self, char Character_Opponent, char Character_Default);    //make ai choose spot
	void AiEnding();                                                                        //print some ending text saying the ai won
};

//PvP class, functions specifically required for player versus player
class PvP : public Game {
public:
	void PvPLoop();                             //pvp game
private:
	void SwitchPlayer();                        //change CurrentPlayerCharacter
};
