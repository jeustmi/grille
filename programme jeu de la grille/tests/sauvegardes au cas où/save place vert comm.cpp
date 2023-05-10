using vect_co=std::array<int,3>; //contient les coordonnées d'un pion enlevé en position 0 et 1 et la boucle à laquelle il a été enlevé
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
            if(g.sl[i][j]=='1'){ //on regarde toutes les cases non prises
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
    a=recherche_min_positif(vert_mat,g.t);
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