CC=gcc
FLAGS=-Wall -g
EXEC=bin
SRC=src/
.PHONY=clean

all: $(EXEC)
	make clean

$(EXEC): $(SRC)main.o
	$(CC) $^ -o $@

$(SRC)main.o: $(SRC)main.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f $(SRC)*.o