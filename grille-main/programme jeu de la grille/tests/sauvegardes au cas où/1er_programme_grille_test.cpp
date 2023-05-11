#include "lecture_fichier.hpp"
#include "aff_mat.hpp"
#include "compte_jetons.hpp"
#include "calcul_score.hpp"
#include "struct.hpp"
#include "ecriture_fichier.hpp"
#include "tab_tri.hpp"
#include "place_pion.hpp"

//g++ 1er_programme_grille_test.cpp lecture_fichier.cpp aff_mat.cpp compte_jetons.cpp calcul_score.cpp struct.cpp ecriture_fichier.cpp tab_tri.cpp place_pion.cpp -o prog.out


int main(){
    grille_complete grille;
    ch taille_grille,lettre_grille,numero_test;
    ch fol="fic/";
    ch fic="probleme_",fic_nb,fic_sl; //les fichiers d'entrée, il faudra demander la grille de nombres au début du programme final avec un std::cin
    int type_programme;

    std::cout<<"Voulez-vous tester une solution déjà existante (rentrez 1) ou en créer une (rentrez 2) ? ";
    std::cin>>type_programme;

    std::cout<<"rentrez la taille de la grille du fichier moodle (n1, un entier naturel) : ";
    std::cin>>taille_grille;
    std::cout<<"rentrez la lettre du fichier (a-z, une lettre minuscule) : ";
    std::cin>>lettre_grille;

    fic_nb=fol+fic+taille_grille+"_"+lettre_grille+".txt";
    lecture_fichier_nb(fic_nb,grille);
    affichage_mat_nb(grille.nb,grille.n); //vérification de la grille de nombres

    if(type_programme==1){
        std::cout<<"rentrez le numero du test actuel (n2, un entier naturel) : ";
        std::cin>>numero_test;
        
        fic_sl=fol+"sl_"+fic+taille_grille+"_"+lettre_grille+"_"+numero_test+".txt";
        //std::cout<<fic<<" "<<fic_nb<<" "<<fic_sl<<std::endl;
        
        lecture_fichier_sl(fic_sl,grille);
        affichage_mat_sl(grille.sl,grille.n); //vérification de la grille solution
        compte_jeton(grille);

        //std::cout<<calcul_score(grille)<<std::endl; //peut être mis en commentaire car on doit de toute façon lancer le programme à l'écriture du fichier solution
        ch fic_sl_fin;
        fic_sl_fin=fol+"sl_"+fic+taille_grille+"_"+lettre_grille+"_"+numero_test+"_final.txt";
        écriture_fichier_solution(grille,fic_sl_fin);
    }

    else if(type_programme==2){
        std::cout<<std::endl;
        init_tab_tri(grille);
        //affiche_tab_tri(grille);
        std::cout<<std::endl;
        tri_selection(grille);
        //affiche_tab_tri(grille);
        std::cout<<std::endl;

        init_sl(grille);
        /*place_vert(grille);
        affichage_mat_sl(grille.sl,grille.n);
        std::cout<<std::endl<<std::endl<<std::endl;*/

        int dn=0,dp=0;
        init_sl(grille);
        placePionRouge(grille,dn);
        affichage_mat_sl(grille.sl,grille.n);
        std::cout<<std::endl<<std::endl<<std::endl;
        place_noir(grille,dp);
        affichage_mat_sl(grille.sl,grille.n);
        std::cout<<std::endl<<std::endl<<std::endl;

        place_vert(grille);
        affichage_mat_sl(grille.sl,grille.n);
        std::cout<<std::endl<<std::endl<<std::endl;
        
        place_orange(grille,dn);
        affichage_mat_sl(grille.sl,grille.n);
        std::cout<<std::endl<<std::endl<<std::endl;
        /*place_bleu(grille,dn);
        affichage_mat_sl(grille.sl,grille.n);
        std::cout<<std::endl<<std::endl<<std::endl;
        place_jaune(grille,dp);
        affichage_mat_sl(grille.sl,grille.n);
        std::cout<<std::endl<<std::endl<<std::endl;*/
        
    }

    else if(type_programme==3){
        init_tab_tri(grille);
        tri_selection(grille);
        init_sl(grille);
        int dn=0,dp=0;
        place_orange(grille,dn);
        affichage_mat_sl(grille.sl,grille.n);
    }
    
    return 0;
}
