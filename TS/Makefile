CC=gcc
FLAGS=-Wall -g -Wunused-function
SRC=src/
EXEC=ts

.PHONY=clean

all: $(EXEC)
	setcap "CAP_SYS_TIME=ep" $(EXEC)
	make clean
$(EXEC): $(SRC)main.c
	$(CC) $(FLAGS) -lcap -o $@ $^

clean:
	rm -f $(SRC)*.o