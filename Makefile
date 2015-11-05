CC=g++
CFLAGS=-Wno-unused-variable -Wall -g -std=c++11
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf
EXEC=test

all: $(EXEC) clean

test: SDL2_gfx/SDL2_gfxPrimitives.o SDL2_gfx/SDL2_rotozoom.o Utils.o Faction.o Player.o Engine.o Screen.o Widget.o Interface.o Game.o Entity.o Planet.o Star.o Ship.o main.o
	$(CC) -o $(EXEC) SDL2_gfx/SDL2_gfxPrimitives.o SDL2_gfx/SDL2_rotozoom.o Utils.o Faction.o Player.o Engine.o Screen.o Widget.o Interface.o Game.o Entity.o Planet.o Star.o Ship.o main.o $(LDFLAGS)

SDL2_rotozoom.o: SDL2_gfx/SDL2_rotozoom.c
	$(CC) -o $@ -c $<

SDL2_gfxPrimitives.o: SDL2_gfx/SDL2_gfxPrimitives.c SDL2_gfx/SDL2_rotozoom.h
	$(CC) -o $@ -c $<

Utils.o: Utils.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Faction.o: Faction.cpp Utils.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Engine.o: Engine.cpp Utils.hpp Faction.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Entity.o: Entity.cpp Utils.hpp Engine.hpp Faction.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Planet.o: Planet.cpp Utils.hpp Engine.hpp Entity.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Star.o: Star.cpp Utils.hpp Engine.hpp Planet.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Ship.o: Ship.cpp Utils.hpp Engine.hpp Planet.hpp Entity.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Player.o: Player.cpp Utils.hpp Engine.hpp Faction.hpp Planet.hpp Ship.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Screen.o: Screen.cpp Engine.hpp Utils.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Widget.o: Widget.cpp Engine.hpp Utils.hpp Planet.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Interface.o: Interface.cpp Utils.hpp Engine.hpp Planet.hpp Widget.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

Game.o: Game.cpp Utils.hpp Engine.hpp Interface.hpp Screen.hpp Faction.hpp Player.hpp Entity.hpp Planet.hpp Star.hpp Ship.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.cpp Engine.hpp Game.hpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

clean:
	@rm -rf *.o
	@echo "[+] Object files removed.\n\n"

mrproper: clean
	rm -rf $(EXEC)
