CC=gcc
FLAGS=-Wall -g
EXEC=bin
SRC=src/
.PHONY=clean

all: $(EXEC)
	sudo setcap cap_setpcap+eip $(EXEC)
	make clean

$(EXEC): $(SRC)main.o
	$(CC) $^ -o $@ -lcap

$(SRC)main.o: $(SRC)main.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f $(SRC)*.o