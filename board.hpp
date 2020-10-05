#pragma once

#include <vector>
#include <iostream>
#include <utility>
#include "init.hpp"
#include "cell.hpp"
#include "colour.hpp"
#include "display.hpp"

const int LENGTH =  8;
const int BREADTH = 8;
const int PADDING = 4;

enum TURN{
	PLAYER_ONE,
	PLAYER_TWO
};

class Board
{
	public:
		Board();
		void draw();
		void updateBoardOntoBuffer();
		void getMove();
		void placeDisk();
		bool isValidMove(int, int);
		int  noOfFlippedDiscs(Cell_States, int, int, int, int, int);
		void flipDiscs(Cell_States, int, int, int, int);
		bool isGameOver();
		void declareWinner();
		bool isNeighbouringDisk(int, int);
		bool isAtCurrPos(int, int);
		bool isValidIndex(int , int);
		int  setDirX(int);
		int  setDirY(int);
		
	private:
		int l;
		int b;
		int x;
		int y;
		int noOfBlackDisks;
		int noOfWhiteDisks;
		TURN turn;
		COLOUR cursorCol;
		std::vector<std::string> buf;
		std::vector<std::vector<Cell>> cells;
		bool dirs[9];
};

Board::Board(){
	l = LENGTH;
	b = BREADTH;
	turn = PLAYER_ONE;
	cells = std::vector<std::vector<Cell>>(b, std::vector<Cell>(l, Cell()));
	x = 1;
	y = 1;
	cursorCol = RED;
	noOfBlackDisks = noOfWhiteDisks = 2;
	cells[(l-1)/2][(b-1)/2].state = WHITE;
	cells[l/2][(b-1)/2].state = BLACK;
	cells[(l-1)/2][b/2].state = BLACK;
	cells[l/2][b/2].state = WHITE;
}

