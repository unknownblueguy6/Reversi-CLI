#pragma once

#include <iostream>
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