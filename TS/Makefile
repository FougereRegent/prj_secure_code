CC=gcc
FLAGS=-Wall
SRC=src/
EXEC=ts

.PHONY=clean

all: $(EXEC)
	sudo setcap cap_setpcap,cap_sys_time+eip $(EXEC)
$(EXEC): $(SRC)main.c
	$(CC) $(FLAGS) -o $@ $^ -lcap

clean:
	rm -f server ts
