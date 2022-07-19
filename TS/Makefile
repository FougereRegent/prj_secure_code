CC=gcc
FLAGS=-Wall -g -Wunused-function -z execstack
SRC=src/
EXEC=ts

.PHONY=clean

all: $(EXEC)
	setcap "CAP_SYS_TIME=ep" $(EXEC)

$(EXEC): $(SRC)main.c
	$(CC) $(FLAGS) -lcap -o $@ $^

clean:
	rm -f server ts
