#include <Interface.hpp>

Interface::Interface(const int& boardSize, const bool ai){
    /*
    Constructs a graphic interface for the game of tic-tac-toe
    */

    gameWindow.create(sf::VideoMode(windowWidth, windowHeight+tabSize), "TicTacToe", sf::Style::Close);
    game = TicTacToe(boardSize);
    this->ai = ai; 

    cellWidth = windowWidth / boardSize;
    cellHeight = windowHeight / boardSize;
}

void Interface::drawField(){
    /*
    Draws the grid
    */

    const int boardSize = game.getBoardSize();

    for (int i = 1; i < boardSize; i++){
        sf::Vertex vLine[] = {
           sf::Vertex(sf::Vector2f(i*cellWidth, 0)),
           sf::Vertex(sf::Vector2f(i*cellWidth, windowHeight))};

        sf::Vertex hLine[] = {
            sf::Vertex(sf::Vector2f(0, i*cellHeight)),
            sf::Vertex(sf::Vector2f(windowWidth, i*cellHeight))};

        gameWindow.draw(vLine, 2, sf::Lines);
        gameWindow.draw(hLine, 2, sf::Lines);
    }

    sf::Vertex vLine[] = {
        sf::Vertex(sf::Vector2f(0, windowHeight)),
        sf::Vertex(sf::Vector2f(windowWidth, windowHeight))};

    gameWindow.draw(vLine, 2, sf::Lines);
    gameWindow.display();
}

void Interface::makeMove(int& i, int& j){
    /*
    Marks the [i][j] spot as the char for currentPlayer
    */

    const char currentPlayer = game.getCurrentPlayer();
    game[i][j] = currentPlayer;

    drawMove(i, j, currentPlayer);
    game.nextPlayer();
}

std::vector<int> Interface::coordsToBoard(const int& x, const int& y){
    /*
    Returns an int vector with the row and column for the passsed coordinates
    */

    return {y/cellHeight, x/cellWidth};
}

void Interface::drawMove(const int& row, const int& column, const char& currentPlayer){
    /*
    Draws the char for the passed player on the grid 
    */
   
    const int offset = cellHeight / 50;
    
    if(currentPlayer == 'x'){
        sf::Vertex mDiagonal[] = {
            sf::Vertex(sf::Vector2f(
                column*cellWidth + offset, 
                row*cellHeight + offset)), 

            sf::Vertex(sf::Vector2f(
                (column+1)*cellWidth -offset,
                (row+1)*cellHeight - offset))
        };

        sf::Vertex aDiagonal[] = {
            sf::Vertex(sf::Vector2f(
                column*cellWidth + offset, 
                (row+1)*cellHeight - offset)), 

            sf::Vertex(sf::Vector2f(
                (column+1)*cellWidth - offset,
                row*cellHeight + offset))
        };

        gameWindow.draw(mDiagonal, 2, sf::Lines);
        gameWindow.draw(aDiagonal, 2, sf::Lines);
    }
    else if(currentPlayer == 'o'){
        const int radius = cellWidth / 2 - offset;
        const int thickness = 1;
        sf::CircleShape oShape(radius);

        oShape.setFillColor(fieldColor);
        oShape.setOutlineThickness(thickness);

        oShape.setPosition((column)*cellWidth+offset, (row)*cellHeight+offset);
        gameWindow.draw(oShape);
    }
}

void Interface::drawWinner(const char& winner){
    /*
    Draws the text the passed game result in a special place below the board
    */

    const std::string fontFolder = "fonts/";
    const std::string tieString = "Game resulted in a tie";

    sf::Font winnerTextFont;
    if(!(winnerTextFont.loadFromFile(fontFolder + "arial.ttf"))) return;

    sf::Text winnerText;
    winnerText.setFont(winnerTextFont);

    std::string winnerString = "Winner is ";
    winnerString.push_back(winner);

    if(winner != game.getTie()) winnerText.setString(winnerString);
    else winnerText.setString(tieString);

    winnerText.move(0, windowHeight);
    gameWindow.draw(winnerText);
}

void Interface::gameLoop(){
    /*
    The main loop of the game

    Basic algorithm:

    1. Wait for the player to click somewhere
    2. Convert mouse coordinates to the row and the column
    3. If [row][column] is available, mark the spot and draw the move
    4. If ai is enabled, calculate the best spot, mark it and draw the move
    5. If returned char for winner is not goAhead char, draw the winner
    */

    TicTacToeAI aiPlayer;
    const char tie = game.getTie();
    const char goAhead = game.getGoAhead();
    bool gameIsRunning = true;

    while(gameWindow.isOpen()){
        sf::Event event;

        while(gameWindow.pollEvent(event)) { 
            if(event.type == sf::Event::Closed){
                gameWindow.close();
            }

            if(event.type == sf::Event::MouseButtonPressed and gameIsRunning){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(gameWindow);
                int x = mousePosition.x;
                int y = mousePosition.y;

                if(x < 0 or x >= windowWidth or y < 0 or y >= windowHeight){
                    continue;
                }

                std::vector<int> onBoardPosition = coordsToBoard(x, y);

                int row = onBoardPosition[0];
                int column = onBoardPosition[1];

                if(game.isAvailable(row, column)) {
                    makeMove(row, column);

                    if(ai){
                        std::vector<std::vector<char>> currentState = game.getGameState();
                        std::vector<int> aiSpot = aiPlayer.aiMove(currentState);

                        int aiRow = aiSpot[0];
                        int aiColumn = aiSpot[1];
                        
                        if (aiRow != -1 and aiColumn != -1) makeMove(aiRow, aiColumn);
                    }
                }

                char winner = game.winnerCheck();
                if(winner != goAhead) {
                    drawWinner(winner);
                    gameIsRunning = false;
                }

                gameWindow.display();
            }
        } 
    }
}