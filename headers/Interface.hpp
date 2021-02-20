#ifndef INTERFACE_H
#define INTERFACE_H
#include <vector>
#include <SFML/Graphics.hpp>

#include "TicTacToe.hpp"
#include "TicTacToeAI.hpp"

class Interface{
private:
    TicTacToe game;
    bool ai;

    const int windowWidth = 800;
    const int windowHeight = 800;
    const int tabSize = 50;

    int cellWidth;
    int cellHeight;

    sf::RenderWindow gameWindow;
    sf::Color fieldColor = sf::Color::Black;

    void drawMove(const int& row, const int& column, const char& currentPlayer);
public:
    Interface(const int& boardSize, const bool ai);

    void drawField();

    void makeMove(int& i, int& j);

    std::vector<int> coordsToBoard(const int& x, const int& y);

    void drawWinner(const char& winner);

    void update();

    void gameLoop();
};

#endif