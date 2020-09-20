#pragma once

#include <vector>
#include <iostream>
#include <utility>
#include "init.hpp"
#include "cell.hpp"
#include "colour.hpp"

const int LENGTH = 8;
const int BREADTH = 8;

enum TURN{
	PLAYER_ONE,
	PLAYER_TWO
};

class Board
{
	public:
		Board();
		void draw();
		void getMove();
		void placeDisk();
		bool isValidMove();
		int noOfFlippedDiscs(Cell_States, int, int, int, int, int);
		bool isAtCurrPos(int, int);
		bool isValidIndex(int , int);
		
	private:
		int l;
		int b;
		int x;
		int y;
		TURN turn;
		COLOUR cursorCol;
		std::vector<std::vector<Cell>> cells;
};

Board::Board(){
	l = LENGTH;
	b = BREADTH;
	turn = PLAYER_ONE;
	cells = std::vector<std::vector<Cell>>(b, std::vector<Cell>(l, Cell()));
	x = 1;
	y = 1;
	cursorCol = RED;
	cells[(l-1)/2][(b-1)/2].state = WHITE;
	cells[l/2][(b-1)/2].state = BLACK;
	cells[(l-1)/2][b/2].state = BLACK;
	cells[l/2][b/2].state = WHITE;
}

void Board::draw(){
	std::vector<std::string> buf;
	std::string s = "";
	for(int j = 0; j < l; ++j){
		if(j == 0){
			s += "┏";
				for(int i = 0; i < b-1; ++i){
					if(isAtCurrPos(j, i)) s += cursorCol + "━━━" + RESET +"┳";	
					else s += "━━━┳";
				}
				if(isAtCurrPos(j, b-1)) s += cursorCol + "━━━" + RESET +"┓\n";
				else s += "━━━┓\n"; 
				buf.push_back(s);
				s = "";
		}

		if(j > 0 && j < l){
			s += "┣";
			for(int i = 0; i < b-1; ++i){
				if(isAtCurrPos(j-1, i) || isAtCurrPos(j, i)) s += cursorCol + "━━━" + RESET + "╋";
				else s += "━━━╋";
			}
			if(isAtCurrPos(j-1, b-1)|| isAtCurrPos(j, b-1)) s += cursorCol + "━━━" + RESET +"┫\n";
			else s += "━━━┫\n"; 
			buf.push_back(s);
			s = "";
		}

		if(isAtCurrPos(j, 0)) s += cursorCol + "┃" + RESET;	
		else s += "┃";

		for(int i = 0; i < b; ++i){
			switch(cells[j][i].state){
			case EMPTY:
				s += "  ";
				break;
			case BLACK:
				s += "⚫️";	
				break;
			case WHITE:
				s += "⚪";
				break;
			}
			if(isAtCurrPos(j, i) || isAtCurrPos(j, i+1)) s += cursorCol + " ┃" + RESET;
			else s += " ┃";
		}
		s += "\n";
		buf.push_back(s);
		s = "";
		
		if(j == l-1){
			s += "┗";
			for(int i = 0; i < b-1; ++i){
				if(isAtCurrPos(j, i)) s += cursorCol + "━━━" + RESET + "┻";
				else s += "━━━┻";
			}
			if(isAtCurrPos(j, b-1)) s += cursorCol + "━━━" + RESET + "┛\n";
			else s += "━━━┛\n"; 
			buf.push_back(s);
			s = "";
		}
	}
	for(auto str: buf) std::cout << str;
}

void Board::getMove(){
    KEY k = getKey();
    switch (k){
		case K_UP:
			if(isValidIndex(y-1, x)) --y;
			if(isValidMove()) cursorCol = GREEN;
			else cursorCol = RED;
			return;

		case K_DOWN:
			if(isValidIndex(y+1, x)) ++y;
			if(isValidMove()) cursorCol = GREEN;
			else cursorCol = RED;
			return;

		case K_LEFT:
			if(isValidIndex(y, x-1)) --x;
			if(isValidMove()) cursorCol = GREEN;
			else cursorCol = RED;
			return;

		case K_RIGHT:
			if (isValidIndex(y, x+1)) ++x;
			if(isValidMove()) cursorCol = GREEN;
			else cursorCol = RED;
			return;

		case K_SPACE: //placeholder
			if(cursorCol == GREEN) placeDisk();
			return;
	}
}

void Board::placeDisk(){
	if(turn == PLAYER_ONE){
		cells[y][x].state = BLACK;
		turn = PLAYER_TWO;
	}
	else{
		cells[y][x].state = WHITE;
		turn = PLAYER_ONE;
	}

}

bool Board::isValidMove(){
	if(cells[y][x].state != EMPTY) return false;
	
	Cell_States s = turn == PLAYER_ONE ? BLACK : WHITE;
	std::vector<bool> dirs;
	
	for(int j = -1; j <= 1; ++j){
		for(int i = -1; i <= 1; ++i){
			
			if(j == 0 && i == 0){
				dirs.push_back(false);
				continue;
			}
			
			if(isValidIndex(y+j, x+i)){
				if(cells[y+j][x+i].state == EMPTY) dirs.push_back(false);
				else if(cells[y+j][x+i].state == s) dirs.push_back(false);
				else dirs.push_back(true);  
			}

			else dirs.push_back(false);
		}
	}

	int search_dir_x, search_dir_y;

	for(int k = 0; k < 9; ++k){
		if(dirs[k]){

			switch(k){
				case 0:
				case 1:
				case 2:
					search_dir_y = -1;
					break;
				case 3:
				case 5:
					search_dir_y =  0;
					break;
				case 6:
				case 7:
				case 8:
					search_dir_y = +1;
					break;
			}

			switch(k){
				case 0:
				case 3:
				case 6:
					search_dir_x = -1;
					break;
				case 1:
				case 7:
					search_dir_x =  0;
					break;
				case 2:
				case 5:
				case 8:
					search_dir_x = +1;
					break;
			}

			if(noOfFlippedDiscs(s, y+search_dir_y, x+search_dir_x, search_dir_y, search_dir_x, 0) > 0) return true;
		}
	}
	return false;
}

int Board::noOfFlippedDiscs(Cell_States state, int curr_y, int curr_x, int dir_y, int dir_x, int flippedDiscs){
	if(!isValidIndex(curr_y, curr_x)) return 0;
	if(cells[curr_y][curr_x].state == EMPTY) return 0;
	if(cells[curr_y][curr_x].state == state) return flippedDiscs;
	else return noOfFlippedDiscs(state, curr_y + dir_y, curr_x + dir_x, dir_y, dir_x, flippedDiscs + 1);
}

inline bool Board::isValidIndex(int j, int i){
	if(j <  0 || i <  0) return false;
	if(j >= l || i >= b) return false;
	return true;
}

inline bool Board::isAtCurrPos(int j, int i){
	return i == x && j == y;
} 