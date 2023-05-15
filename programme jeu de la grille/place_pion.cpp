#include "place_pion.hpp"
#include "calcul_score.hpp"

void init_sl(grille_complete & g){//init la grille de solution avec des '1'
    for(int i=0; i<g.n ; ++i){
        for(int j=0; j<g.n ; ++j){
            g.sl[i][j]='1';
        }
    }
}

int recherche_min_positif_mat(mat_tri mat, int t){
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

int recherche_min_positif(grille_complete & g){
    int k=0;
    bool trouver=false;
    while(not trouver and k<g.t){
        if(g.vt[k][0]>0 and g.sl[g.vt[k][1]][g.vt[k][2]]=='1'){
            trouver=true;
        }
        ++k;
    }
    return k-1;
}

int trouve_dn(grille_complete & g, int dn){
    bool trouve_n = false;
    dn=0;
    for(int i=1;i<g.t-1;++i){
        if(trouve_n==false and g.sl[g.vt[i][1]][g.vt[i][2]]=='1'){
            dn=i;
            trouve_n=true;
        }
    }
    return dn;
}

int trouve_dp(grille_complete & g, int dp){
    bool trouve_p = false;
    dp=0;
    for(int i=0;i<g.t-1;++i){
        if(trouve_p==false and g.sl[g.vt[i][1]][g.vt[i][2]]=='1'){
            dp=i;
            trouve_p=true;
        }
    }
    return dp;    
}

void placePionRouge(grille_complete & g,int & dn){//place le pion rouge sur la case avec la plus petite valeur
    g.sl[g.vt[0][1]][g.vt[0][2]]='R';
    ++dn;
}

void place_noir(grille_complete & g,int & dp){
    mat_tri vert_mat;
    tab_tri vert_tab;
    int vn=0,poi_v,cette_variable_est_utilisee_dans_jeton_v_mais_en_fait_on_sen_sert_pas_apres_du_coup_je_lappelle_comme_ca;
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
                jeton_v(g,poi_v,cette_variable_est_utilisee_dans_jeton_v_mais_en_fait_on_sen_sert_pas_apres_du_coup_je_lappelle_comme_ca,i,j);
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

using vect_co=std::array<int,3>; //contient les coordonnées d'un pion enlevé en position 0 et 1 et la boucle à laquelle il a été enlevé
using mat2=std::array<vect_co,750>; //contient une combinaison de pions, avec le score en position 0, le nombre de pions enlevés de cette combinaison en position 1 et chaque pion enlevé aux positions suivantes
using mat3=std::array<mat2,750>; //contient les combinaisons testées à l'instant, triées en fonction du score à partir de la position 1, et avec la meilleure combinaison d'avant en position 0

            //cette fonction teste les meilleures combinaisons de verts à partir de toutes les cases possibles
void compte_vert(grille_complete & g, mat3 & val_comb_vert, mat_tri & vert_pos_mat, int vpm_n, bool & fin){
    int n;
    n=val_comb_vert[0][1][0]; //on initialise n au nombre de verts enlevés dans les tests
    for(int i=0;i<vpm_n-n;++i){ //on lance une boucle qui enleve chaque jeton restant un à un pour calculer le score, n augmentera donc forcément de 1
        int poi=0;
        int pen=0;
        mat2 val_1comb;
        val_1comb=val_comb_vert[0]; //on fait cette affectation pour garder en mémoire les pions deja enleves, on rajoutera par la suite celui qu'on enleve a cette boucle a la fin de val_comb_vert et on changera n en n+1 (pos 1) et le score en fonction (pos 0)
        val_1comb[1][0]=n+1; //de fait, on enleve 1 pion de plus qu'a la boucle while d'avant (voir la fonction place_vert)
        g.sl[vert_pos_mat[i][0]][vert_pos_mat[i][1]]='v'; //on teste d'enlever un des pions verts
        val_1comb[2+n][0]=vert_pos_mat[i][0]; val_1comb[2+n][1]=vert_pos_mat[i][1]; val_1comb[2+n][2]=i; //on rajoute ses coordonnées à la fin de val_1comb 
        
        for(int j=0;j<vpm_n-n;++j){ //on compte les points des verts non enleves
            if(j!=i){
                jeton_v(g,poi,pen,vert_pos_mat[j][0],vert_pos_mat[j][1]);
                g.sl[vert_pos_mat[j][0]][vert_pos_mat[j][1]]='v';
            }
        }

        for(int j=0;j<vpm_n-n;++j){ //on replace les verts non enleves (on les remplace temporairement par 'v' pour le comptage)
            if(j!=i){
                g.sl[vert_pos_mat[j][0]][vert_pos_mat[j][1]]='V';
            }
        }

        //boucle de test 
        /*std::cout<<std::endl<<pen<<" "<<poi<<std::endl<<std::endl;
        for(int k=0;k<g.n;++k){
            for(int l=0;l<g.n;++l){
                std::cout<<g.sl[k][l]<<" ";
            }
        std::cout<<std::endl;
        }*/
        //std::cout<<vert_pos_mat[i][0]<<" "<<vert_pos_mat[i][1]<<std::endl;

        g.sl[vert_pos_mat[i][0]][vert_pos_mat[i][1]]='V'; //on replace le vert enleve (on ne le fait pas avant pour pouvoir faire une vérification avec des std::cout)
        val_1comb[0][0]=poi-pen; //on rentre le score de cette combinaison

        int j=i+1;
        while ((j>1) and (val_comb_vert[j-1][0][0] < val_1comb[0][0])){ //on trie par insertion les meilleures combinaisons de cette boucle
            val_comb_vert[j] = val_comb_vert[j-1];
            --j;
        }
        val_comb_vert[j]=val_1comb;
    }
    
    int j=val_comb_vert[1][2+n][2]; //on met le pion eleve donnant le plus grand score a la fin de notre liste pour pouvoir ne plus le compter après
    tab_tri temp;
    temp=vert_pos_mat[j];
    while (j<vpm_n){
        vert_pos_mat[j] = vert_pos_mat[j+1];
        ++j;
    }
    vert_pos_mat[j]=temp;
    if(val_comb_vert[1][0][0]>=val_comb_vert[0][0][0]){ //si la combinaison actuelle est meilleure que celle d'avant, on recommence
        val_comb_vert[0]=val_comb_vert[1];
        g.sl[val_comb_vert[0][2+n][0]][val_comb_vert[0][2+n][1]]='1';
    }
    else{ //sinon, on arrete
        fin=true;
    }
}

void place_vert(grille_complete & g){
    mat_tri vert_mat;
    tab_tri vert_tab;
    int poi,pen,i,j,vn;
    vn=0;
    for(i=0;i<g.n;i++){ 
        for(j=0;j<g.n;j++){
            if(g.sl[i][j]=='1' or g.sl[i][j]=='V'){ //on regarde toutes les cases non prises
                poi=0;
                pen=0;
                jeton_v(g,poi,pen,i,j); //on compte les points de cette case si on mettait un vert dessus
                vert_tab={poi,i,j};
                ++vn;
                int k;
                k=vn-1;
                while ((k>0) and (vert_mat[k-1][0] > vert_tab[0])){ //on trie par score
                    vert_mat[k] = vert_mat[k-1];
                    --k;
                }
                vert_mat[k] = vert_tab;
            }
        }
    }
    mat_tri vert_pos_mat;
    int a, vpm_n=0;
    poi=0;
    pen=0;
    i=vn-1;
    a=recherche_min_positif_mat(vert_mat,g.t);
    while(i>=a){ //on ne garde que les meilleures cases (celles rapportant un score positif)
        jeton_v(g,poi,pen,vert_mat[i][1],vert_mat[i][2]);
        g.sl[vert_mat[i][1]][vert_mat[i][2]]='V'; //on pose un jeton sur chacune de ces cases
        vert_pos_mat[vpm_n]={vert_mat[i][1],vert_mat[i][2]};
        ++vpm_n;
        --i;
    }
    mat3 val_comb_vert;
    val_comb_vert[0]={poi-pen,-2,-2,0,-2,-2}; //on initialise val_comb_vert
    bool fin=false;
    while(fin==false){ //on lance le programme pour trouver la meilleure combinaison de verts parmi ceux posés au début
        compte_vert(g,val_comb_vert,vert_pos_mat,vpm_n,fin);
        if(val_comb_vert[0][1][0]==vpm_n){
            fin=true;
        }
    }
}

void place_orange(grille_complete & g,int & dn){ //place la meilleure position des oranges, dans certains cas
    mat_tri or_mat;
    tab_tri or_tab;
    int or_mat_n,a,k,i,pen;
    dn=trouve_dn(g,dn);
    a=recherche_min_positif(g);
    a=a-dn;
    //std::cout<<dn<<" "<<a<<std::endl;
    or_mat_n=0;
    i=dn;
    while(i<dn+a){
        if(g.sl[g.vt[i][1]][g.vt[i][2]]=='1'){
            g.sl[g.vt[i][1]][g.vt[i][2]]='O';
            or_mat[or_mat_n][1]=g.vt[i][1];
            or_mat[or_mat_n][2]=g.vt[i][2];
            ++or_mat_n;
        }
        ++i;
    }
    /*for(int i=dn;i<dn+a;i++){
        or_mat[k][0]=g.vt[i][1];
        or_mat[k][1]=g.vt[i][2];
        ++k;
    }*/
    bool fin=false;
    or_mat[or_mat_n-1][0]=42;
    while(fin==false){
        if(or_mat[or_mat_n-1][0]!=0){
            g.sl[or_mat[or_mat_n-1][1]][or_mat[or_mat_n-1][2]]='1';
            --or_mat_n;
            for(int i=0;i<or_mat_n;++i){
                pen=0;
                jeton_o(g,pen,or_mat[i][1],or_mat[i][2]);
                or_tab[0]=pen;
                or_tab[1]=or_mat[i][1];
                or_tab[2]=or_mat[i][2];
                k=i;
                while ((k>0) and (or_mat[k-1][0] > or_tab[0])){
                    or_mat[k] = or_mat[k-1];
                    --k;
                }
                or_mat[k] = or_tab;   
            }
        }
        else{
            fin=true;
        }
    }
}

void place_bleu(grille_complete & g,int & dn){
    int vb,i1,j1,i2,j2,k,rien;
    bool b_placer = true;
    
    dn=trouve_dn(g,dn);
    k=recherche_min_positif(g);
    
    while (b_placer){
        dn=trouve_dn(g,dn);
        k=recherche_min_positif(g);
        i1=g.vt[dn][1];
        j1=g.vt[dn][2];
        i2=g.vt[k][1];
        j2=g.vt[k][2];
        if(g.vt[k][0]>0 and g.vt[dn][0]>0){
            vb=g.vt[k][0]-g.vt[dn][0]-g.p;
        }
        else{
            vb=g.vt[k][0]-g.vt[dn][0];
        }
        if(dn==k){
            b_placer = false;
        }
        else if(g.sl[i1][j1]!='1' or g.sl[i2][j2]!='1'){
            b_placer = false;
        }
        else{
            if(vb>=0){
                if(g.sl[i1][j1]=='1' and g.sl[i2][j2]=='1'){
                    g.sl[i1][j1]='B';
                    g.sl[i2][j2]='B';
                }
            }
        }
    }
}

/*void place_jaune(grille_complete & g,int & dp){
    int poi_tot_j,pen_tot_j,i,j,rien;
    dp=trouve_dp(g,dp);
    bool j_placer = true; //est vrais tant que tout les noir ne sont pas placer correctement
    while (j_placer and dp<g.t and dp>1){
        dp=trouve_dp(g,dp);
        poi_tot_j=0;
        pen_tot_j=0;
        i=g.vt[dp][1];
        j=g.vt[dp][2];
        std::cout<<" i: "<<i<<" j: "<<j<<std::endl;
        jeton_j(g,poi_tot_j,pen_tot_j,i,j);
        std::cout<<"poi_tot_j-pen_tot_j : "<<poi_tot_j-pen_tot_j<<std::endl;
        
        if(g.sl[i][j]!='1'){
            j_placer = false;
        }

        else if(poi_tot_j-pen_tot_j>=-g.p){
             std::cout<<"cc"<<std::endl;
            if(g.sl[i][j]=='1'){
                g.sl[i][j]='J';
            }
    
        }
        else{
            j_placer = false;
        }
    }
}*/

void place_jaune(grille_complete & g){
    int i,j;
    for(int h=0; h<g.t ; ++h){
        i=g.vt[h][1];
        j=g.vt[h][2];
        if(g.sl[i][j]=='1'){
            g.sl[i][j]='J';
        }
    }
    int poi,pen;
    for(int i=0;i<g.n;++i){
        for(int j=0;j<g.n;j++){
            poi=0;
            pen=0;
            if(g.sl[i][j]=='J'){
                jeton_j(g,poi,pen,i,j);
                if(pen>0 and poi<g.p){
                    g.sl[i][j]='B';
                }
            }
        }
    }
}

void place_zero(grille_complete & g){
    int m=recherche_min_positif(g)-1,poi_j,pen_j,poi_v,pen_v,i=g.vt[m][1],j=g.vt[m][2];
    
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