BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

all:
	g++ -c $(SRC)/func1.c  -I $(INCLUDE)/ -o $(OBJ)/func1.o
	g++ -c $(SRC)/func2.c  -I $(INCLUDE)/ -o $(OBJ)/func2.o
	g++ -c $(SRC)/func3.c  -I $(INCLUDE)/ -o $(OBJ)/func3.o
	g++ -c $(SRC)/func4.c  -I $(INCLUDE)/ -o $(OBJ)/func4.o
	g++ -c $(SRC)/func5.c  -I $(INCLUDE)/ -o $(OBJ)/func5.o
	g++ -c $(SRC)/func6.c  -I $(INCLUDE)/ -o $(OBJ)/func6.o
	g++ -c $(SRC)/func7.c  -I $(INCLUDE)/ -o $(OBJ)/func7.o
	g++ -c $(SRC)/func8.c  -I $(INCLUDE)/ -o $(OBJ)/func8.o
	g++ -c $(SRC)/func9.c  -I $(INCLUDE)/ -o $(OBJ)/func9.o
	
	g++ -c $(SRC)/structs/arvoreb.c  -I $(INCLUDE)/structs -o $(OBJ)/arvoreb.o
	g++ -c $(SRC)/utils.c  -I $(INCLUDE)/ -o $(OBJ)/utils.o

	g++ ./main.c $(OBJ)/*.o -I $(INCLUDE) -lm -o $(BIN)/main

run:
	$(BIN)/main


clean:
	rm $(OBJ)/*.o
	rm $(BIN)/main


test: all run clean