#pragma once

#include <vector>
#include <iostream>
#include <utility>
#include "init.hpp"
#include "cell.hpp"
#include "colour.hpp"

const unsigned LENGTH = 8;
const unsigned BREADTH = 8;


class Board
{
	public:
		Board();
		void draw();
		bool isAtCurrPos(int, int);
		void getMove();
		
	private:
		unsigned l;
		unsigned b;
		unsigned x;
		unsigned y;
		std::vector<std::vector<Cell>> cells;
};

Board::Board(){
	l = LENGTH;
	b = BREADTH;
	cells = std::vector<std::vector<Cell>>(b, std::vector<Cell>(l, Cell()));
	x = (l-1)/2;
	y = (b-4)/2;
	cells[(l-1)/2][(b-1)/2].state = WHITE;
	cells[l/2][(b-1)/2].state = BLACK;
	cells[(l-1)/2][b/2].state = BLACK;
	cells[l/2][b/2].state = WHITE;
}

void Board::draw(){
	std::vector<std::string> buf;
	std::string s = "";
	for(unsigned j = 0; j < l; ++j){
		if(j == 0){
			s += "┏";
				for(unsigned i = 0; i < b-1; ++i){
					if(isAtCurrPos(j, i)) s += blue_fg + "━━━" + reset +"┳";	
					else s += "━━━┳";
				}
				if(isAtCurrPos(j, b-1)) s += blue_fg + "━━━" + reset +"┓\n";
				else s += "━━━┓\n"; 
				buf.push_back(s);
				s = "";
		}

		if(j > 0 && j < l){
			s += "┣";
			for(unsigned i = 0; i < b-1; ++i){
				if(isAtCurrPos(j-1, i) || isAtCurrPos(j, i)) s += blue_fg + "━━━" + reset + "╋";
				else s += "━━━╋";
			}
			if(isAtCurrPos(j-1, b-1)|| isAtCurrPos(j, b-1)) s += blue_fg + "━━━" + reset +"┫\n";
			else s += "━━━┫\n"; 
			buf.push_back(s);
			s = "";
		}

		if(isAtCurrPos(j, 0)) s += blue_fg + "┃" + reset;	
		else s += "┃";

		for(unsigned i = 0; i < b; ++i){
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
			if(isAtCurrPos(j, i) || isAtCurrPos(j, i+1)) s += blue_fg + " ┃" + reset;
			else s += " ┃";
		}
		s += "\n";
		buf.push_back(s);
		s = "";
		
		if(j == l-1){
			s += "┗";
			for(unsigned i = 0; i < b-1; ++i){
				if(isAtCurrPos(j, i)) s += blue_fg + "━━━" + reset + "┻";
				else s += "━━━┻";
			}
			if(isAtCurrPos(j, b-1)) s += blue_fg + "━━━" + reset + "┛\n";
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
			if (y)
				--y;
			return;

		case K_DOWN:
			if (y != b - 1)
				++y;
			return;

		case K_LEFT:
			if (x)
				--x;
			return;

		case K_RIGHT:
			if (x != l - 1)
				++x;
			return;

		case K_SPACE: //placeholder
			return;
	}
}

inline bool Board::isAtCurrPos(int y, int x){
	return x == this->x && y == this->y;
} 