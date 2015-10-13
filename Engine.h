#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
public:
	Engine();
	~Engine();
	void update_display_mode();
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_DisplayMode display;
};

#endif
