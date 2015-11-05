#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include "Utils.hpp"
#include "Faction.hpp"

/*----
 * Inputs
 *	La gestion des inputs se fait grâce à un tableau d'entiers (keys) dont chaque élément
 *	correspond à une touche du clavier. Trois valeurs possibles :
 *			0		La touche n'est pas pressée
 *			1		La touche est pressée
 *			2		La touche est pressée et son effet a déjà été activé (throttle)
 *	Le throttle permet de ne pas activer l'effet d'un input à chaque frame pendant laquel-
 *	le la touche est pressée.
 */
const int BG_COLOR[] = {25,25,25};

// Touches de saisie du pourcentage
const SDL_Keycode K_10P = 38;
const SDL_Keycode K_20P = 233;
const SDL_Keycode K_30P = 34;
const SDL_Keycode K_40P = 39;
const SDL_Keycode K_50P = 40;
const SDL_Keycode K_60P = 45;
const SDL_Keycode K_70P = 232;
const SDL_Keycode K_80P = 95;
const SDL_Keycode K_90P = 231;
const SDL_Keycode K_100P = 224;
// Touches directionnelles
const SDL_Keycode K_RIGHT = 1073741903;
const SDL_Keycode K_LEFT = 1073741904;
const SDL_Keycode K_DOWN = 1073741905;
const SDL_Keycode K_UP = 1073741906;
const SDL_Keycode K_CTRL = 1073742048;

enum {
	UPDATE_INTERVAL = 1000/60
	, NB_SHIPS = 100
};

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

const string TERM_COLOR_WHITE		= "0;30";
const string TERM_COLOR_RED			= "0;31";
const string TERM_COLOR_GREEN		= "0;32";
const string TERM_COLOR_YELLOW	= "0;33";
const string TERM_COLOR_BLUE		= "0;34";
const string TERM_COLOR_BLACK		= "0;37";
const string END_COLOR					= "\033[m";

const string FONT_PATH			= "fonts/Welbut__.ttf";
const int FONT_SIZE_DEFAULT	= 12;

class Engine
{
public:
	Engine();
	~Engine();

	// Textures
	SDL_Texture* text_to_textureColor(
		const string &message,
		Uint32 color,
		const string &fontFile = FONT_PATH,
		Uint8 fontSize = FONT_SIZE_DEFAULT
	);
	SDL_Texture* text_to_textureRGBA(
		const string &message,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a,
		const string &fontFile = FONT_PATH,
		Uint8 fontSize = FONT_SIZE_DEFAULT
	);

	//----
	// Dessin
	void draw_textColor( const string &text, Point* pos, Uint32 color );
	void draw_textRGBA(
		const std::string &text,
		Point* pos,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a,
		const string &fontFile = FONT_PATH,
		Uint8 fontSize = FONT_SIZE_DEFAULT
	);
	void draw_texture( SDL_Texture* texture, Point* pos, Sint8 alpha = 255 );
	void draw_polygon( short int x[], short int y[], Sint8 n, Uint32 color );

	//----
	// Physique
	bool circleCollide( Point* pos1, Point* pos2, int size );

	//----
	// Divers
	void log( const string &message, const string &color = TERM_COLOR_BLACK );
	void log_error( const string &message );
	void update_display_mode();
	string multString( string str, Sint8 n );

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_DisplayMode display;
	std::map<int,int> keys;
	Point cursor;
	int click; // 0 = none, 1 = left, 2 = middle, 3 = right
	int amount;
};

#endif
