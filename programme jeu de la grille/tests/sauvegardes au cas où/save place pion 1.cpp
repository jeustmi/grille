using vect_co=std::array<int,3>; //contient les coordonnées d'un pion enlevé
using mat2=std::array<vect_co,512>; //contient une combinaison de pions, avec le score en position 0, le nombre de pions enlevés de cette combinaison en position 1 et chaque pion enlevé aux positions suivantes
using mat3=std::array<mat2,512>; //contient les combinaisons testées à l'instant, triées en fonction du score à partir de la position 1, et avec la meilleure combinaison d'avant en position 0

            //cette fonction teste les meilleures combinaisons de verts à partir de toutes les cases possibles
void compte_vert(grille_complete & g, mat3 & val_comb_vert, mat_tri & vert_pos_mat, int vpm_n, bool & fin){
    int n;
    n=val_comb_vert[0][1][0]; //on initialise n au nombre de verts enlevés dans les tests
    for(int i=0;i<vpm_n-n;++i){ //on lance une boucle qui enleve chaque jeton restant un à un pour calculer le score, n augmentera donc forcément de 1
        int poi=0;
        int pen=0;
        mat2 val_1comb;
        val_1comb=val_comb_vert[0]; //on fait cette affectation pour garder en mémoire les pions deja enleves, on rajoutera par la suite celui qu'on enleve a cette boucle a la fin de val_comb_vert
        val_1comb[1][0]=n+1;
        g.sl[vert_pos_mat[i][0]][vert_pos_mat[i][1]]='v';
        val_1comb[2+n][0]=vert_pos_mat[i][0]; val_1comb[2+n][1]=vert_pos_mat[i][1]; val_1comb[2+n][2]=i;
        
        for(int j=0;j<vpm_n-n;++j){
            if(j!=i){
                jeton_v(g,poi,pen,vert_pos_mat[j][0],vert_pos_mat[j][1]);
                g.sl[vert_pos_mat[j][0]][vert_pos_mat[j][1]]='v';
            }
        }

        for(int j=0;j<vpm_n-n;++j){
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

        g.sl[vert_pos_mat[i][0]][vert_pos_mat[i][1]]='V';
        val_1comb[0][0]=poi-pen;

        int j=i+1;
        while ((j>1) and (val_comb_vert[j-1][0][0] < val_1comb[0][0])){
            val_comb_vert[j] = val_comb_vert[j-1];
            --j;
        }
        val_comb_vert[j]=val_1comb;
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

