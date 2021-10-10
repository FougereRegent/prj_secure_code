CC=gcc
FLAGS=-Wall -g -Wunused-function
SRC=src/
EXEC=ts

.PHONY=clean

all: $(EXEC)

$(EXEC): $(SRC)main.c
	$(CC) $(FLAGS) -o $@ $^ -lcap

clean:
	rm -f server ts
