CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=-lSDL2
EXEC=test

all: $(EXEC) clean

test: SDL2_gfx/SDL2_gfxPrimitives.o SDL2_gfx/SDL2_rotozoom.o Engine.o Utils.o Screen.o Interface.o Game.o Planet.o Ship.o main.o
	$(CC) -o $(EXEC) SDL2_gfx/SDL2_gfxPrimitives.o SDL2_gfx/SDL2_rotozoom.o Engine.o Utils.o Screen.o Game.o Interface.o Planet.o Ship.o main.o $(LDFLAGS)

SDL2_gfx/SDL2_rotozoom.o: SDL2_gfx/SDL2_rotozoom.c
	$(CC) -o $@ -c $<

SDL2_gfx/SDL2_gfxPrimitives.o: SDL2_gfx/SDL2_gfxPrimitives.c SDL2_gfx/SDL2_rotozoom.h
	$(CC) -o $@ -c $<

Utils.o: Utils.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Engine.o: Engine.cpp Utils.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Screen.o: Screen.cpp Engine.hpp Utils.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Interface.o: Interface.cpp Utils.hpp Engine.hpp Planet.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Game.o: Game.cpp Utils.hpp Engine.hpp Interface.hpp Planet.hpp Ship.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Planet.o: Planet.cpp Utils.hpp Engine.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Ship.o: Ship.cpp Utils.hpp Engine.hpp Planet.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.cpp Engine.hpp Utils.hpp Screen.hpp Game.hpp Interface.hpp Planet.hpp Ship.hpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

clean:
	@rm -rf *.o
	@echo -e "[+] Object files removed.\n\n"

mrproper: clean
	rm -rf $(EXEC)
