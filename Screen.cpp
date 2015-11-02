#include "Screen.hpp"

/*----
* Classe "Screen", classe d'abstraction pour tous les écrans du projet.
* /!\ Toutes les classes héritières doivent être équipées d'une méthode "draw" /!\
*/

Screen::Screen( Engine* E )
:E(E)
{
  if ( TTF_Init() == -1 ) {
    cout << "[!] TTF_Init" << endl;
    exit(EXIT_FAILURE);
  }
}

Screen::~Screen()
{

}
