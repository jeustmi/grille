#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <array>
#include <iostream>

using tab_nb=std::array<int,64>;
using mat_nb=std::array<tab_nb,64>;
using tab_sl=std::array<char,64>;
using mat_sl=std::array<tab_sl,64>;
using tab_tri=std::array<int,3>;
using mat_tri=std::array<tab_tri,1024>;

struct grille_complete{ //on fait une structure contenant toutes les informatiosn pour faciliter l'accès aux données (même si l'on n'a que ramement besoinde tous)
    mat_nb nb; //grille de nombres
    mat_sl sl; //grille de solution
    mat_tri vt; //tableau contenant les valeurs de la matrice nb, triées
    int J=0,V=0,N=0,B=0,O=0,R=0; //nombre de jeton de chaque couleur de la grille.sl
    int n,p,t; //n=taille, p=pénalité, t=taille au carre
};

#endif