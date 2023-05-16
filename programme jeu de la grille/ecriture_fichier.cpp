#include <fstream>

#include "ecriture_fichier.hpp"
#include "calcul_score.hpp"

void écriture_fichier_solution(grille_complete grille, ch fic){
    int score;
    fof sol(fic); //recrée un fichier solution, avec cette fois-ci le score à la fin, comme attendu
    
    calcul_score(grille,score);

    if(sol){
        for(int i=0;i<grille.n;++i){
            for(int j=0;j<grille.n;++j){
                sol << grille.sl[i][j];
            }
            sol << std::endl;
        }
        sol << score;
    }
    else{
        std::cout<<"erreur à l'écriture du fichier"<<std::endl;
    }
}
