#include "board.hpp"
#include "display.hpp"
#include "computer.hpp"

int main(){
	system("clear");
	showMenu();
	Computer comp; 
	TURN currTurn = PLAYER_ONE;
	Board board;
	while(true){
		system("clear");
		displayBanner(); 
		board.draw();
		if(board.isGameOver()){
			board.declareWinner();
			break;
		}
		if(gameMode == HUMAN) board.getMove();
		else{
			if(currTurn == PLAYER_ONE) board.getMove();
			else comp.makeMove(board);
		}
		currTurn = board.turn;
	}
}