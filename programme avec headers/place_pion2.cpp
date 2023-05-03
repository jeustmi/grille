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
    mat_tri vert_mat;
    tab_tri vert_tab;
    int vn=0,poi_v,serarien;
    int nn=0; //nn le nombre de noire placer
    int nt=0;
    int poi_tot,pen_tot,i,j;

    bool n_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (n_placer and nt<g.t){
        if(g.vt[g.t-1-nt][0]>1){
            poi_tot=0;
            pen_tot=0;
            i=g.vt[g.t-1-nt][1];
            j=g.vt[g.t-1-nt][2];
            jeton_v(g,poi_tot,pen_tot,i,j);
            //std::cout<<"pen_tot"<<pen_tot<<" poi_tot"<<poi_tot<<std::endl;
            if((2*(g.vt[g.t-1-nt][0]-1)>poi_tot-(pen_tot))){
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
        ++nt;
    }
}

void place_orange(grille_complete & g){
    int nt=1;
    int pen_tot_o,poi_tot_v,pen_tot_v,i,j,p_v;
    bool o_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (o_placer and nt<g.t){
        if(g.vt[nt][0]<0){
            poi_tot_v=0;
            pen_tot_v=0;
            pen_tot_o=0;
            i=g.vt[nt][1];
            j=g.vt[nt][2];
            jeton_v(g,poi_tot_v,pen_tot_v,i,j);
            jeton_o(g,pen_tot_o,i,j);
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
            o_placer = false;
        }
        
        ++nt;
    }
}

int recherche_min_positif(grille_complete g){
    int k=0;
    bool trouver=false;
    while(not trouver and k<g.t){
        if(g.vt[k][0]>0){
            trouver=true;
        }
        ++k;
    }
    return k-1;
}

void place_orange2(grille_complete & g){
    int mini=1;
    int pen_tot_o,poi_tot_v,pen_tot_v,i,j,p_v;
    int a;
    a=recherche_min_positif(g);
    //bool o_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while(mini<a){
        poi_tot_v=0;
        pen_tot_v=0;
        pen_tot_o=0;
        i=g.vt[mini][1];
        j=g.vt[mini][2];
        jeton_v(g,poi_tot_v,pen_tot_v,i,j);
        p_v=poi_tot_v-(pen_tot_v);
        jeton_o(g,pen_tot_o,i,j);
        if(pen_tot_o==0){
            if(g.sl[i][j]=='1'){
                g.sl[i][j]='O';
            }
        }
        else if(p_v>0){
            if(g.sl[i][j]=='1'){
                g.sl[i][j]='V';
            }
        }
        ++mini;
    }
}

void place_bleu(grille_complete & g){
    int nt=1;
    int vb,poi_tot1,pen_tot1,poi_tot2,pen_tot2,i1,j1,i2,j2,k;
    
    bool b_placer = true;
    
    k=recherche_min_positif(g);
    while (b_placer and nt!=k){
        poi_tot1=0;
        pen_tot1=0;
        i1=g.vt[nt][1];
        j1=g.vt[nt][2];
        jeton_v(g,poi_tot1,pen_tot1,i1,j1);
        poi_tot2=0;
        pen_tot2=0;
        i2=g.vt[k-1+nt][1];
        j2=g.vt[k-1+nt][2];
        jeton_v(g,poi_tot2,pen_tot2,i2,j2);
        vb=g.vt[k-1+nt][0]-g.vt[nt][0];
        std::cout<<"vb :"<<vb<<std::endl;
        if(vb>=0 and vb>=(poi_tot1-pen_tot1)+(poi_tot2-pen_tot2)){
            std::cout<<"afqb";
            if(g.sl[i1][j1]=='1' and g.sl[i2][j2]=='1'){
                g.sl[i1][j1]='B';
                g.sl[i2][j2]='B';
            }
        }
        else if (vb>0) {
            if(vb<poi_tot1-pen_tot1){
                if(g.sl[i1][j1]=='1'){
                g.sl[i1][j1]='V';
                }
            }
            else if(vb<poi_tot2-pen_tot2){
                if(g.sl[i2][j2]=='1'){
                g.sl[i2][j2]='V';
                }
            }
        }
        else{
            b_placer = false;
        }
        
        ++nt;
    }
}

void place_jaune(grille_complete & g){
    int nt=0;
    int poi_tot_j,pen_tot_j,poi_tot_v,pen_tot_v,i,j;

    bool j_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (j_placer and nt<g.t){
        if(g.vt[g.t-1-nt][0]>0){
            poi_tot_v=0;
            pen_tot_v=0;
            poi_tot_j=0;
            pen_tot_j=0;
            i=g.vt[g.t-1-nt][1];
            j=g.vt[g.t-1-nt][2];
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
            j_placer = false;
        }
        
        ++nt;
    }
}