#include "board.hpp"

int main(){
	Board board;
	while(true){
		system("clear"); 
		board.draw();
		board.getMove();
	}
}