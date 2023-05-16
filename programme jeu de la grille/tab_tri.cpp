#include "tab_tri.hpp"

void init_tab_tri(grille_complete & grille){ //initialise la matrice qui contient les valeur de la grille et leur indice
    int k=0;
    for(int i=0; i<grille.n ; ++i){
        for(int j=0; j<grille.n ; ++j){
            grille.vt[k][0]=grille.nb[i][j];
            grille.vt[k][1]=i;
            grille.vt[k][2]=j;
            ++k;
        }
    }
}

void affiche_tab_tri(grille_complete grille){ //affiche les valeur de la grille et leur indice
    int k=0;
    for(int i=0; i<grille.n ; ++i){
        for(int j=0; j<grille.n ; ++j){
            //std::cout<<"valeur : "<<grille.vt[k][0]<<" i :"<<grille.vt[k][1]<<" j :"<<grille.vt[k][2]<<std::endl;
            ++k;
        }
    }
}

void tri_selection(grille_complete & grille){  //trie les valeur de la grille, selection
    tab_tri aux;
    for(int i=0; i<grille.t; ++i){
        int max = 0;
        for(int j=0; j<grille.t-i; j++){
            if (grille.vt[max][0]<grille.vt[j][0]){
                max = j;
            }
        }
        aux = grille.vt[max];
        grille.vt[max] = grille.vt[grille.t-1-i];
        grille.vt[grille.t-1-i] =  aux;
    }
}