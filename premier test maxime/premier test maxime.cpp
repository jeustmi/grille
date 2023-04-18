#include <iostream>
#include <fstream>
#include <string>
#include <array>
using fif=std::ifstream;
using fof=std::ofstream;
using ch=std::string;
using tab_nb=std::array<int,16>;
using mat_nb=std::array<tab_nb,16>;
using tab_sl=std::array<char,16>;
using mat_sl=std::array<tab_sl,16>;
int i,j,k,l;

struct grille_complète{ //on fait uen structure contenant toutes les informatiosn pour faciliter l'accès aux données (même si l'on n'a que ramement besoinde tous)
    mat_nb nb; //grille de nombres
    mat_sl sl; //grille de solution
    int J=0,V=0,N=0,B=0,O=0; //nombre de jeton de chaque couleur de la grille.sl
    int n,p; //n=taille, p=pénalité
};

void lecture_fichier_nb(ch fic,grille_complète &grille){ //lit un fichier de la forme grille.nb avec n et p en en-tête (entrée)
    fif grille_fichier(fic);
    int e;
    if(grille_fichier){
        grille_fichier >> e;
        grille.n=e;
        grille_fichier >> e;
        grille.p=e;
        for(i=0;i<grille.n;++i){
            for(j=0;j<grille.n;++j){
                grille_fichier >> e;
                grille.nb[i][j]=e;
            }
        }
    }
    else{
        std::cout<<"erreur lecture du fichier"<<std::endl;
    }
}

void lecture_fichier_sl(ch fic,grille_complète &grille){ //lit un fichier de la forme grille.sl, avec seulement les numéros (sortie dans le programme final, entrée ici)
    fif grille_fichier(fic);
    char e;
    if(grille_fichier){
        for(i=0;i<grille.n;++i){
            for(j=0;j<grille.n;++j){
                grille_fichier >> e;
                grille.sl[i][j]=e;
            }
        }
    }
    else{
        std::cout<<"erreur lecture du fichier"<<std::endl;
    }
}

void affichage_mat_nb(mat_nb grille,int n){ //affiche une matrice d'int
    for(i=0;i<n;++i){
        for(j=0;j<n;++j){
            std::cout<<grille[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void affichage_mat_sl(mat_sl grille,int n){ //affiche une matrice de char
    for(k=0;k<n;++k){
        for(l=0;l<n;++l){
            std::cout<<grille[k][l]<<" ";
        }
        std::cout<<std::endl;
    }
}

void compte_jeton(grille_complète &grille){ //compte le nombre de jeton de chaque couleur d'une grille solution (sert pour compter les points des noirs, autant le faire pour tout le monde)
    char jeton;
    for(i=0;i<grille.n;++i){
        for(j=0;j<grille.n;++j){
            jeton=grille.sl[i][j];
            if(jeton=='J'){
                grille.J+=1;
            }
            else if(jeton=='V'){
                grille.V+=1;
            }
            else if(jeton=='N'){
                grille.N+=1;
            }
            else if(jeton=='B'){
                grille.B+=1;
            }
            else if(jeton=='O'){
                grille.O+=1;
            }
        }
    }
    std::cout<<grille.J<<" "<<grille.V<<" "<<grille.N<<" "<<grille.B<<" "<<grille.O<<std::endl; //simple vérification
}

            //comptage des points, les commentaires indiquent ce dont la fonction a besoin pour marcher (pen = pénalités, poi = points)
void jeton_j(grille_complète grille, int &poi_tot, int &pen_tot){ //pen + poi
    poi_tot+=grille.nb[i][j]; //points de la case
    bool b;
    b=0;
    for(k=i-1;k<i+2;k++){
        for(l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)){
                if(grille.sl[k][l]=='J'){
                    b=1; //pas de pénalité si un autre jaune est adjacent
                }
            }
        }
    }
    if(b==0){
        pen_tot+=1;
    }
}
void jeton_v(grille_complète &grille, int &poi_tot, int &pen_tot){ //pen + poi + change son propre char pour ne pas recompter la pénalité
    int a,b;
    a=1; //compte le nombre de tours de la double boucle et sert à savoir à quelle boucle on est dans un coin et donc quand il ne faut pas compter les points
    b=0;
    for(k=i-1;k<i+2;k++){
        for(l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and a!=1 and a!=3 and a!=7 and a!=9){ // (0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)) : vérifie qu'il n'y a pas de core dumped, (a!=1 and a!=3 and a!=7 and a!=9) : vérifie qu'on est pas dans un coin
                poi_tot+=grille.nb[k][l]; //points des cases adjacentes mais pas en diagonale du jeton
            }
            ++a;
        }
    }
    for(k=i-1;k<i+2;k++){
        for(l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)){ // (0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)) : vérifie qu'il n'y a pas de core dumped, !(k==i and l==j) :  vérifie qu'on ne compte pas la case sur lequel est le jeton, sinon on aurait une pénalité d'office
                if(grille.sl[k][l]=='V'){
                    pen_tot+=1; //pénalité si un jeton vert est adjacent
                }
            }
        }
    }
    grille.sl[i][j]='v'; //on change le char de la case car on ne veut pas le recompter plus tard pour les autres pénalités des jetons verts (les variables char et string sont case sensitive)
}
void jeton_n(grille_complète grille, int &poi_tot){ //poi + a besoin de n
    if(grille.N<=grille.n){ //s'il y a au plus n jetons noirs:
        poi_tot+=2*(grille.nb[i][j]-1); //points de la case doublés
    }
    else{ //sinon
        poi_tot+=grille.nb[i][j]-1; //points de la case
    }
}
void jeton_b(grille_complète grille, int &pen_tot){ //pen, n'a pas besoin d'être appelé à chaque boucle
    int d;
    d=0;
    for(i=0;i<grille.n;++i){
        for(j=0;j<grille.n;++j){
            if(grille.sl[i][j]=='B'){
                if(grille.nb[i][j]<0){ //si le jeton est sur une case négative
                    d+=1; //la différence augmente de 1
                }
                else if(grille.nb[i][j]>0){ //sinon, s'il est sur une case positive
                    d-=1; //la différence baisse de 1
                }
            } //on ne compte pas les cases = 0 car elles sont les deux, on fait donc d+1 puis d-1, donc ça ne sert à rien
        }
    }
    if(d>0){ //si la différence est négative
        pen_tot+=d; //on ajoute cette différence aux pénalités
    }
}
void jeton_o(grille_complète &grille, int &pen_tot){ //pen + change son propre char pour ne pas recompter la pen
    for(k=0;k<grille.n;++k){ //parcours de la grille en croix suisse
        if(k!=i and grille.sl[k][j]=='O'){ //hroizontalement
            pen_tot+=1; //pénalité si un autre jeton orage sur la ligne
        }
        if(k!=j and grille.sl[i][k]=='O'){ //verticalement
            pen_tot+=1; //pénalité si un autre jeton orange sur la colonne
        }
    }
    for(k=-std::min(i,j);k<grille.n-std::max(i,j);k++){
        if(k!=0 and grille.sl[i+k][j+k]=='O'){ //parcours de la grille en diagonale tl:dr
            pen_tot+=1; //pénalité si un autre jeton orange sur la diagonale
        }
    }
    for(k=-std::min(i,j);k<grille.n-std::max(i,j);k++){
        if(k!=0 and grille.sl[i-k][j+k]=='O'){ //parcours de la grille en diagonale dl:tr
            pen_tot+=1; //pénalité si un autre jeton orange sur la diagonale
        }
    }
    grille.sl[i][j]='o'; //même chose que pour les jetons verts
}
void jeton_r(grille_complète grille, int &poi_tot){ //poi, a besoin de parcourir la grille solution  
    poi_tot+=-grille.nb[i][j];
}

            //cette fonction n'est pas un void mais fait quand même des std::cout périodiquement, il faudra changer ça
