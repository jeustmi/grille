#include "plh.hpp"
#include "calcul_score.hpp"

void init_sl(grille_complete & g){//init la grille de solution avec des '1'
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
    mat_tri vert_t;
    int abc=0,poi_v,serarien;
    int nn=0; //nombre de noirs placés
    int nt=0;
    int poi_tot,pen_tot,i,j;

    int t=g.n*g.n;
    bool n_placer = true; //vrai tant que tout les noir ne sont pas placés correctement
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
                poi_v=0;
                jeton_v(g,poi_v,serarien);
                vert_t[abc][0]=poi_v;
                vert_t[abc][1]=i;
                vert_t[abc][2]=j;
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