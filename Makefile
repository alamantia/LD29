LIBS  = -lSDL2 -lBox2D -lSDL2_image  -lSDL2_mixer
CFLAGS = -w -ggdb

# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.cpp)

game: nxjson.o  $(SRC)
	g++ -o $@ $^ $(CFLAGS) $(LIBS) -std=c++11 -std=gnu++11  -DLINUX 

nxjson.o:
	gcc -c nxjson.c 

clean:		
	rm *.o ./game
