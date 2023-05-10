#include "tab_tri.hpp"

void init_tab_tri(grille_complete & g){ //initialise la matrice qui contient les valeur de la grille et leur indice
    int k=0;
    for(int i=0; i<g.n ; ++i){
        for(int j=0; j<g.n ; ++j){
            g.vt[k][0]=g.nb[i][j];
            g.vt[k][1]=i;
            g.vt[k][2]=j;
            ++k;
        }
    }
}

void affiche_tab_tri(grille_complete g){ //affiche les valeur de la grille et leur indice
    int k=0;
    for(int i=0; i<g.n ; ++i){
        for(int j=0; j<g.n ; ++j){
            std::cout<<"valeur : "<<g.vt[k][0]<<" i :"<<g.vt[k][1]<<" j :"<<g.vt[k][2]<<std::endl;
            ++k;
        }
    }
}

void tri_selection(grille_complete & g){  //trie les valeur de la grille, selection
    tab_tri aux;
    for(int i=0; i<g.t; ++i){
        int max = 0;
        for(int j=0; j<g.t-i; j++){
            if (g.vt[max][0]<g.vt[j][0]){
                max = j;
            }
        }
        aux = g.vt[max];
        g.vt[max] = g.vt[g.t-1-i];
        g.vt[g.t-1-i] =  aux;
    }
}