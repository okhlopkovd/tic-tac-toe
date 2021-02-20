#include <TicTacToe.hpp>

TicTacToe::TicTacToe(const int& boardSize, std::vector<std::vector<char>> startState, char startPlayer){
    this->boardSize = boardSize;
    this->currentPlayer = startPlayer;

    if(startState.size() == 0){
        for(int i=0; i<boardSize;i++){
            std::vector<char> row;
            for(int j=0; j<boardSize;j++) row.push_back(TicTacToe::getEmptyCell());
            gameState.push_back(row);
        }
    }

    else gameState = startState;
}

char TicTacToe::getPlayer1(){
     return player1; 
}
char TicTacToe::getPlayer2(){ 
    return player2; 
}

std::vector<std::vector<char>> TicTacToe::getGameState() { 
    return gameState;
}

void TicTacToe::nextPlayer(){
    if (currentPlayer == player1) currentPlayer = player2;
    else currentPlayer = player1;
}

char TicTacToe::getEmptyCell(){ 
    return emptyCell;
}

std::vector<char>& TicTacToe::operator[](int& row){ return gameState[row]; }

char TicTacToe::getGoAhead(){ 
    return goAhead; 
}

char TicTacToe::getTie(){ 
    return tie; 
}

bool TicTacToe::isAvailable(const int& row, const int& column){
    if(gameState[row][column] == emptyCell) return true;
    else return false;
}

char TicTacToe::winnerCheck(){
    bool tiePossibility = true;

    std::set<char> winner1 = {player1}; 
    std::set<char> winner2 = {player2};

    std::vector<std::set<char>> winners;

    std::set<char> mdWinner; 
    std::set<char> adWinner; 
    for (int i = 0; i < boardSize; i++){
        std::set<char> hWinner; 
        std::set<char> vWinner; 

        for (int j = 0; j < boardSize; j++){
            char vCell = gameState[j][i];
            char hCell = gameState[i][j];
            
            if(vCell == emptyCell or hCell == emptyCell and tiePossibility==true)
                tiePossibility = false;
            
            hWinner.insert(hCell);
            vWinner.insert(vCell);

            if(i==j) mdWinner.insert(vCell); 
            if(j==boardSize-i-1) adWinner.insert(gameState[i][j]);  
        }
        winners.push_back(hWinner); 
        winners.push_back(vWinner); 
    }
    winners.push_back(adWinner);
    winners.push_back(mdWinner);

    for(int i=0;i<winners.size();i++){
        std::set<char> winner = winners[i];

        if(winner == winner1) return player1;
        else if(winner == winner2) return player2;
    }

    if (tiePossibility) return tie;
    else return goAhead;
}

TicTacToe& TicTacToe::operator=(const TicTacToe& other){
    this->gameState = other.gameState;
    this->boardSize = other.boardSize;
    this->currentPlayer = other.currentPlayer;
    return *this;
}

int TicTacToe::getBoardSize(){ 
    return boardSize; 
}

char TicTacToe::getCurrentPlayer() { 
    return currentPlayer; 
}

