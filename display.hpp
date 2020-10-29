#pragma once

#include <iostream>
#include <iomanip>
#include "init.hpp"
#include "colour.hpp"
#include "board.hpp"

void displayBanner(){
    std::cout << R"(
    8888888b.  8888888888 888     888 8888888888 8888888b.   .d8888b. 8888888 
    888   Y88b 888        888     888 888        888   Y88b d88P  Y88b  888   
    888    888 888        888     888 888        888    888 Y88b.       888   
    888   d88P 8888888    Y88b   d88P 8888888    888   d88P  "Y888b.    888   
    8888888P"  888         Y88b d88P  888        8888888P"      "Y88b.  888   
    888 T88b   888          Y88o88P   888        888 T88b         "888  888   
    888  T88b  888           Y888P    888        888  T88b  Y88b  d88P  888   
    888   T88b 8888888888     Y8P     8888888888 888   T88b  "Y8888P" 8888888)";
    std::cout << "\n\n\n"; 
}

void displayControls(std::vector<std::string> &buf)
{
    std::vector<std::string> controls = {
        "CONTROLS : ",
        GREEN + "Green Cursor " + RESET + ": Disk can be placed",
        RED + "Red Cursor "  + RESET + ": Disk cannot be placed",
        "↑, ←, ↓, → : Move the Cursor",
        "SPACEBAR : Place Disk",
    };
    for(int i = 0; i < controls.size(); ++i){
        buf[i] += "  " + controls[i];
    }
}

void showMenu()
{
    int ch;
    do
    {
        displayBanner();
        std::cout << std::setw(10);
        std::cout << BLUE << "Maximise Terminal or press F11 for the optimal experience" << RESET;
        std::cout << "\n\n";
        std::cout << std::setw(21) << "Choose Game Mode:\n";
        std::cout << std::setw(10);
        std::cout << RED << "1. VS. COMPUTER\n";
        std::cout << std::setw(10);
        std::cout << GREEN << "2. VS. HUMAN\n\n" << RESET;
        std::cout << "   ";
        std::cin >> ch;

        if (ch < 1 || ch > 2)
        {
            std::cout << RED << "Invalid Choice. Try again\n";
            auto c = getch();
        }
        else
            gameMode = (GAME_MODE)ch;
        system("clear");

    } while (ch < 1 || ch > 4);
}