CC=gcc
FLAGS=-Wall -g -Wunused-function
SRC=src/
EXEC=ts

.PHONY=clean

all: $(EXEC)
	make clean
$(EXEC): $(SRC)main.c
	$(CC) $(FLAGS) -lcap -o $@ $^

clean:
	rm -f $(SRC)*.o