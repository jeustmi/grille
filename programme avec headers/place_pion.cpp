#include "place_pion.hpp"
#include "calcul_score.hpp"

void init_sl(grille_complete & g){//inite la grille de solution avec des '1'
    for(int i=0; i<g.n ; ++i){
        for(int j=0; j<g.n ; ++j){
            g.sl[i][j]='1';
            
        }
    }
}

void placePionRouge(grille_complete & g,int & dn){//place le pion rouge sur la case avec la plus petite valeur
    g.sl[g.vt[0][1]][g.vt[0][2]]='R';
    std::cout<<dn<<std::endl;
    ++dn;
    std::cout<<dn<<std::endl;
}

void place_noir(grille_complete & g,int & dp){
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

int recherche_min_positif(mat_tri mat,int t){
    int k=0;
    bool trouver=false;
    while(not trouver and k<t){
        if(mat[k][0]>0){
            trouver=true;
        }
        ++k;
    }
    return k-1;
}

void place_vert(grille_complete & g){
    mat_tri vert_mat;
    tab_tri vert_tab;
    int poi,pen,i,j,vn;
    vn=0;
    for(i=0;i<g.n;i++){
        for(j=0;j<g.n;j++){
            if(g.sl[i][j]=='1'){
                poi=0;
                pen=0;
                jeton_v(g,poi,pen,i,j);
                vert_tab={poi,i,j};
                ++vn;
                int k;
                k=vn-1;
                while ((k>0) and (vert_mat[k-1][0] > vert_tab[0])){
                    vert_mat[k] = vert_mat[k-1];
                    --k;
                }
                vert_mat[k] = vert_tab;
                /*for(int i=0;i<vn;i++){
                    std::cout<<"val "<<vert_mat[i][0]<<" i "<<vert_mat[i][1]<<" j "<<vert_mat[i][2]<<std::endl;
                }
                std::cout<<std::endl;*/
            }
        }
    }
    i=vn-1;
    int a;
    a=recherche_min_positif(vert_mat,g.t);
    while(i>=a){
        pen=0;
        jeton_v(g,poi,pen,vert_mat[i][1],vert_mat[i][2]);
        g.sl[vert_mat[i][1]][vert_mat[i][2]]='V';
        --i;
    }
    std::array<std::array<int,16>,1024> truc;
    std::array<int,16> truk;
    i=vn-1;
    int w=0;
    while(i>=a){
        ++w;
        g.sl[vert_mat[i][1]][vert_mat[i][2]]='v';
        poi=0;
        pen=0;
        j=vn-1;
        while(j>=a){
            if(j!=i){
                jeton_v(g,poi,pen,vert_mat[j][1],vert_mat[j][2]);
            }
            --j;
        }
        truk={poi-pen,vert_mat[i][1],vert_mat[i][2]};
        j=w-1;
        while ((j>0) and (truc[j-1][0] < truk[0])){
            truc[j] = truc[j-1];
            --j;
        }
        truc[j]=truk;/*
        for(j=0;j<w;++j){
            std::cout<<truc[j][0]<<" "<<truc[j][1]<<" "<<truc[j][2]<<std::endl;
        }*/
        g.sl[vert_mat[i][1]][vert_mat[i][2]]='V';
        --i;
    }
    g.sl[truc[0][1]][truc[0][2]]='1';
}

void place_orange(grille_complete & g,int & dn){
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
            if((pen_tot_o==0 and -g.nb[i][j]>p_v)){
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

void place_orange2(grille_complete & g,int & dn){
    int pen_tot_o,poi_tot_v,pen_tot_v,i,j,p_v;
    int a;
    a=recherche_min_positif(g.vt,g.t);
    //bool o_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    std::cout<<dn<<std::endl;
    while(dn<a){
        /*poi_tot_v=0;
        pen_tot_v=0;*/
        pen_tot_o=0;
        i=g.vt[dn][1];
        j=g.vt[dn][2];
        //jeton_v(g,poi_tot_v,pen_tot_v,i,j);
        //p_v=poi_tot_v-(pen_tot_v);
        jeton_o(g,pen_tot_o,i,j);
        if(pen_tot_o==0){
            if(g.sl[i][j]=='1'){
                g.sl[i][j]='O';
            }
        }
        /*else if(p_v>0){
            if(g.sl[i][j]=='1'){
                g.sl[i][j]='V';
            }
        }*/

        ++dn;
    }
}

void place_orange3(grille_complete & g,int & dn){
    int a;
    a=recherche_min_positif(g.vt,g.t);
    while(dn<a){
        //programmation par contrainte
        ++dn;
    }
}

void place_bleu(grille_complete & g,int & dn){
    int vb,poi_tot1,pen_tot1,poi_tot2,pen_tot2,i1,j1,i2,j2,k;
    
    bool b_placer = true;
    
    k=recherche_min_positif(g.vt,g.t);
    while (b_placer and dn!=k){
        poi_tot1=0;
        pen_tot1=0;
        i1=g.vt[dn][1];
        j1=g.vt[dn][2];
        jeton_v(g,poi_tot1,pen_tot1,i1,j1);
        poi_tot2=0;
        pen_tot2=0;
        i2=g.vt[k-1+dn][1];
        j2=g.vt[k-1+dn][2];
        jeton_v(g,poi_tot2,pen_tot2,i2,j2);
        vb=g.vt[k-1+dn][0]-g.vt[dn][0];
        if(vb>=0){
            if(vb<poi_tot1-pen_tot1){
                if(g.sl[i1][j1]=='1'){
                    g.sl[i1][j1]='V';
                    ++dn;
                    --k;
                }
            }
            else if(vb<poi_tot2-pen_tot2){
                if(g.sl[i2][j2]=='1'){
                    g.sl[i2][j2]='V';
                    ++k;
                }
            }
            else{
                if(g.sl[i1][j1]=='1' and g.sl[i2][j2]=='1'){
                    g.sl[i1][j1]='B';
                    g.sl[i2][j2]='B';
                }
            }
        }
        else{
            b_placer = false;
        }

        ++dn;
    }
}

void place_jaune(grille_complete & g,int & dp){
    int poi_tot_j,pen_tot_j,poi_tot_v,pen_tot_v,i,j;

    bool j_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (j_placer and dp<g.t){
        if(g.vt[g.t-1-dp][0]>=0){
            poi_tot_v=0;
            pen_tot_v=0;
            poi_tot_j=0;
            pen_tot_j=0;
            i=g.vt[g.t-1-dp][1];
            j=g.vt[g.t-1-dp][2];
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
        
        ++dp;
    }
}

void place_zero(grille_complete & g){
    int m=recherche_min_positif(g.vt,g.t)-1,poi_j,pen_j,poi_v,pen_v,i=g.vt[m][1],j=g.vt[m][2];
    
    bool fin=true;
    while(fin){
        if(g.vt[m][0]==0 and g.sl[i][j]=='1'){
            jeton_v(g,poi_v,pen_v,i,j);
            jeton_j(g,poi_j,pen_j,i,j);
            if(poi_v-pen_v>0){
                g.sl[i][j]='V';
            }
            else if(pen_j==0){
                g.sl[i][j]='J';
            }
            else{
                g.sl[i][j]='B';
            }
            --m;
        }
        else{
            fin=false;
        }
    }
}