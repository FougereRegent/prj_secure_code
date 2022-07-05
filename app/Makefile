CC=gcc
FLAGS=-Wall -g
INC=-I includes/
SRC= src/
EXEC=bin

.PHONY=clean

$(EXEC): $(SRC)main.c $(SRC)UI.o
	$(CC) $(INC) $(FLAGS) -o $@ $^

$(SRC)%.o: $(SRC)%.c
	$(CC) $(INC) $(FLAGS) -o $(SCR)$@ -c $<

clean:
	rm -f $(SRC)*.o