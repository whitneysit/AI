CFLAGS = -O -g
CC = g++ -std=c++11

main: hero.o game.o main.cpp
	$(CC) $(CFLAGS) -o main hero.o main.cpp game.o

game.o: game.cpp
	$(CC) $(CFLAGS) -c game.cpp

hero.o: hero.cpp
	$(CC) $(CFLAGS) -c hero.cpp

clean:
	rm -f core *.o main
