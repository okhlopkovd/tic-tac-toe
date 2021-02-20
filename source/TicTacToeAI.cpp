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

    for (int rowIdx = 0; rowIdx < rowsLen; rowIdx++){
        for (int colIdx = 0; colIdx < colsLen; colIdx++){
            if(state[rowIdx][colIdx] == emptyCell){
                std::vector<std::vector<char>> possibleMove = state;
                possibleMove[rowIdx][colIdx] = currentPlayer;
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

        for (int possibleSpotIdx = 0; possibleSpotIdx < possibleSpots.size(); possibleSpotIdx++){
            int score = minimax(possibleSpots[possibleSpotIdx], alpha, beta, false);
            bestScore = std::max(score, bestScore);

            alpha = std::max(alpha, score);
            if(beta<=alpha) break;
        }

        return bestScore;
    }
    else{ 
        int bestScore = 100;
        std::vector<std::vector<std::vector<char>>> possibleSpots = possibleMoves(state, humanPlayer);

        for (int possibleSpotIdx = 0; possibleSpotIdx < possibleSpots.size(); possibleSpotIdx++){
            int score = minimax(possibleSpots[possibleSpotIdx], alpha, beta, true);
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
    
    for(int rowIdx=0; rowIdx<rowsLen; rowIdx++){
        for (int colIdx = 0; colIdx < colsLen; colIdx++){
           if(state[rowIdx][colIdx] == emptyCell){
                state[rowIdx][colIdx] = aiPlayer;
                int score = minimax(state, -100, 100, false);
                state[rowIdx][colIdx] = emptyCell;

                if(score>bestScore){
                    bestScore = score;
                    bestSpot = {rowIdx, colIdx};
                }
           }
        }
    }
    return bestSpot;
}