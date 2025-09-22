#ifndef VISUAL_H
#define VISUAL_H

int init_SDL();                    // Initializes SDL and creates window + renderer
void afficher_tableau(int* tab, int taille, int highlight1, int highlight2); // Displays array as bars, with optional highlights
void fermer_SDL();                  // Cleans up SDL

#endif