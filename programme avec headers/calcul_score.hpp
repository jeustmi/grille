#include "struct.hpp"

void jeton_j(grille_complete grille, int &poi_tot, int &pen_tot, int i, int j);
void jeton_v(grille_complete &grille, int &poi_tot, int &pen_tot, int i, int j);
void jeton_n(grille_complete grille, int &poi_tot, int i, int j);
void jeton_r(grille_complete grille, int &poi_tot, int i, int j);
void jeton_b(grille_complete grille, int &pen_tot, int i, int j);
void jeton_o(grille_complete &grille, int &pen_tot, int i, int j);

int calcul_score(grille_complete &grille);
