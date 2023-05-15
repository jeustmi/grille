#include "calcul_score.hpp"

            //comptage des points, les commentaires indiquent ce dont la fonction a besoin pour marcher (pen = pénalités, poi = points)
void jeton_j(grille_complete grille, int & poi_tot, int & pen_tot, int i, int j){ //pen + poi
    poi_tot+=grille.nb[i][j]; //points de la case
    bool pen_temp;
    pen_temp=0;
    for(int k=i-1;k<i+2;k++){
        for(int l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)){
                if(grille.sl[k][l]=='J'){
                    pen_temp=1; //pas de pénalité si un autre jaune est adjacent
                }
            }
        }
    }
    if(pen_temp==0){
        pen_tot+=grille.p;
    }
}

void jeton_v(grille_complete & grille, int & poi_tot, int & pen_tot, int i, int j){ //pen + poi + change son propre char pour ne pas recompter la pénalité
    int compteur;
    compteur=1; //compte le nombre de tours de la double boucle et sert à savoir à quelle boucle on est dans un coin et donc quand il ne faut pas compter les points
    for(int k=i-1;k<i+2;k++){
        for(int l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and compteur!=1 and compteur!=3 and compteur!=7 and compteur!=9){ // (0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)) : vérifie qu'il n'y a pas de core dumped, (a!=1 and a!=3 and a!=7 and a!=9) : vérifie qu'on est pas dans un coin
                poi_tot+=grille.nb[k][l]; //points des cases adjacentes mais pas en diagonale du jeton
            }
            ++compteur;
        }
    }
    for(int k=i-1;k<i+2;k++){
        for(int l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)){ // (0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)) : vérifie qu'il n'y a pas de core dumped, !(k==i and l==j) :  vérifie qu'on ne compte pas la case sur lequel est le jeton, sinon on aurait une pénalité d'office
                if(grille.sl[k][l]=='V'){
                    pen_tot+=grille.p; //pénalité si un jeton vert est adjacent
                }
            }
        }
    }
}

void jeton_n(grille_complete grille, int &poi_tot, int i, int j){ //poi + a besoin de n
    if(grille.N<=grille.n){ //s'il y a au plus n jetons noirs:
        poi_tot+=2*(grille.nb[i][j]-1); //points de la case doublés
    }
    else{ //sinon
        poi_tot+=grille.nb[i][j]-1; //points de la case
    }
}

void jeton_r(grille_complete grille, int &poi_tot, int i, int j){ //poi, a besoin de parcourir la grille solution  
    poi_tot+=-grille.nb[i][j];
}

void jeton_b(grille_complete grille, int &pen_tot, int i, int j){ //pen, n'a pas besoin d'être appelé à chaque boucle
    int nb_pen_temp;
    nb_pen_temp=0;
    for(i=0;i<grille.n;++i){
        for(j=0;j<grille.n;++j){
            if(grille.sl[i][j]=='B'){
                if(grille.nb[i][j]<0){ //si le jeton est sur une case négative
                    nb_pen_temp+=1; //la différence augmente de 1
                }
                else if(grille.nb[i][j]>0){ //sinon, s'il est sur une case positive
                    nb_pen_temp-=1; //la différence baisse de 1
                }
            } //on ne compte pas les cases = 0 car elles sont les deux, on fait donc nb_pen_temp+1 puis nb_pen_temp-1, donc ça ne sert à rien
        }
    }
    if(nb_pen_temp>0){ //si la différence est négative
        pen_tot+=nb_pen_temp*grille.p; //on ajoute cette différence aux pénalités
    }
}

void jeton_o(grille_complete &grille, int &pen_tot, int i, int j){ //pen + change son propre char pour ne pas recompter la pen
    for(int k=0;k<grille.n;++k){ //parcours de la grille en croix suisse
        if(k!=i and grille.sl[k][j]=='O'){ //hroizontalement
            pen_tot+=grille.p; //pénalité si autre jeton orage sur la ligne
        }
        if(k!=j and grille.sl[i][k]=='O'){ //verticalement
            pen_tot+=grille.p; //pénalité si autre jeton orange sur la colonne
        }
    }
    for(int k=-std::min(i,j);k<grille.n-std::max(i,j);k++){
        if(k!=0 and grille.sl[i+k][j+k]=='O'){ //parcours de la grille en diagonale tl:dr
            pen_tot+=grille.p; //pénalité si un autre jeton orange sur la diagonale
        }
    }
    for(int k=-std::min(grille.n-1-i,j);k<grille.n-std::max(grille.n-1-i,j);k++){
        if(k!=0 and grille.sl[i-k][j+k]=='O'){ //parcours de la grille en diagonale dl:tr
            pen_tot+=grille.p; //pénalité si un autre jeton orange sur la diagonale
        }
    } 
}

void calcul_score(grille_complete &grille, int &score){
    int i,j;
    int poi_tot=0,pen_tot=0; //variables point totaux et pénalités totales
    char jeton; //sert juste à ne pas réécrire grille[i][j] à chaque fois
    mat_sl save_grille_sl; //save de la grille pour pouvoir reourner aux valeur initiales car on change certains char en minuscule pour le comptage
    save_grille_sl=grille.sl;
    jeton_b(grille,pen_tot,i,j);
    for(i=0;i<grille.n;++i){
        for(j=0;j<grille.n;++j){
            jeton=grille.sl[i][j];
            if(jeton=='J'){
                jeton_j(grille,poi_tot,pen_tot,i,j);
            }
            else if(jeton=='V'){
                jeton_v(grille,poi_tot,pen_tot,i,j);
                grille.sl[i][j]='v'; //on change le char de la case car on ne veut pas le recompter plus tard pour les autres pénalités des jetons verts (les variables char et string sont case sensitive)
            }
            else if(jeton=='N'){
                jeton_n(grille,poi_tot,i,j);
            }
            else if(jeton=='O'){
                jeton_o(grille,pen_tot,i,j);
                grille.sl[i][j]='o'; //même chose que pour les jetons verts
            }
            else if(jeton=='R'){
                jeton_r(grille,poi_tot,i,j);
            }
            else if(jeton!='B'){
                std::cout<<"erreur lecture jeton"<<std::endl;
            }
        }
    }
        std::cout<<pen_tot<<" "<<poi_tot<<std::endl; //check des points et pénalités pour mieux repérer les erreurs
    poi_tot=poi_tot-pen_tot; //calcul du score final
    grille.sl=save_grille_sl; //réattribution de la grille solution initiale
        std::cout<<poi_tot<<std::endl;
    score=poi_tot;
}
