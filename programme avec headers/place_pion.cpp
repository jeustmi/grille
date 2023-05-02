#include "place_pion.hpp"
#include "calcul_score.hpp"

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
            jeton_v(g,poi_tot,pen_tot,i,j);
            //std::cout<<"pen_tot"<<pen_tot<<" poi_tot"<<poi_tot<<std::endl;
            if((2*(g.vt[t-1-nt][0]-1)>poi_tot-(pen_tot))){
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
void place_orange(grille_complete & g){
    int nt=1;
    int pen_tot_o,poi_tot_v,pen_tot_v,i,j,p_v;
    int t=g.n*g.n;
    bool n_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (n_placer and nt<t){
        if(g.vt[nt][0]<0){
            poi_tot_v=0;
            pen_tot_v=0;
            pen_tot_o=0;
            i=g.vt[nt][1];
            j=g.vt[nt][2];
            jeton_v(g,poi_tot_v,pen_tot_v,i,j);
            jeton_o(g,pen_tot_o,i,jZ);
            p_v=poi_tot_v-(pen_tot_v);
            if((pen_tot_o==0 and (pen_tot_o)<=p_v)){
                if(g.sl[i][j]=='1'){
                    g.sl[i][j]='O';
                }
            }
            else if(p_v>0){
                if(g.sl[i][j]=='1'){
                    g.sl[i][j]='V';
                }
            }
        }
        else{
            n_placer = false;
        }
        
        ++nt;
    }
}
void place_jaune(grille_complete & g){
    int nt=0;
    int poi_tot_j,pen_tot_j,poi_tot_v,pen_tot_v,i,j;

    int t=g.n*g.n;
    bool n_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (n_placer and nt<t){
        if(g.vt[t-1-nt][0]>0){
            poi_tot_v=0;
            pen_tot_v=0;
            poi_tot_j=0;
            pen_tot_j=0;
            i=g.vt[t-1-nt][1];
            j=g.vt[t-1-nt][2];
            jeton_v(g,poi_tot_v,pen_tot_v,i,j);
            jeton_j(g,poi_tot_j,pen_tot_j,i,j);
            if((poi_tot_j-pen_tot_j>poi_tot_v-pen_tot_v)){
                if(g.sl[i][j]=='1'){
                    g.sl[i][j]='J';
                }
            }
            else{
                if(g.sl[i][j]=='1'){
                    g.sl[i][j]='V';
                }
            }
        }
        else{
            n_placer = false;
        }
        
        ++nt;
    }
}

