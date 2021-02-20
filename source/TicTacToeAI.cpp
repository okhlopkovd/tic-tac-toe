#include <TicTacToeAI.hpp>
#include <iostream>

std::vector<std::vector<std::vector<char>>> TicTacToeAI::possibleMoves(std::vector<std::vector<char>>& state, const char& currentPlayer){
    /*
    Calculates all available moves in the passed state for the passed player
    Returns the 3d char vector with all of the moves
    */

    const int rowsLen = state.size();
    const int colsLen = state[0].size();
    std::vector<std::vector<std::vector<char>>> possibleMoves;

    for (int i = 0; i < rowsLen; i++){
        for (int j = 0; j < colsLen; j++){
            if(state[i][j] == emptyCell){
                std::vector<std::vector<char>> possibleMove = state;
                possibleMove[i][j] = currentPlayer;
                possibleMoves.push_back(possibleMove);
            }
        }  
    }  
    return possibleMoves; 
}

int TicTacToeAI::minimax(std::vector<std::vector<char>>& state, int alpha, int beta, bool isMaximizing){
    /*
    The implementation for minimax algorithm with alpha-beta pruning
    The link to the basic explanation: https://en.wikipedia.org/wiki/Minimax
    */

    const int boardSize = state.size(); 
    const char goAhead = TicTacToe::getGoAhead();

    TicTacToe predictedGame(boardSize, state); 

    char winner = predictedGame.winnerCheck(); 
    if(winner != goAhead) return winnerScore[winner];

    if(isMaximizing){
        int bestScore = - 100;
        std::vector<std::vector<std::vector<char>>> possibleSpots = possibleMoves(state, aiPlayer);

        for (int i = 0; i < possibleSpots.size(); i++){
            int score = minimax(possibleSpots[i], alpha, beta, false);
            bestScore = std::max(score, bestScore);

            alpha = std::max(alpha, score);
            if(beta<=alpha) break;
        }

        return bestScore;
    }
    else{ 
        int bestScore = 100;
        std::vector<std::vector<std::vector<char>>> possibleSpots = possibleMoves(state, humanPlayer);

        for (int i = 0; i < possibleSpots.size(); i++){
            int score = minimax(possibleSpots[i], alpha, beta, true);
            bestScore = std::min(score, bestScore);

            beta = std::min(beta, score);
            if(beta<=alpha) break;
        }

        return bestScore;
    }
}

std::vector<int> TicTacToeAI::aiMove(std::vector<std::vector<char>>& state){
    /*
    Calculates the best move for the passed state
    Returns the vector with the row and the column of the best move
    */

    int bestScore = -100;
    std::vector<int> bestSpot = {-1, -1};

    const int rowsLen = state.size();
    const int colsLen = state[0].size();
    
    for(int i=0; i<rowsLen;i++){
        for (int j = 0; j < colsLen; j++){
           if(state[i][j] == emptyCell){
                state[i][j] = aiPlayer;
                int score = minimax(state, -100, 100, false);
                state[i][j] = emptyCell;

                if(score>bestScore){
                    bestScore = score;
                    bestSpot = {i, j};
                }
           }
        }
    }
    return bestSpot;
}