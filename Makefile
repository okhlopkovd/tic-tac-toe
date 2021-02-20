SFML_PATH = libs/SFML-2.5.1
SOURCE_PATH = source
HEADERS_PATH = headers
OBJECTS_PATH = objects

export LD_LIBRARY_PATH=$(SFML_PATH)/lib

game: 
	g++ -c $(SOURCE_PATH)/Interface.cpp -I $(HEADERS_PATH)/ -I $(SFML_PATH)/include -o $(OBJECTS_PATH)/Interface.o
	g++ -c $(SOURCE_PATH)/TicTacToe.cpp -I $(HEADERS_PATH)/ -o $(OBJECTS_PATH)/TicTacToe.o
	g++ -c $(SOURCE_PATH)/TicTacToeAI.cpp -I $(HEADERS_PATH)/ -o $(OBJECTS_PATH)/TicTacToeAI.o
	g++ -c $(SOURCE_PATH)/game.cpp -I $(HEADERS_PATH)/ -I $(SFML_PATH)/include -o $(OBJECTS_PATH)/game.o
	g++ $(OBJECTS_PATH)/game.o $(OBJECTS_PATH)/TicTacToe.o $(OBJECTS_PATH)/TicTacToeAI.o $(OBJECTS_PATH)/Interface.o -o tictactoe.exe -L${SFML_PATH}/lib -lsfml-graphics -lsfml-window -lsfml-system
