a.out:game.o ai.o function.o
	g++ -Wall -o a.out game.o ai.o function.o
game.o:game.cpp chessman.h
	g++ -Wall -c game.cpp
function.o:function.h function.cpp
	g++ -Wall -c function.cpp
ai.o:ai.h ai.cpp chessman.h
	g++ -Wall -c ai.cpp

clean:
	rm -f ai.o game.o function.o a.out
