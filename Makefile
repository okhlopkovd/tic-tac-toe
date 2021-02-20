SFML_PATH = libs/SFML-2.5.1
SOURCE_PATH = source
HEADERS_PATH = headers
OBJECTS_PATH = objects

game: 
	g++ -c $(SOURCE_PATH)/Interface.cpp -I $(HEADERS_PATH)/ -o $(OBJECTS_PATH)/Interface.o
	g++ -c $(SOURCE_PATH)/TicTacToe.cpp -I $(HEADERS_PATH)/ -o $(OBJECTS_PATH)/TicTacToe.o
	g++ -c $(SOURCE_PATH)/TicTacToeAI.cpp -I $(HEADERS_PATH)/ -o $(OBJECTS_PATH)/TicTacToeAI.o
	g++ -c $(SOURCE_PATH)/game.cpp -I $(HEADERS_PATH)/ -o $(OBJECTS_PATH)/game.o
	g++ -c $(OBJECTS_PATH)/Interface.o -I $(SFML_PATH)/include
	g++ $(OBJECTS_PATH)/game.o $(OBJECTS_PATH)/Interface.o $(OBJECTS_PATH)/TicTacToe.o $(OBJECTS_PATH)/TicTacToeAI.o -o tictactoe.exe -L SFML_PATH/lib/ -lsfml-graphics -lsfml-window -lsfml-system
