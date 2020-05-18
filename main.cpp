#include<iostream>
#include"Game.h"


int main(){
	int Mode;
	char Play_Again;
	PvE GameE;
	PvP GameP;
	Start:
	std::cout << "Choose which mode you want to play:\n 1)PvE\n 2)PvP\n 3)EvE Skynet mode\n";    
	std::cin >> Mode;
	//mode selection, either play with another person or with the computer
	switch(Mode){
	case 1:
		GameE.PvELoop();
		break;
	case 2:
		GameP.PvPLoop();
		break;
	case 3:
		GameE.EvELoop();
		break;
	}
	std::cout << "Would you like to play again?(y/n)\n";
	std::cin >> Play_Again;
	if (Play_Again == 'Y' || Play_Again == 'y')
		goto Start;


	//wait for use input before closing
	std::cin.get();
	std::cin.get();
	return 0;
}