int calcul_score(grille_complète &grille){
    int poi_tot=0,pen_tot=0; //variables point totaux et pénalités totales
    char jeton; //sert juste à ne pas réécrire grille[i][j] à chaque fois
    mat_sl save_grille_sl; //save de la grille pour pouvoir reourner aux valeur initiales car on change certains char en minuscule pour le comptage
    save_grille_sl=grille.sl;
    jeton_b(grille,pen_tot);
    for(i=0;i<grille.n;++i){
        for(j=0;j<grille.n;++j){
            jeton=grille.sl[i][j];
            if(jeton=='J'){
                jeton_j(grille,poi_tot,pen_tot);
            }
            else if(jeton=='V'){
                jeton_v(grille,poi_tot,pen_tot);
            }
            else if(jeton=='N'){
                jeton_n(grille,poi_tot);
            }
            else if(jeton=='O'){
                jeton_o(grille,pen_tot);
            }
            else if(jeton=='R'){
                jeton_r(grille,poi_tot);
            }
            else if(jeton!='B'){
                std::cout<<"erreur lecture jeton"<<std::endl;
            }
        }
    }
    std::cout<<pen_tot<<" "<<poi_tot<<std::endl; //check des points et pénalités pour mieux repérer les erreurs
    poi_tot=poi_tot-grille.p*pen_tot; //calcul du score final
    grille.sl=save_grille_sl; //réattribution de la grille solution initiale
    std::cout<<poi_tot<<std::endl;
    return poi_tot;
}

void écriture_fichier_solution(ch fic){

}

int main(){
    grille_complète grille;
    ch fic="probleme_4_0",fic_nb,fic_sl; //les fichiers d'entrée, il faudra demander la grille de nombres au début du programme final avec un std::cin
    fic_nb=fic+".txt";
    fic_sl="sl_"+fic+".txt";
    std::cout<<fic<<" "<<fic_nb<<" "<<fic_sl<<std::endl;
    lecture_fichier_nb(fic_nb,grille);
    lecture_fichier_sl(fic_sl,grille);
    affichage_mat_nb(grille.nb,grille.n); //vérification de la grille de nombres
    affichage_mat_sl(grille.sl,grille.n); //vérification de la grille solution
    compte_jeton(grille);
    //std::cout<<calcul_score(grille)<<std::endl; //peut être mis en commentaire car on doit de toute façon lancer le programme à l'écriture du fichier solution
    ch fic_sl_fin;
    fic_sl_fin="sl_"+fic+"_final.txt";
    fof sol(fic_sl_fin); //recrée un fichier solution, avec cette fois-ci le score à la fin, comme attendu
    if(sol){
        for(i=0;i<grille.n;++i){
            for(j=0;j<grille.n;++j){
                sol << grille.sl[i][j];
            }
            sol << std::endl;
        }
        sol << calcul_score(grille);
    }
    else{
        std::cout<<"erreur à l'écriture du fichier"<<std::endl;
    }
    return 0;
}