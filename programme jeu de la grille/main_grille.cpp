#include "lecture_fichier.hpp"
#include "aff_mat.hpp"
#include "compte_jetons.hpp"
#include "calcul_score.hpp"
#include "struct.hpp"
#include "ecriture_fichier.hpp"
#include "tab_tri.hpp"
#include "place_pion.hpp"

//g++ main_grille.cpp lecture_fichier.cpp aff_mat.cpp compte_jetons.cpp calcul_score.cpp struct.cpp ecriture_fichier.cpp tab_tri.cpp place_pion.cpp -o prog.out


int main(){
    grille_complete grille;
    ch taille_grille,lettre_grille,numero_test;
    ch fichier,fichier_grille,fichier_solution,fic_test_sol;
    ch folg="fic/grilles/",fols="fic/solutions/";

    std::cout<<"Rentrez le nom du fichier contenant la grille (veuillez respecter les consignes données) : (mets juste le nom du fichier sans fic/ ou .txt)";
    std::cin>>fichier;

    fichier_grille=folg+fichier+".txt";
    fichier_solution=fols+"solution_"+fichier+".txt";

    int type_programme; //a supprimer avant de rendre
    std::cout<<"Voulez-vous tester une solution déjà existante (rentrez 1) ou en créer une (rentrez 2) ? "; //
    std::cin>>type_programme; //fin suppr
    
    lecture_fichier_nb(fichier_grille,grille);
    affichage_mat_nb(grille.nb,grille.n); //vérification de la grille de nombres

    if(type_programme==1){ //a suppr aussi du coup
        std::cout<<"rentrez le nom du fichier solution (avec sl_ au debut) : ";
        std::cin>>fic_test_sol;

        ch fic_sl_fin;
        fic_sl_fin=fols+"sl_"+fic_test_sol+"_score.txt";
        fic_test_sol=fols+"sl_"+fic_test_sol+".txt";

        lecture_fichier_sl(fic_test_sol,grille);
        affichage_mat_sl(grille.sl,grille.n); //vérification de la grille solution
        int score=0;
        compte_jeton(grille);
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

        place_bleu(grille,dn);

            affichage_mat_sl(grille.sl,grille.n);
            std::cout<<std::endl<<std::endl<<std::endl;

        place_jaune(grille);

            affichage_mat_sl(grille.sl,grille.n);
            std::cout<<std::endl<<std::endl<<std::endl;

        int score=0;
        calcul_score(grille, score);

        écriture_fichier_solution(grille,fichier_solution);
    }
    
    return 0;
}
