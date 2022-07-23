CC=gcc
FLAGS=-Wall -g
INC=-I includes/
SRC= src/
EXEC=bin

.PHONY=clean

all: $(EXEC)
	sudo setcap cap_setpcap+eip $(EXEC)
	make clean
$(EXEC): $(SRC)main.c $(SRC)treatment_time.o $(SRC)UI.o $(SRC)server.o
	$(CC) $(INC) $(FLAGS) -pthread -o $@ $^ -lcap

$(SRC)%.o: $(SRC)%.c
	$(CC) $(INC) $(FLAGS) -o $(SCR)$@ -c $<

clean:
	rm -f $(SRC)*.o