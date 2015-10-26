> /!\ Ce programme ne fonctionne pas /!\
> /!\ This is no working program /!\

Lightless Sky
===
Un jeu de stratégie minimaliste dans un univers de science-fiction. Une introduction scénaristique viendra bientôt agrémenter cette page.

![Lightless Sky - screenshot](http://i.imgur.com/AUdHDfF.png)

Compilation
---
### Linux
Cette commande devrait faire l'affaire pour compiler le bouzin. Vous aurez besoin de la SDL2, version développeur.
`g++ -Wall -g -std=c++11 main.cpp SDL2_gfxPrimitives.c SDL2_rotozoom.c Engine.cpp Game.cpp Screen.cpp Interface.cpp Planet.cpp Ship.cpp Utils.cpp -Wall -w -lSDL2 -o test && ./test`
