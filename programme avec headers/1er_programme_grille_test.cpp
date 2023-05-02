#include "lecture_fichier.hpp"
#include "aff_mat.hpp"
#include "compte_jetons.hpp"
#include "calcul_score.hpp"
#include "struct.hpp"
#include "ecriture_fichier.hpp"
#include "tab_tri.hpp"
#include "plh.hpp"

//g++ 1er_programme_grille_test.cpp lecture_fichier.cpp aff_mat.cpp compte_jetons.cpp calcul_score.cpp struct.cpp ecriture_fichier.cpp tab_tri.cpp plh.cpp -o prog.out


int main(){
    grille_complete grille;
    ch taille_grille,lettre_grille,numero_test;
    ch fol="fic/";
    ch fic="probleme_",fic_nb,fic_sl; //les fichiers d'entrée, il faudra demander la grille de nombres au début du programme final avec un std::cin

    std::cout<<"rentrez la taille de la grille du fichier moodle (n1, un entier naturel) : ";
    std::cin>>taille_grille;
    std::cout<<"rentrez la lettre du fichier (a-z, une lettre minuscule) : ";
    std::cin>>lettre_grille;
    std::cout<<"rentrez le numero du test actuel (n2, un entier naturel) : ";
    std::cin>>numero_test;
    fic_nb=fol+fic+taille_grille+"_"+lettre_grille+".txt";
    fic_sl=fol+"sl_"+fic+taille_grille+"_"+lettre_grille+"_"+numero_test+".txt";
    std::cout<<fic<<" "<<fic_nb<<" "<<fic_sl<<std::endl;

    lecture_fichier_nb(fic_nb,grille);
    lecture_fichier_sl(fic_sl,grille);
    affichage_mat_nb(grille.nb,grille.n); //vérification de la grille de nombres
    affichage_mat_sl(grille.sl,grille.n); //vérification de la grille solution
    compte_jeton(grille);

    //std::cout<<calcul_score(grille)<<std::endl; //peut être mis en commentaire car on doit de toute façon lancer le programme à l'écriture du fichier solution
    ch fic_sl_fin;
    fic_sl_fin=fol+"sl_"+fic+taille_grille+"_"+lettre_grille+"_"+numero_test+"_final.txt";
    écriture_fichier_solution(grille,fic_sl_fin);

    std::cout<<std::endl;
    init_tab_tri(grille);
    affiche_tab_tri(grille);
    std::cout<<std::endl;
    tri_selection(grille,grille.n*grille.n);
    affiche_tab_tri(grille);
    std::cout<<std::endl;

    init_sl(grille);
    placePionRouge(grille);
    affichage_mat_sl(grille.sl,grille.n);
    std::cout<<std::endl;
    place_noir(grille);
    affichage_mat_sl(grille.sl,grille.n);
    
    return 0;
}