#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Utils.hpp"

/* Couleurs
 *      vert   bleu
 *          \  /
 *    0xAABBCCDD
 *      /  \
 * opacité  rouge
 */
const int GREEN	= 0xFF70BD28;
const int BLACK	= 0xFF000000;
const int RED		= 0xFF0000FF;
const int GRAY	= 0x2254778C;
const int WHITE	= 0xFFFFFFFF;

const string FONT_PATH			= "fonts/Welbut__.ttf";
const int FONT_SIZE_DEFAULT	= 12;

class Engine
{
public:
	Engine();
	~Engine();
	void update_display_mode();
	// Drawing functions
	SDL_Texture* text_to_textureColor(
		const string &message,
		const string &fontFile,
		Uint32 color,
		Uint8 fontSize = FONT_SIZE_DEFAULT
	);
	SDL_Texture* text_to_textureRGBA(
		const string &message,
		const string &fontFile,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a,
		Uint8 fontSize = FONT_SIZE_DEFAULT
	);
	void draw_textColor( const string &text, Point* pos, Uint32 color );
	void draw_textRGBA(
		const std::string &text,
		Point* pos,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a,
		Uint8 fontSize = FONT_SIZE_DEFAULT
	);
	void draw_texture( SDL_Texture* texture, Point* pos, Sint8 alpha = 255 );
	void draw_polygon( short int x[], short int y[], Sint8 n, Uint32 color );
	string multString( string str, Sint8 n );

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_DisplayMode display;
	Point cursor;
	int amount;
	bool click;
};

#endif
