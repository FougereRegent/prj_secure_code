CC=gcc
FLAGS=-Wall
EXEC=bin
SRC=src/
.PHONY=clean

all: $(EXEC)
	make clean

$(EXEC): $(SRC)main.o
	$(CC) $^ -o $@ -lcap

$(SRC)main.o: $(SRC)main.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f $(SRC)*.o