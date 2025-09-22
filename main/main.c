#include "../visual/visual.h"
#include <SDL2/SDL.h>
#include "../visual/visual.h"

int main() {
    if (!init_SDL()) return 1;

    int tableau[] = {5, 2, 8, 3, 7}; // tableau fixe
    int taille = 5;

    afficher_tableau(tableau, taille);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }
    }

    fermer_SDL();
    return 0;
}
