#include "Game.h"

//Game class
void Game::CreateBoard()                                             //assign default values to the board
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Board[i][j] = '0';
		}
	}
}

void Game::DrawBoard()                                                 //draw board
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << Board[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Game::PlayerInput()
{
	int Requested_Input;
	Input_Begin:
	std::cout << "Please Input a number: ";
	std::cin >> Requested_Input;
		switch (Requested_Input) {
		case 1:
			if (Board[2][0] == '0')
				Board[2][0] = CurrentPlayerCharacter;
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		case 2:
			if (Board[2][1] == '0')
				Board[2][1] = CurrentPlayerCharacter;
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		case 3:
			if (Board[2][2] == '0')
				Board[2][2] = CurrentPlayerCharacter;
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		case 4:
			if (Board[1][0] == '0')
				Board[1][0] = CurrentPlayerCharacter;
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		case 5:
			if (Board[1][1] == '0')
				Board[1][1] = CurrentPlayerCharacter;
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		case 6:
			if (Board[1][2] == '0')
				Board[1][2] = CurrentPlayerCharacter;
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		case 7:
			if (Board[0][0] == '0')
				Board[0][0] = CurrentPlayerCharacter;
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		case 8:
			if (Board[0][1] == '0')
				Board[0][1] = CurrentPlayerCharacter; 
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		case 9:
			if (Board[0][2] == '0')
				Board[0][2] = CurrentPlayerCharacter;
			else { std::cout << "That spot is already taken!\n"; goto Input_Begin; }
			break;
		}
}

bool Game::CheckWinner(char Player_To_Check)
{
	//win conditions that use the 1,1 of the board
	if (Board[1][1] == Player_To_Check) {                          //X00
		if (Board[0][0] == Player_To_Check) {                  //0X0
			if (Board[2][2] == Player_To_Check) {          //00X
				return true;
			}
		}
		if (Board[0][1] == Player_To_Check) {                  //0X0
			if (Board[2][1] == Player_To_Check) {          //0X0
				return true;                           //0X0
			}
		}
		if (Board[1][0] == Player_To_Check) {                  //000
			if (Board[1][2] == Player_To_Check) {          //XXX 
				return true;                           //000
			}
		}
		if (Board[0][2] == Player_To_Check) {                  //00X
			if (Board[2][0] == Player_To_Check) {          //0X0
				return true;                           //X00
			}
		}
	}
	//win conditions through 0,2
	if (Board[0][2] == Player_To_Check) {                      //XXX
		if (Board[0][1] == Player_To_Check) {              //000
			if (Board[0][0] == Player_To_Check) {      //000
				return true;
			}
		}
		if (Board[1][2] == Player_To_Check) {                  //00X
			if (Board[2][2] == Player_To_Check) {          //00X
				return true;                           //00X
			}
		}
	}
	//win condition through 2,0
	if (Board[2][0] == Player_To_Check) {                      //000
		if (Board[2][1] == Player_To_Check) {              //000
			if (Board[2][2] == Player_To_Check) {      //XXX
				return true;
			}
		}
		if (Board[1][0] == Player_To_Check) {                  //X00
			if (Board[0][0] == Player_To_Check) {          //X00
				return true;                           //X00
			}
		}
	}
	else { return false; }
}

void Game::EndingMessage()
{
	std::cout << "Player " << CurrentPlayerCharacter << " won!\n";
}


//PvE class

void PvE::PvELoop()                           //assembly of PvE game loop 
{
	//Game Setup
	srand(time(NULL));
	CreateBoard();
	//Game Loop
	while (Game_Over != true) {
		PlayerInput();
		if (CheckWinner(PlayerCharacter) == true) { Game_Over = true; DrawBoard(); EndingMessage(); goto End; }
		AIChoose('O','X','0');
		DrawBoard();
		if (CheckWinner(AiCharacter) == true) { Game_Over = true; DrawBoard(); AiEnding(); goto End; }
	}
End:
	std::cout << "";
}
void PvE::EvELoop()                           //assembly of PvE game loop 
{
	//Game Setup
	srand(time(NULL));
	CreateBoard();

	DrawBoard();
	//Game Loop
	while (true) {
		AIChoose(PlayerCharacter, AiCharacter, '0');
		if (CheckWinner(PlayerCharacter) == true) { DrawBoard(); EndingMessage(); goto End; }
		AIChoose(AiCharacter, PlayerCharacter, '0');
		std::cout << std::endl;
		if (CheckWinner(AiCharacter) == true) {  DrawBoard(); AiEnding(); goto End; }
		DrawBoard();
	}
End:
	std::cout << "";
}

void PvE::AIChoose(char Character_Self, char Character_Opponent, char Character_Default)
{
	srand(time(NULL));
	int Requested_Input, Behaviour_Controller;
	//immeadiate response
	Behaviour_Controller =  rand() % 8;
	if (Behaviour_Controller != 2) {                                                                                     //random failure to "see" an imminent victory for the human touch   

		if (Board[1][1] == Character_Opponent) {                                                                         //check if middle square is player owned
			if (Board[1][0] == Character_Opponent) {                                                                                      //prevent 000        fill in 1,2
				if (Board[1][2] == Character_Default) { Board[1][2] = Character_Self; goto Chosen; }                                  //        XXX 
			}                                                                                                                             //        000  
											                                                       
			if (Board[1][2] == Character_Opponent) { if (Board[1][0] == Character_Default) { Board[1][0] = Character_Self; goto Chosen; } }  //prevent 000    fill in 1,0
																														                     //        XXX
																														                     //        000
			if (Board[1][0] == Character_Opponent) { if (Board[1][2] == Character_Default) { Board[1][2] = Character_Self; goto Chosen; } }  //prevent 000    fill in 1,2
																														                     //        XXX
																														                     //        000
			if (Board[2][1] == Character_Opponent) { if (Board[0][1] == Character_Default) { Board[0][1] = Character_Self; goto Chosen; } }  //prevent 0X0    fill in 0,1
																														                     //        0X0
																														                     //        0X0
			if (Board[0][1] == Character_Opponent) { if (Board[2][1] == Character_Default) { Board[2][1] = Character_Self; goto Chosen; } }  //prevent 0X0    fill in 2,1
																														                     //        0X0
																														                     //        0X0
			if (Board[2][0] == Character_Opponent) { if (Board[0][2] == Character_Default) { Board[0][2] = Character_Self; goto Chosen; } }  //prevent 00X    fill in 0,2
																														                     //        0X0
																														                     //        X00
			if (Board[0][2] == Character_Opponent) { if (Board[2][0] == Character_Default) { Board[2][0] = Character_Self; goto Chosen; } }  //prevent 00X    fill in 2,0
																														                     //        0X0
																														                     //        X00
			if (Board[2][2] == Character_Opponent) { if (Board[0][0] == Character_Default) { Board[0][0] = Character_Self; goto Chosen; } }  //prevent X00    fill in 0,0
																														                     //        0X0
																														                     //        00X
			if (Board[0][0] == Character_Opponent) { if (Board[2][2] == Character_Default) { Board[2][2] = Character_Self; goto Chosen; } }  //prevent X00    fill in 2,2
																														                     //        0X0
																														                     //        00X
		}

		if (Board[0][1] == Character_Opponent) {                                                                                             //checks for possible winning combinations involving 0,1
			if (Board[0][2] == Character_Opponent) { if (Board[0][0] == Character_Default) { Board[0][0] = Character_Self; goto Chosen; } }  //prevent XXX    fill in 0,0
																														                     //        000
																														                     //        000
			if (Board[0][0] == Character_Opponent) { if (Board[0][2] == Character_Default) { Board[0][2] = Character_Self; goto Chosen; } }  //prevent XXX    fill in 0,2
																														                     //        000
																														                     //        000
		}
		if (Board[2][1] == Character_Opponent) {                                                                            //checks for possible winning combinations involving 2,1
			if (Board[2][2] == Character_Opponent) { if (Board[2][0] == Character_Default) { Board[2][0] = Character_Self; goto Chosen; } }  //prevent 000    fill in 2,0
																														                     //        000
																														                     //        XXX
			if (Board[0][0] == Character_Opponent) { if (Board[0][2] == Character_Default) { Board[0][2] = Character_Self; goto Chosen; } }  //prevent 000    fill in 2,2
																														                     //        000
																														                     //        XXX
		}
		if (Board[1][0] == Character_Opponent) {                                                                            //checks for possible winning combinations involving 1,0
			if (Board[2][0] == Character_Opponent) { if (Board[0][0] == Character_Default) { Board[0][0] = Character_Self; goto Chosen; } }  //prevent X00    fill in 0,0
																														                     //        X00
																														                     //        X00
			if (Board[0][0] == Character_Opponent) { if (Board[2][0] == Character_Default) { Board[2][0] = Character_Self; goto Chosen; } }  //prevent X00    fill in 2,0
																														                     //        X00
																														                     //        X00
		}
		if (Board[1][2] == Character_Opponent) {                                                                            //checks for possible winning combinations involving 1,2
			if (Board[0][2] == Character_Opponent) { if (Board[2][2] == Character_Default) { Board[2][2] = Character_Self; goto Chosen; } }  //prevent 00X    fill in 2,2
																														                     //        00X
																														                     //        00X
			if (Board[2][2] == Character_Opponent) { if (Board[0][2] == Character_Default) { Board[0][2] = Character_Self; goto Chosen; } }  //prevent 00X    fill in 0,2
																														                     //        00X
																														                     //        00X
		}
	}



	//tactics
	if (Board[1][1] == Character_Default) { Board[1][1] = Character_Self; goto Chosen; }                                //1,1
	if (Board[1][1] == Character_Self) {
		if (Board[0][0] != Character_Opponent && Board[2][2] != Character_Opponent) {                   //O00
			if (Board[0][0] == Character_Default) { Board[0][0] = Character_Self; goto Chosen; }    //0O0                 0,0
			if (Board[2][2] == Character_Default) { Board[2][2] = Character_Self; goto Chosen; }    //00O                 2,2
		}
        if (Board[0][0] == Character_Opponent || Board[2][2] == Character_Opponent) {                           //00O
			if (Board[0][2] == Character_Default) { Board[0][2] = Character_Self; goto Chosen; }    //0O0                 0,2
			if (Board[2][0] == Character_Default) { Board[2][0] = Character_Self; goto Chosen; }    //O00                 2,0  
		}
	}
	if(Board[1][1] == Character_Opponent){
		Behaviour_Controller = rand() % 4;
		switch (Behaviour_Controller) {                                                     //makes a random corner of the board ai owned
		case 0:
			if (Board[0][0] == Character_Default) { Board[0][0] = Character_Self; goto Chosen; }   //0,0
			break;
		case 1:
			if (Board[2][0] == Character_Default) { Board[2][0] = Character_Self; goto Chosen; }   //2,0
			break;
		case 2:
			if (Board[0][2] == Character_Default) { Board[0][2] = Character_Self; goto Chosen; }   //0,2
			break;
		case 3:
			if (Board[2][2] == Character_Default) { Board[2][2] = Character_Self; goto Chosen; }   //2,2
			break;
		}
		if (Board[1][0] != Character_Opponent && Board[2][0] != Character_Opponent){                   //O00         
			if (Board[1][0] == Character_Default) { Board[1][0] = Character_Self; goto Chosen; }   //O00          1,0
			if (Board[2][0] == Character_Default) { Board[0][0] = Character_Self; goto Chosen; }   //O00          2,0
		}
		if (Board[0][1] == Character_Opponent || Board[0][2] == Character_Opponent) {                   //OOO
			if (Board[0][2] == Character_Default) { Board[0][2] = Character_Self; goto Chosen; }    //000                 0,2  
			if (Board[0][1] == Character_Default) { Board[0][1] = Character_Self; goto Chosen; }    //000                 0,1
		}
		
	}
	Random:
	Behaviour_Controller = rand() % 9;
	switch (Behaviour_Controller) {
	case 0:
		if (Board[0][0] == Character_Default) { Board[0][0] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	case 1:
		if (Board[0][1] == Character_Default) { Board[0][1] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	case 2:
		if (Board[0][2] == Character_Default) { Board[0][2] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	case 3:
		if (Board[1][0] == Character_Default) { Board[1][0] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	case 4:
		if (Board[1][1] == Character_Default) { Board[1][1] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	case 5:
		if (Board[1][2] == Character_Default) { Board[1][2] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	case 6:
		if (Board[2][0] == Character_Default) { Board[2][0] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	case 7:
		if (Board[2][1] == Character_Default) { Board[2][1] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	case 8:
		if (Board[2][2] == Character_Default) { Board[2][2] = Character_Self; goto Chosen; }
		else { goto Random; }
		break;
	}
Chosen:
	Requested_Input = 0;    //make sure the compiler doesnt screw up regarding goto points followed by brackets
}

void PvE::AiEnding()
{
	std::cout << "The AI won!\n";
}




//PvP class
void PvP::SwitchPlayer()                             //change CurrentPlayerCharacter 
{
	if (CurrentPlayerCharacter == 'X') {
		CurrentPlayerCharacter = 'O';
	}
	else { CurrentPlayerCharacter = 'X'; }
}

void PvP::PvPLoop()
{
	//Game Setup
	CreateBoard();
	//Game Loop
	while (Game_Over != true) {
		DrawBoard();
		PlayerInput();
		if(CheckWinner(CurrentPlayerCharacter) == true){ Game_Over = true; DrawBoard(); EndingMessage(); }
		SwitchPlayer();
	}
}

