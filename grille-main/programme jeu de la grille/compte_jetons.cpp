#include "compte_jetons.hpp"

void compte_jeton(grille_complete &grille){ //compte le nombre de jeton de chaque couleur d'une grille solution (sert pour compter les points des noirs, autant le faire pour tout le monde)
    char jeton;
    for(int i=0;i<grille.n;++i){
        for(int j=0;j<grille.n;++j){
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
            else if(jeton=='R'){
                grille.R+=1;
            }
        }
    }
    std::cout<<grille.J<<" "<<grille.V<<" "<<grille.N<<" "<<grille.B<<" "<<grille.O<<" "<<grille.R<<std::endl; //simple vérification
}