CC=gcc
FLAGS=-Wall
SRC=src/
EXEC=ts

.PHONY=clean

all: $(EXEC)
	sudo setcap cap_sys_time+ep $(EXEC)
$(EXEC): $(SRC)main.c
	$(CC) $(FLAGS) -o $@ $^ -lcap

clean:
	rm -f server ts
