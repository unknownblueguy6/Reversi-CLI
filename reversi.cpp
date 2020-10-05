#include "board.hpp"
#include "display.hpp"
int main(){
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