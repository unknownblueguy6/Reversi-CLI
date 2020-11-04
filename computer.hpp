#pragma once

#include <algorithm>
#include "board.hpp"

class Computer{
    public:
        std::pair<int, int> chooseMove(Board);
        void makeMove(Board&);
    private:
        bool isOnCorner(std::pair<int, int>, int, int);

};

std::pair<int, int> Computer::chooseMove(Board board){
    std::vector<std::pair<int, int>> possibleMoves;
    
    for(int j = 0; j < board.l; ++j){
        for(int i = 0; i < board.b; ++i){
            if(board.isValidMove(j, i)){
                possibleMoves.push_back(std::make_pair(i, j));
            } 
        }
    }

    std::random_shuffle(possibleMoves.begin(), possibleMoves.end());

    for(auto move : possibleMoves){
        std::cout << move.first << " " << move.second << "\n";
        if(isOnCorner(move, board.l, board.b)) return move;    
    }

    int bestScore = -1;
    std::pair<int, int> bestMove;
    
    for(auto move: possibleMoves){
        Board copy = board;
        copy.x = move.first;
        copy.y = move.second;
        copy.isValidMove(copy.y, copy.x);
        copy.placeDisk();
        copy.draw();
        for(int k = 0; k < 9; ++k){
			if(copy.dirs[k]){
				int dir_y = copy.setDirY(k);
				int dir_x = copy.setDirX(k);
				copy.flipDiscs(copy.cells[copy.y][copy.x].state, copy.y+dir_y, copy.x+dir_x, dir_y, dir_x);
			}
		}
        
        if(bestScore < copy.noOfWhiteDisks){
            bestScore = copy.noOfWhiteDisks;
            bestMove = move;
        }
    }

    return bestMove;

}

void Computer::makeMove(Board &board){
    Board copy = board;
    auto move = chooseMove(board);
    board.x = move.first;
    board.y = move.second;
    board.isValidMove(board.y, board.x);
    board.placeDisk();
    for(int k = 0; k < 9; ++k){
		if(board.dirs[k]){
			int dir_y = board.setDirY(k);
			int dir_x = board.setDirX(k);
			board.flipDiscs(board.cells[board.y][board.x].state, board.y+dir_y, board.x+dir_x, dir_y, dir_x);
		}
	}
}

bool Computer::isOnCorner(std::pair<int, int> coords, int l, int b){
    return (coords.first == 0   && coords.second == 0  ) ||
           (coords.first == 0   && coords.second == b-1) ||
           (coords.first == l-1 && coords.second == 0  ) ||
           (coords.first == l-1 && coords.second == b-1);
}