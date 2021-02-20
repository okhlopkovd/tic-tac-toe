#include <TicTacToe.hpp>

TicTacToe::TicTacToe(const int& boardSize, std::vector<std::vector<char>> startState, char startPlayer){
    /* 
    Constructs a game board with passed boardSize,
    startState(optional) by default an empty vector and startPlayer(optional) by default player x
    */

    this->boardSize = boardSize;
    this->currentPlayer = startPlayer;

    if(startState.size() == 0){
        for(int newRow=0; newRow<boardSize; newRow++){
            std::vector<char> row;
            for(int newCol=0; newCol<boardSize; newCol++) row.push_back(TicTacToe::getEmptyCell());
            gameState.push_back(row);
        }
    }

    else gameState = startState;
}

char TicTacToe::getPlayer1(){
    /* 
    Returns the char for player1
    */

    return player1; 
}
char TicTacToe::getPlayer2(){ 
    /* 
    Returns the char for player2
    */

    return player2; 
}

std::vector<std::vector<char>> TicTacToe::getGameState() { 
    /* 
    Returns a 2d char vector with current game state
    */

    return gameState;
}

void TicTacToe::nextPlayer(){
    /*
    Gives the turn to the next player
    */
    if (currentPlayer == player1) currentPlayer = player2;
    else currentPlayer = player1;
}

char TicTacToe::getEmptyCell(){ 
    /*
    Returns the char for an empty cell
    */

    return emptyCell;
}

std::vector<char>& TicTacToe::operator[](int& row){ 
    return gameState[row]; 
}

char TicTacToe::getGoAhead(){ 
    /*
    Returns the char for the case, where there are no winner yet, but 
    the board still has some empty cells
    */

    return goAhead; 
}

char TicTacToe::getTie(){ 
    /*
    Returns the char for the tie state of the game
    */

    return tie; 
}

bool TicTacToe::isAvailable(const int& row, const int& column){
    /*
    Returns true if [row][column] is an empty cell and false otherwise
    */

    if(gameState[row][column] == emptyCell) return true;
    else return false;
}

char TicTacToe::winnerCheck(){
    /*
    Returns either player1 or player2 chars, when there's a winner
    Returns tie char when there is a tie
    Returns goAhead char when there is no winner, but the board still has some cells available

    The main algorithm here is to create a set for each row, column and diagonal and add respective chars to the each set. 
    If one of the sets contains only one char and this char is not the char for an empty spot, it means, that there is a winner
    */

    bool tiePossibility = true;

    std::set<char> winner1 = {player1}; 
    std::set<char> winner2 = {player2};

    std::vector<std::set<char>> winners;

    std::set<char> mdWinner; 
    std::set<char> adWinner; 
    for (int curRowIdx = 0; curRowIdx < boardSize; curRowIdx++){
        std::set<char> hWinner; 
        std::set<char> vWinner; 

        for (int curColIdx = 0; curColIdx < boardSize; curColIdx++){
            char vCell = gameState[curColIdx][curRowIdx];
            char hCell = gameState[curRowIdx][curColIdx];
            
            if(vCell == emptyCell or hCell == emptyCell and tiePossibility==true)
                tiePossibility = false;
            
            hWinner.insert(hCell);
            vWinner.insert(vCell);

            if(curRowIdx==curColIdx) mdWinner.insert(vCell); 
            if(curColIdx==boardSize-curRowIdx-1) adWinner.insert(gameState[curRowIdx][curColIdx]);  
        }
        winners.push_back(hWinner); 
        winners.push_back(vWinner); 
    }
    winners.push_back(adWinner);
    winners.push_back(mdWinner);

    for(int winnerStateIdx=0; winnerStateIdx<winners.size(); winnerStateIdx++){
        std::set<char> winner = winners[winnerStateIdx];

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
    /*
    Returns the char for current player
    */

    return currentPlayer; 
}

