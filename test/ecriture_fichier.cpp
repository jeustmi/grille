#include "ecriture_fichier.hpp"
#include "calcul_score.hpp"

void écriture_fichier_solution(grille_complète grille, ch fic){
    fof sol(fic); //recrée un fichier solution, avec cette fois-ci le score à la fin, comme attendu
    if(sol){
        for(int i=0;i<grille.n;++i){
            for(int j=0;j<grille.n;++j){
                sol << grille.sl[i][j];
            }
            sol << std::endl;
        }
        sol << calcul_score(grille);
    }
    else{
        std::cout<<"erreur à l'écriture du fichier"<<std::endl;
    }
}