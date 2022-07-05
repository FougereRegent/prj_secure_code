CC = gcc
FLAGS = -Wall -g
SOURCES = main.c

.PHONY = clean

bin : %.o
	@echo "Compilation des fichiers obj"
	$(CC) $< -o $@
	make clean

%.o : $(SOURCES)
	@echo "Compilation des sources"
	$(CC) $(FLAGS) $<


clean:
	@echo "Suppression de tous les fichiers obj"
	rm -f *.o