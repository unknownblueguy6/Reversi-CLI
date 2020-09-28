#pragma once

#include "board.hpp"

enum Cell_States{
	EMPTY,
	WHITE,
	BLACK,
};    

class Cell{
	public:
		Cell();
		void flip();
		friend class Board;

	private:
		Cell_States state;
};

Cell::Cell(){
	state = EMPTY;
}

void Cell::flip(){
	if(state == EMPTY) return;
	if(state == BLACK) {
		state = WHITE;
		return;
	}
	if(state == WHITE){
		state = BLACK;
		return;
	}
}