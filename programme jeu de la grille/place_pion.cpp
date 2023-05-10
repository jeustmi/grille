#include "place_pion.hpp"
#include "calcul_score.hpp"

void init_sl(grille_complete & g){//init la grille de solution avec des '1'
    for(int i=0; i<g.n ; ++i){
        for(int j=0; j<g.n ; ++j){
            g.sl[i][j]='1';
        }
    }
}

void placePionRouge(grille_complete & g,int & dn){//place le pion rouge sur la case avec la plus petite valeur
    g.sl[g.vt[0][1]][g.vt[0][2]]='R';
    ++dn;
}

void trouve_dp_dn(grille_complete & g, int & dp,int & dn){ //si la grille est remplie, renvoie 0 pour dn et dp
    bool trouve_n,trouve_p;
    trouve_n=trouve_p=false;
    dp=0;
    dn=0;
    for(int i=1;i<g.t-1;++i){
        if(trouve_n==false and g.sl[g.vt[i][1]][g.vt[i][2]]=='1' and g.sl[g.vt[i-1][1]][g.vt[i-1][2]]!='1'){
            dn=i;
            trouve_n=true;
        }
        if(trouve_p==false and g.sl[g.vt[g.t-i][1]][g.vt[g.t-i][2]]=='1' and g.sl[g.vt[g.t-i+1][1]][g.vt[g.t-i+1][2]]!='1'){
            dp=i-1; //truc bizarre ici, je sais pas si le -1 est nécessaire
            trouve_p=true;
        }
    }
    int k=0;

    //boucle de test
    /*for(int i=0; i<g.n ; ++i){
        for(int j=0; j<g.n ; ++j){
            std::cout<<k<<" valeur : "<<g.vt[k][0]<<" i :"<<g.vt[k][1]<<" j :"<<g.vt[k][2]<<std::endl;
            ++k;
        }
    }*/

}

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

using vect_co=std::array<int,3>;
using mat2=std::array<vect_co,512>;
using mat3=std::array<mat2,512>;

