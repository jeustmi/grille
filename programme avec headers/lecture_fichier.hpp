#include <fstream>
#include <string>

#include "struct.hpp"

using fif=std::ifstream;
using fof=std::ofstream;
using ch=std::string;

void lecture_fichier_nb(ch fic,grille_complete &grille);
void lecture_fichier_sl(ch fic,grille_complete &grille);