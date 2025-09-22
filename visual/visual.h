#ifndef VISUAL_H
#define VISUAL_H

int init_SDL();                    // initialise SDL et crée la fenêtre + renderer
void afficher_tableau(int* tab, int taille); // affiche un tableau d'entiers en colonnes
void fermer_SDL();                  // nettoie SDL

#endif