void compte_vert(grille_complete & g, mat3 & val_comb_vert, mat_tri & vert_pos_mat, int vpm_n, bool & fin){
    /*if(val_comb_vert[0][1][0]=vpm_n){
        val_comb_vert[0][1][0]=vpm_n;
    }*/
    /*else if(n!=0 and vert_pos_mat[1][0]<vert_pos_mat[0][0]){

    }*/
    //if(val_comb_vert[0][1][0]<vpm_n){
    /*if(val_comb_vert[0][1][0]!=0){
        val_comb_vert[0]=val_comb_vert[1];
    }*/
    int n;
    n=val_comb_vert[0][1][0];
    //std::cout<<std::endl;
    //std::cout<<n<<std::endl<<std::endl;
    for(int i=0;i<vpm_n-n;++i){
        //std::cout<<i<<std::endl;
        int poi=0;
        int pen=0;
        mat2 val_1comb;
        val_1comb=val_comb_vert[0];
        val_1comb[1][0]=n+1;
        g.sl[vert_pos_mat[i][0]][vert_pos_mat[i][1]]='v';
        val_1comb[2+n][0]=vert_pos_mat[i][0]; val_1comb[2+n][1]=vert_pos_mat[i][1]; val_1comb[2+n][2]=i;
        
        for(int j=0;j<vpm_n-n;++j){
            if(j!=i){
                jeton_v(g,poi,pen,vert_pos_mat[j][0],vert_pos_mat[j][1]);
                g.sl[vert_pos_mat[j][0]][vert_pos_mat[j][1]]='v';
            }
        }
        //std::cout<<vpm_n-n<<"   ";
        for(int j=0;j<vpm_n-n;++j){
            if(j!=i){
                g.sl[vert_pos_mat[j][0]][vert_pos_mat[j][1]]='V';
            }
        }
        /*std::cout<<std::endl<<pen<<" "<<poi<<std::endl<<std::endl;
        for(int k=0;k<g.n;++k){
            for(int l=0;l<g.n;++l){
                std::cout<<g.sl[k][l]<<" ";
            }
        std::cout<<std::endl;
        }*/
        //std::cout<<vert_pos_mat[i][0]<<" "<<vert_pos_mat[i][1]<<std::endl;
        g.sl[vert_pos_mat[i][0]][vert_pos_mat[i][1]]='V';
        val_1comb[0][0]=poi-pen;
        //std::cout<<val_1comb[0][0]<<std::endl;

        int j=i+1;
        while ((j>1) and (val_comb_vert[j-1][0][0] < val_1comb[0][0])){
            val_comb_vert[j] = val_comb_vert[j-1];
            --j;
        }
        val_comb_vert[j]=val_1comb;
        /*for(j=0;j<i+2;++j){
            std::cout<<val_comb_vert[j][0][0]<<std::endl;
        }
        std::cout<<std::endl;*/
    }
    
    int j=val_comb_vert[1][2+n][2];
    tab_tri temp;
    temp=vert_pos_mat[j];
    while (j<vpm_n){
        vert_pos_mat[j] = vert_pos_mat[j+1];
        ++j;
    }
    vert_pos_mat[j]=temp;
    if(val_comb_vert[1][0][0]>=val_comb_vert[0][0][0]){
        val_comb_vert[0]=val_comb_vert[1];
        g.sl[val_comb_vert[0][2+n][0]][val_comb_vert[0][2+n][1]]='1';
    }
    else{
        fin=true;
    }
    //g.sl[val_comb_vert[0][2+n][0]][val_comb_vert[0][2+n][1]]='1';
    //}
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
    mat_tri vert_pos_mat;
    int a, vpm_n=0;
    poi=0;
    pen=0;
    i=vn-1;
    a=recherche_min_positif(vert_mat,g.t);
    while(i>=a){
        jeton_v(g,poi,pen,vert_mat[i][1],vert_mat[i][2]);
        g.sl[vert_mat[i][1]][vert_mat[i][2]]='V';
        vert_pos_mat[vpm_n]={vert_mat[i][1],vert_mat[i][2]};
        ++vpm_n;
        --i;
    }
    mat3 val_comb_vert;
    val_comb_vert[0]={poi-pen,-2,-2,0,-2,-2};
    /*for(i=0;i<3;++i){
        for(j=0;j<3;++j){
            std::cout<<val_comb_vert[0][i][j]<<" ";
        }
        std::cout<<std::endl;
    }*/
    bool fin=false;
    while(fin==false){
        compte_vert(g,val_comb_vert,vert_pos_mat,vpm_n,fin);
        if(val_comb_vert[0][1][0]==vpm_n){
            fin=true;
        }
    }
    /*for(i=2;i<val_comb_vert[0][1][0]+2;++i){
        g.sl[val_comb_vert[0][i][0]][val_comb_vert[0][i][1]]='v';
    }*/
    /*i=1;
    while(i<vpm_n){
        ++vpm_n;
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
        vert_pos_tab={poi-pen,vert_mat[i][1],vert_mat[i][2]};
        j=vpm_n-1;
        while ((j>0) and (vert_pos_mat[j-1][0] < vert_pos_tab[0])){
            vert_pos_mat[j] = vert_pos_mat[j-1];
            --j;
        }
        vert_pos_mat[j]=vert_pos_tab;*/
        /*for(j=0;j<vpm_n;++j){
            std::cout<<vert_pos_mat[j][0]<<" "<<vert_pos_mat[j][1]<<" "<<vert_pos_mat[j][2]<<std::endl;
        }*/
        /*g.sl[vert_mat[i][1]][vert_mat[i][2]]='V';
        ++i;
    }
    g.sl[vert_pos_mat[0][1]][vert_pos_mat[0][2]]='1';*/
}

void place_orange(grille_complete & g,int & dn){ //place la meilleure position des oranges, dans certains cas
    mat_tri or_mat;
    tab_tri or_tab;
    int or_mat_n,a,rine,k,i,pen;
    trouve_dp_dn(g,rine,dn);
    a=recherche_min_positif(g.vt,g.t);
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

void place_jaune2(grille_complete & g, int & dp){

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