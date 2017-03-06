a.out:game.o ai.o
	g++ -Wall -o a.out game.o ai.o
game.o:game.cpp chessman.h
	g++ -Wall -c game.cpp
ai.o:ai.h ai.cpp chessman.h
	g++ -Wall -c ai.cpp

clean:
	rm -f ai.o game.o a.out
