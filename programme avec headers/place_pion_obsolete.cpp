#include "place_pion.hpp"
#include "calcul_score.hpp"

void init_sl(grille_complete & g){//inite la grille de solution avec des '1'
    for(int i=0; i<g.n ; ++i){
        for(int j=0; j<g.n ; ++j){
            g.sl[i][j]='1';
            
        }
    }
}

void placePionRouge(grille_complete & g,int dn){//place le pion rouge sur la case avec la plus petite valeur
    g.sl[g.vt[0][1]][g.vt[0][2]]='R';
    ++dn;
}

void place_noir(grille_complete & g,int dp){
    mat_tri vert_mat;
    tab_tri vert_tab;
    int vn=0,poi_v,serarien;
    int nn=0; //nn le nombre de noire placer
    int poi_tot,pen_tot,i,j;

    bool n_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
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

void place_orange(grille_complete & g,int dn){
    int pen_tot_o,poi_tot_v,pen_tot_v,i,j,p_v;
    bool o_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (o_placer and dn<g.t){
        if(g.vt[dn][0]<0){
            poi_tot_v=0;
            pen_tot_v=0;
            pen_tot_o=0;
            i=g.vt[dn][1];
            j=g.vt[dn][2];
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
        
        ++dn;
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

void place_orange2(grille_complete & g,int & dn){
    int pen_tot_o,poi_tot_v,pen_tot_v,i,j,p_v;
    int a;
    a=recherche_min_positif(g);
    //bool o_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while(dn<a){
        poi_tot_v=0;
        pen_tot_v=0;
        pen_tot_o=0;
        i=g.vt[dn][1];
        j=g.vt[dn][2];
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
        ++dn;
    }
}

void place_bleu(grille_complete & g,int dn){
    int vb,poi_tot1,pen_tot1,poi_tot2,pen_tot2,i1,j1,i2,j2,k;
    
    bool b_placer = true;
    
    k=recherche_min_positif(g); int nt;
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
    int poi_tot_j,pen_tot_j,poi_tot_v,pen_tot_v,i,j; int nt;

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