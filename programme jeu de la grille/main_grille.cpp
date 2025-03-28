#include "lecture_fichier.hpp"
#include "aff_mat.hpp"
#include "compte_jetons.hpp"
#include "calcul_score.hpp"
#include "struct.hpp"
#include "ecriture_fichier.hpp"
#include "tab_tri.hpp"
#include "place_pion.hpp"

//Il suffit de copier la commande suivante dans le console ouverte au bon dossier :
//g++ main_grille.cpp lecture_fichier.cpp aff_mat.cpp compte_jetons.cpp calcul_score.cpp struct.cpp ecriture_fichier.cpp tab_tri.cpp place_pion.cpp -o programme_grille.out

int main(){
    grille_complete grille;
    ch taille_grille,lettre_grille,numero_test;
    ch fichier,fichier_grille,fichier_solution,fic_test_sol;
    ch folg="../fichiers_grille/grilles/",fols="../fichiers_grille/solutions/";

    std::cout<<"Rentrez le nom du fichier contenant la grille (veuillez respecter les consignes données dans le fichier \"instructions utilisation programme\") : ";
    std::cin>>fichier;

    fichier_grille=folg+fichier+".txt";
    fichier_solution=fols+"solution_"+fichier+".txt";
    
    std::cout<<std::endl;
    lecture_fichier_nb(fichier_grille,grille);
    affichage_mat_nb(grille.nb,grille.n); //vérification de la grille de nombres

    int dn=0,dp=0;
    init_tab_tri(grille);
    tri_selection(grille);
    init_sl(grille);

    placePionRouge(grille,dn);
    place_noir(grille,dp);
    place_vert(grille);
    place_orange(grille,dn);
    place_bleu(grille,dn);
    place_jaune(grille);

    std::cout<<std::endl;
    affichage_mat_sl(grille.sl,grille.n);

    int score=0;
    std::cout<<std::endl;
    écriture_fichier_solution(grille,fichier_solution);
    
    return 0;
}
