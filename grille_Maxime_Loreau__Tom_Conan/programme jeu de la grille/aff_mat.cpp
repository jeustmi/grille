#include "aff_mat.hpp"

void affichage_mat_nb(mat_nb grille,int n){ //affiche une matrice d'int
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            std::cout<<grille[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void affichage_mat_sl(mat_sl grille,int n){ //affiche une matrice de char
    for(int k=0;k<n;++k){
        for(int l=0;l<n;++l){
            std::cout<<grille[k][l]<<" ";
        }
        std::cout<<std::endl;
    }
}