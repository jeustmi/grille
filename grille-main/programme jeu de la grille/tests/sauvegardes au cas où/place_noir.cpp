#include "../../place_pion.hpp"
#include "../../calcul_score.hpp"

void place_noir(grille_complete & g,int & dp){
    mat_tri vert_mat;
    tab_tri vert_tab;
    int vn=0,poi_v,serarien;
    int nn=0; //nombre de noirs places
    int poi_tot,pen_tot,i,j;

    bool n_placer = true; //est vrai tant que tout les noirs ne sont pas places correctement
    while (n_placer and dp<g.t){
        if(g.vt[g.t-1-dp][0]>2){
            poi_tot=0;
            pen_tot=0;
            i=g.vt[g.t-1-dp][1];
            j=g.vt[g.t-1-dp][2];
            jeton_v(g,poi_tot,pen_tot,i,j);
            //std::cout<<"pen_tot"<<pen_tot<<" poi_tot"<<poi_tot<<std::endl;
            if((2*(g.vt[g.t-1-dp][0]-1)>poi_tot-(pen_tot))){
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
                jeton_v(g,poi_v,serarien,i,j);
                vert_tab={poi_v,i,j};
                ++vn;
                int k;
                k=vn-1;
                while ((k > 0) and (vert_mat[k-1][0] > vert_tab[0])){
                    vert_mat[k] = vert_mat[k-1];
                    --k;
                }
                vert_mat[k] = vert_tab;
            }
            if(nn==g.n){
                n_placer = false;
            } 
        }
        else{
            n_placer = false;
        }
        ++dp;
    }
}
