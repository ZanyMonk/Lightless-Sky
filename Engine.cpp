#include "Engine.hpp"

using namespace std;

Engine::Engine()
{
	cursor = Point(0,0);
	amount = 100;
	click = false;
	update_display_mode();
}

Engine::~Engine()
{
}

//----
// Affiche un message dans la console.
void Engine::log( const string &message, const string &color )
{
	char buff[255];
	sprintf(buff, "\e[%sm%s", color.c_str(), message.c_str());
	cout << buff << END_COLOR << endl;
}

//----
// Affiche un message dans la console, en rouge et précédé du marqueur d'erreur
void Engine::log_error( const string &message )
{
	char buff[255];
	sprintf(buff, "%s%s", "[!] ", message.c_str());
	log(message, "red");
}

//----
// Met à jour l'objet SDL_DisplayMode de notre moteur
void Engine::update_display_mode()
{
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	display = dm;
}

//----
// Transforme une string en SDL_Texture
// Arguments :
//	string	message		Text à transformer
//	Uint32	color			Couleur 0xAARRGGBB
//	Uint8		fontSize	Taille de font
//	string	fontFile	Chemin vers la font (FONT_PATH par défaut)
SDL_Texture* Engine::text_to_textureColor(
	const string &message,
	Uint32 color,
	const string &fontFile,
	Uint8 fontSize
) {
	Uint8 *c = (Uint8 *) &color;
	SDL_Texture* texture =  text_to_textureRGBA(message, c[0], c[1], c[2], c[3], fontFile, fontSize);

	return texture;
}

//----
// Transforme une string en SDL_Texture
// Arguments :
//	string	message		Text à transformer
//	Uint8		r,g,b,a		Couleur
//	Uint8		fontSize	Taille de font
//	string	fontFile	Chemin vers la font (FONT_PATH par défaut)
SDL_Texture* Engine::text_to_textureRGBA(
	const string &message,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a,
	const string &fontFile,
	Uint8 fontSize
) {

	SDL_Color col = {r, g, b, a};

	TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);

	if ( font == nullptr ) {
		log_error("TTF_OpenFont");
		return nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), col);
	if ( surface == nullptr ) {
		TTF_CloseFont(font);
		log_error("TTF_RenderText");
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if ( texture == nullptr ) {
		log_error("CreateTexture");
	}

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	return texture;

}

void Engine::draw_textColor( const string &text, Point* pos, Uint32 color )
{
	/*
		Petit trick C
		On crée un Uint8 qui pointe vers un Uint32, ce qui nous donne un mot mémoire Uint32
		séparé en quatre mots Uint8 correspondants aux différents canaux (red, green, blue,
		alpha)
	*/
	Uint8 *c = (Uint8 *)&color;
	draw_textRGBA(text, pos, c[0], c[1], c[2], c[3]);
}

void Engine::draw_textRGBA(
	const string &text,
	Point* pos,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a,
	const string &fontFile,
	Uint8 fontSize
) {

  SDL_Texture* image = text_to_textureRGBA(text, r, g, b, a, fontFile, fontSize);

  if ( image == nullptr ) {
    log_error("Engine");
    TTF_Quit();
    SDL_Quit();
  }

	draw_texture( image, pos );

}

void Engine::draw_texture( SDL_Texture* texture, Point* pos, Sint8 alpha )
{
  int w, h;

  SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_SetTextureAlphaMod(texture, alpha);

  SDL_Rect dst;
	dst.w = w;
	dst.h = h;
	dst.x = pos->x-w/2;
	dst.y = pos->y-h/2;
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void Engine::draw_polygon( short int x[], short int y[], Sint8 n, Uint32 color )
{
	Sint16 x1 = x[0];
	Sint16 y1 = y[0];
	Sint16 x2, y2;

	for ( int i = 1; i <= n; i++ ) {
		x2 = (i == n ? x[0] : x[i]);
		y2 = (i == n ? y[0] : y[i]);
	  lineColor(
	    renderer,
	    x1, y1,
	    x2, y2,
	    color
	  );
		x1 = x[i];
		y1 = y[i];
	}
}

string Engine::multString( string str, Sint8 n )
{
	string res;

	for ( int i = 0; i < n; i++ ) {
		res += str;
	}

	return res;
}
