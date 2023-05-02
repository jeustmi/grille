#include "plh.hpp"

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

void tri_selection(grille_complete & g,int n){  //tri les valeur de la grille
    tab_tri aux;
    for(int i=0; i<n; ++i){
        int maxi = 0;
        for(int j=0; j<n-i; j++){
            if (g.vt[maxi][0]<g.vt[j][0]){
                maxi = j;
            }
        }
        aux = g.vt[maxi];
        g.vt[maxi] =  g.vt[n-1-i];
        g.vt[n-1-i] =  aux;
    }

}

void init_sl(grille_complete & g){//inite la grille de solution avec des '1'
    for(int i=0; i<g.n ; ++i){
        for(int j=0; j<g.n ; ++j){
            g.sl[i][j]='1';
            
        }
    }
}

void placePionRouge(grille_complete & g){//place le pion rouge sur la case avec la plus petite valeur
    g.sl[g.vt[0][1]][g.vt[0][2]]='R';
}

void place_noir(grille_complete & g){
    int nn=0; //nn le nombre de noire placer
    int nt=0;
    int poi_tot,pen_tot,i,j;

    int t=g.n*g.n;
    bool n_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (n_placer and nt<t){
        if(g.vt[t-1-nt][0]>1){
            poi_tot=0;
            pen_tot=0;
            i=g.vt[t-1-nt][1];
            j=g.vt[t-1-nt][2];
            if((2*(g.vt[t-1-nt][0]-1)>poi_tot-pen_tot)){
                if(g.sl[i][j]=='1'){
                    g.sl[i][j]='N';
                    ++nn;
                }
            }
            else{
                if(g.sl[i][j]=='1'){
                    g.sl[i][j]='V';
                }
            }
            if(nn==g.n){
                n_placer = false;
            } 
        }
        else{
            n_placer = false;
        }
        
        ++nt;
    }
}