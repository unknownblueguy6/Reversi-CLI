#include "board.hpp"
#include "display.hpp"

int main(){
	system("clear");
	showMenu();

	Board board;
	while(true){
		system("clear");
		displayBanner(); 
		board.draw();
		if(board.isGameOver()){
			board.declareWinner();
			break;
		}
		board.getMove();
	}
}