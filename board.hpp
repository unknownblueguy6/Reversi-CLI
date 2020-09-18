#pragma once

#include <vector>
#include <iostream>
#include "cell.hpp"

const unsigned LENGTH = 8;
const unsigned BREADTH = 8;


class Board
{
	public:
		Board();
		void draw();
		
	private:
		unsigned l;
		unsigned b;
		std::vector<std::vector<Cell>> cells;
};

Board::Board(){
	l = LENGTH;
	b = BREADTH;
	cells = std::vector<std::vector<Cell>>(b, std::vector<Cell>(l, Cell()));
}

void Board::draw(){
	std::vector<std::string> buf;
	std::string s = "";
	for(unsigned i = 0; i < l; ++i){
		if(i == 0){
			s += "┏";
				for(unsigned j = 0; j < b-1; ++j) s += "━━━┳";
				s += "━━━┓\n"; 
				buf.push_back(s);
				s = "";
		}

		if(i > 0 && i < l){
			s += "┣";
			for(unsigned j = 0; j < b-1; ++j) s += "━━━╋";
			s += "━━━┫\n"; 
			buf.push_back(s);
			s = "";
		}

		s += "┃";
		for(unsigned j = 0; j < b; ++j){
			switch(cells[i][j].state){
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
			s += " ┃";
		}
		s += "\n";
		buf.push_back(s);
		s = "";
		
		if(i == l-1){
			s += "┗";
			for(unsigned j = 0; j < b-1; ++j) s += "━━━┻";
			s += "━━━┛\n"; 
			buf.push_back(s);
			s = "";
		}
	}
	for(auto str: buf) std::cout << str;
}