void Board::updateBoardOntoBuffer(){
	std::string s = std::string(PADDING, ' ');
	for(int j = 0; j < l; ++j){
		if(j == 0){
			s += "┏";
				for(int i = 0; i < b-1; ++i){
					if(isAtCurrPos(j, i)) s += cursorCol + "━━━" + RESET +"┳";	
					else s += "━━━┳";
				}
				if(isAtCurrPos(j, b-1)) s += cursorCol + "━━━" + RESET +"┓";
				else s += "━━━┓"; 
				buf.push_back(s);
				s = std::string(PADDING, ' ');
		}

		if(j > 0 && j < l){
			s += "┣";
			for(int i = 0; i < b-1; ++i){
				if(isAtCurrPos(j-1, i) || isAtCurrPos(j, i)) s += cursorCol + "━━━" + RESET + "╋";
				else s += "━━━╋";
			}
			if(isAtCurrPos(j-1, b-1)|| isAtCurrPos(j, b-1)) s += cursorCol + "━━━" + RESET +"┫";
			else s += "━━━┫"; 
			buf.push_back(s);
			s = std::string(PADDING, ' ');
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
		buf.push_back(s);
		s = std::string(PADDING, ' ');
		
		if(j == l-1){
			s += "┗";
			for(int i = 0; i < b-1; ++i){
				if(isAtCurrPos(j, i)) s += cursorCol + "━━━" + RESET + "┻";
				else s += "━━━┻";
			}
			if(isAtCurrPos(j, b-1)) s += cursorCol + "━━━" + RESET + "┛";
			else s += "━━━┛"; 
			buf.push_back(s);
			s = std::string(PADDING, ' ');
		}
	}
	//for(auto str: buf) std::cout << str;
	//std::cout << noOfWhiteDisks << " " << noOfBlackDisks << "\n"; //debugging code
}

void Board::draw(){
	buf.clear();
	updateBoardOntoBuffer();
	displayControls(buf);
	for(auto str: buf) std::cout << str << "\n";
}

void Board::getMove(){
    KEY k = getKey();
    switch (k){
		case K_UP:
			if(isValidIndex(y-1, x)) --y;
			if(isValidMove(y, x)) cursorCol = GREEN;
			else cursorCol = RED;
			return;

		case K_DOWN:
			if(isValidIndex(y+1, x)) ++y;
			if(isValidMove(y, x)) cursorCol = GREEN;
			else cursorCol = RED;
			return;

		case K_LEFT:
			if(isValidIndex(y, x-1)) --x;
			if(isValidMove(y, x)) cursorCol = GREEN;
			else cursorCol = RED;
			return;

		case K_RIGHT:
			if (isValidIndex(y, x+1)) ++x;
			if(isValidMove(y, x)) cursorCol = GREEN;
			else cursorCol = RED;
			return;

		case K_SPACE:
			if(cursorCol == GREEN){
				placeDisk();
				for(int k = 0; k < 9; ++k){
					if(dirs[k]){
						int dir_y = setDirY(k);
						int dir_x = setDirX(k);
						flipDiscs(cells[y][x].state, y+dir_y, x+dir_x, dir_y, dir_x);
					}
				}
				cursorCol = RED;
			}
			return;
	}
}

void Board::placeDisk(){
	if(turn == PLAYER_ONE){
		cells[y][x].state = BLACK;
		++noOfBlackDisks;
		turn = PLAYER_TWO;
	}
	else{
		cells[y][x].state = WHITE;
		++noOfWhiteDisks;
		turn = PLAYER_ONE;
	}

}

bool Board::isValidMove(int y_pos, int x_pos){
	if(cells[y_pos][x_pos].state != EMPTY) return false;
	if(! isNeighbouringDisk(y_pos, x_pos)) return false;
	
	Cell_States s = turn == PLAYER_ONE ? BLACK : WHITE;
	int count = 0;
	bool dirs_copy[9];

	for(int j = -1; j <= 1; ++j){
		for(int i = -1; i <= 1; ++i){
			
			if(j == 0 && i == 0){
				dirs_copy[count++] = false;
				continue;
			}
			
			if(isValidIndex(y_pos+j, x_pos+i)){
				if(cells[y_pos+j][x_pos+i].state == EMPTY) dirs_copy[count] = false;
				else if(cells[y_pos+j][x_pos+i].state == s) dirs_copy[count] = false;
				else dirs_copy[count] = true;  
			}

			else dirs_copy[count] = false;

			++count;
		}
	}

	int search_dir_x, search_dir_y;
	bool flag = false;
	for(int k = 0; k < 9; ++k){
		if(dirs_copy[k]){
			search_dir_y = setDirY(k);
			search_dir_x = setDirX(k);
			if(noOfFlippedDiscs(s, y_pos+search_dir_y, x_pos+search_dir_x, search_dir_y, search_dir_x, 0) > 0){
				flag = true;
			}
			else dirs_copy[k] = false;
		}
	}
	if(isAtCurrPos(y_pos, x_pos)){
		for(int i = 0; i < 9; ++i){
			dirs[i] = dirs_copy[i];
		}
	}
	return flag;
}

int Board::noOfFlippedDiscs(Cell_States state, int curr_y, int curr_x, int dir_y, int dir_x, int flippedDiscs = 0){
	if(!isValidIndex(curr_y, curr_x)) return 0;
	if(cells[curr_y][curr_x].state == EMPTY) return 0;
	if(cells[curr_y][curr_x].state == state) return flippedDiscs;
	else return noOfFlippedDiscs(state, curr_y + dir_y, curr_x + dir_x, dir_y, dir_x, flippedDiscs + 1);
}

void Board::flipDiscs(Cell_States state, int curr_y, int curr_x, int dir_y, int dir_x){
	if(cells[curr_y][curr_x].state == state) return;
	cells[curr_y][curr_x].flip();
	if(state == WHITE){
		++noOfWhiteDisks;
		--noOfBlackDisks;
	}
	else if(state == BLACK){
		++noOfBlackDisks;
		--noOfWhiteDisks;
	}
	flipDiscs(state, curr_y + dir_y, curr_x + dir_x, dir_y, dir_x);
}

bool Board::isGameOver(){
	for(int j = 0; j < l; ++j){
		for(int i = 0; i < b; ++i){
			if(isValidMove(j, i)) return false;
		}
	}
	return true;
}

void Board::declareWinner(){
	std::cout << "\n";
	std::string winner_text;
	if(noOfBlackDisks > noOfWhiteDisks) winner_text = "Player One is the Winner!";
	else if(noOfWhiteDisks > noOfBlackDisks) winner_text = "Player Two is the Winner!";
	else winner_text = "It is a Tie!";
	std::cout << GREEN << winner_text << "\n" << RESET;
}

bool Board::isNeighbouringDisk(int y_pos, int x_pos){
	for(int j = -1; j <= 1; ++j){
		for(int i = -1; i <= 1; ++i){
			if (j == 0 && i == 0) continue;
			if (!isValidIndex(y_pos+j, x_pos+i)) continue;
			if (cells[y_pos+j][x_pos+i].state != EMPTY) return true;
		}
	}
	return false;
}

inline int Board::setDirY(int k){
	switch(k){
		case 0:
		case 1:
		case 2:
			return -1;
		case 3:
		case 5:
			return  0;
		case 6:
		case 7:
		case 8:
			return +1;
	}
	return 0;
}


inline int Board::setDirX(int k){
	switch(k){
		case 0:
		case 3:
		case 6:
			return -1;
		case 1:
		case 7:
			return  0;
		case 2:
		case 5:
		case 8:
			return +1;
	}
	return 0;
}

inline bool Board::isValidIndex(int j, int i){
	if(j <  0 || i <  0) return false;
	if(j >= l || i >= b) return false;
	return true;
}

inline bool Board::isAtCurrPos(int j, int i){
	return i == x && j == y;
} 