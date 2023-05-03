#include "lecture_fichier.hpp"

void lecture_fichier_nb(ch fic,grille_complete &grille){ //lit un fichier de la forme grille.nb avec n et p en en-tête (entrée)
    fif grille_fichier(fic);
    int e;
    if(grille_fichier){
        grille_fichier >> e;
        grille.n=e;
        grille.t=e*e;
        grille_fichier >> e;
        grille.p=e;
        for(int i=0;i<grille.n;++i){
            for(int j=0;j<grille.n;++j){
                grille_fichier >> e;
                grille.nb[i][j]=e;
            }
        }
    }
    else{
        std::cout<<"erreur lecture du fichier nb"<<std::endl;
    }
}

void lecture_fichier_sl(ch fic,grille_complete &grille){ //lit un fichier de la forme grille.sl, avec seulement les numéros (sortie dans le programme final, entrée ici)
    fif grille_fichier(fic);
    char e;
    if(grille_fichier){
        for(int i=0;i<grille.n;++i){
            for(int j=0;j<grille.n;++j){
                grille_fichier >> e;
                grille.sl[i][j]=e;
            }
        }
    }
    else{
        std::cout<<"erreur lecture du fichier sl"<<std::endl;
    }
}