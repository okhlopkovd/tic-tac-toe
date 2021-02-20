#include <iostream>
#include <Interface.hpp>

using namespace std;

int main(){
    const int boardSize = 3;
    Interface game(boardSize, true);
    
    game.drawField();
    game.gameLoop();

    return 0;
}