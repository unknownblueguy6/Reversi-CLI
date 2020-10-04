#include "board.hpp"

int main(){
	Board board;
	while(true){
		system("clear"); 
		board.draw();
		if(board.isGameOver()){
			//placeholder text
			std::cout << "Game Over\n";
			break;
		}
		board.getMove();
	}
}