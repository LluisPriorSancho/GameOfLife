# Coder 1 and Coder 2
CC = gcc
CFLAGS = -Wall -I/usr/include/ -I. -pg 
LDFLAGS = -lncurses -pg
DEPS = common.h Game.h windows.h
OBJ = windows.o Game.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

GameOfLife: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) GameOfLife Times.txt gmon.out metrics.png

init: GameOfLife
	./GameOfLife

memoryCheck: GameOfLife
	valgrind --leak-check=yes --tool=memcheck ./GameOfLife

times: GameOfLife
	gprof GameOfLife gmon.out > Times.txt

connect: GameOfLife
	gprof ./GameOfLife gmon.out | ./gprof2dot/gprof2dot.py -w -s --node-thres=0.0 --edge-thres=0.0 | dot -Tpng -o metrics.png
