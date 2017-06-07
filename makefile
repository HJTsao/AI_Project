<<<<<<< HEAD
a.out:game.o ai.o function.o
	g++ -Wall -o a.out game.o ai.o function.o
game.o:game.cpp chessman.h
	g++ -Wall -c game.cpp
function.o:function.h function.cpp
	g++ -Wall -c function.cpp
=======
a.out:game.o ai.o
	g++ -Wall -o a.out game.o ai.o
game.o:game.cpp chessman.h
	g++ -Wall -c game.cpp
>>>>>>> 185cac7abf9b2e18dfd3fcafdb542cbe405701f5
ai.o:ai.h ai.cpp chessman.h
	g++ -Wall -c ai.cpp

clean:
<<<<<<< HEAD
	rm -f ai.o game.o function.o a.out
=======
	rm -f ai.o game.o a.out
>>>>>>> 185cac7abf9b2e18dfd3fcafdb542cbe405701f5
