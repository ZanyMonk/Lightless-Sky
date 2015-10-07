CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = Loul

all: $(EXE)

$(EXE): main.o Game.o Planet.o
	$(CXX) $< $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Game.o: Game.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Planet.o: Planet.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)

# g++ main.cpp Engine.cpp Game.cpp Planet.cpp Ship.cpp -w -lSDL2 -o test && ./test
