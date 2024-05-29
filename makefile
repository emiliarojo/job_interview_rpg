CC = gcc
CFLAGS = -Wall -g
DEPS = game.h combat.h load_config.h
OBJ = main.o game.o combat.o load_config.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

JobInterviewRPG: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -ljson-c

.PHONY: clean

clean:
	rm -f *.o JobInterviewRPG
