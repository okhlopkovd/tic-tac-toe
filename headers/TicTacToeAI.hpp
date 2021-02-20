#ifndef AI_H
#define AI_H
#include "TicTacToe.hpp"
#include <vector>
#include <map>

class TicTacToeAI{
private:
    const char humanPlayer = TicTacToe::getPlayer1();
    const char aiPlayer = TicTacToe::getPlayer2();

    const char emptyCell = TicTacToe::getEmptyCell();

    std::map<char, int> winnerScore = {
        {humanPlayer, -10},
        {aiPlayer, 10},
        {TicTacToe::getTie(), 0}
    };

    std::vector<std::vector<std::vector<char>>> possibleMoves(std::vector<std::vector<char>>&, const char& currentPlayer);

    int minimax(std::vector<std::vector<char>>& state, int alpha, int beta, bool isMaximizing);
public:

    std::vector<int> aiMove(std::vector<std::vector<char>>& state);
};

#endif