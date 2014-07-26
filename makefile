OBJS = Board.o Minimax.o Source.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

assign2 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o assign2
	
Source.o : Source.cpp
	$(CC) $(CFLAGS) Source.cpp

Minimax.o : Minimax.h Minimax.cpp
	$(CC) $(CFLAGS) Minimax.cpp

Board.o : Board.h Board.cpp
	$(CC) $(CFLAGS) Board.cpp

clean:
	\rm *.o assign2
