#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <set>
#include <vector>


class TicTacToe{
private:
    std::vector<std::vector<char>> gameState;
    int boardSize;

    char currentPlayer;

    static const char emptyCell = ' ';

    static const char tie = 't';
    static const char goAhead = 'g';

    static const char player1 = 'x';
    static const char player2 = 'o';
public:

    TicTacToe()=default;

    TicTacToe(const int& boardSize, std::vector<std::vector<char>> startState={}, char startPlayer='x');

    std::vector<std::vector<char>> getGameState();

    static char getEmptyCell();

    char winnerCheck();

    static char getTie();

    static char getGoAhead();

    std::vector<char>& operator[](int& row);

    TicTacToe& operator=(const TicTacToe& other);

    int getBoardSize();

    bool isAvailable(const int& row, const int& column);

    char getCurrentPlayer();

    void nextPlayer();

    static char getPlayer1();

    static char getPlayer2();
};

#endif