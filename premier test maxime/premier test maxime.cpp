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

struct grille_complète{
    mat_nb nb;
    mat_sl sl;
    int J=0,V=0,N=0,B=0,O=0;
    int n,p;
};

void lecture_fichier_nb(ch fic,grille_complète &grille){
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

void lecture_fichier_sl(ch fic,grille_complète &grille){
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

void affichage_mat_nb(mat_nb grille,int n){
    for(i=0;i<n;++i){
        for(j=0;j<n;++j){
            std::cout<<grille[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void affichage_mat_sl(mat_sl grille,int n){
    for(k=0;k<n;++k){
        for(l=0;l<n;++l){
            std::cout<<grille[k][l]<<" ";
        }
        std::cout<<std::endl;
    }
}

void compte_jeton(grille_complète &grille){
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
}

void jeton_j(grille_complète grille, int &poi_tot, int &pen_tot){ //pen + poi
    poi_tot+=grille.nb[i][j];
    bool b;
    b=0;
    for(k=i-1;k<i+2;k++){
        for(l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)){
                if(grille.sl[k][l]=='J'){
                    b=1;
                }
            }
        }
    }
    if(b==0){
        pen_tot+=1;
    }
}
void jeton_v(grille_complète &grille, int &poi_tot, int &pen_tot){ //pen + poi + change son propre char pour ne pas recompter la pen
    int a,b;
    a=1;
    b=0;
    for(k=i-1;k<i+2;k++){
        for(l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j) and a!=1 and a!=3 and a!=7 and a!=9){
                poi_tot+=grille.nb[k][l];
            }
            ++a;
        }
    }
    poi_tot+=grille.nb[i][j];
    for(k=i-1;k<i+2;k++){
        for(l=j-1;l<j+2;l++){
            if(0<=k and k<grille.n and 0<=l and l<grille.n and !(k==i and l==j)){
                if(grille.sl[k][l]=='V'){
                    pen_tot+=1;
                }
            }
        }
    }
    grille.sl[i][j]='v';
}
void jeton_n(grille_complète grille, int &poi_tot){ //poi + a besoin de n
    if(grille.N<=grille.n){
        poi_tot+=2*(grille.nb[i][j]-1);
    }
    else{
        poi_tot+=grille.nb[i][j]-1;
    }
}
void jeton_b(grille_complète grille, int &pen_tot){ //pen, n'a pas besoin d'être appelé à chaque boucle
    int d;
    d=0;
    for(i=0;i<grille.n;++i){
        for(j=0;j<grille.n;++j){
            if(grille.sl[i][j]=='B'){
                if(grille.nb[i][j]<0){
                    d+=1;
                }
                else if(grille.nb[i][j]>0){
                    d-=1;
                }
            }
        }
    }
    if(d>0){
        pen_tot+=d;
    }
}
void jeton_o(grille_complète &grille, int &pen_tot){ //pen + change son propre char pour ne pas recompter la pen
    for(k=0;k<grille.n;++k){
        if(k!=i and grille.sl[k][j]=='O'){
            pen_tot+=1;
        }
        if(k!=j and grille.sl[i][k]=='O'){
            pen_tot+=1;
        }
    }
    for(k=-std::min(i,j);k<grille.n-std::max(i,j);k++){
        if(k!=0 and grille.sl[i+k][j+k]=='O'){
            pen_tot+=1;
        }
    }
    for(k=-std::min(i,j);k<grille.n-std::max(i,j);k++){
        if(k!=0 and grille.sl[i-k][j+k]=='O'){
            pen_tot+=1;
        }
    }
    grille.sl[i][j]='o';
}
void jeton_r(grille_complète grille, int &poi_tot){ //poi, a besoin de parcourir la sl     
    poi_tot+=-grille.nb[i][j];
}

int calcul_score(grille_complète &grille){
    int poi_tot=0,pen_tot=0;
    char jeton;
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
    std::cout<<pen_tot<<" "<<poi_tot<<std::endl;
    poi_tot=poi_tot-grille.p*pen_tot;
    return poi_tot;
}

int main(){
    grille_complète grille;
    ch fic_nb="probleme_4_0.txt",fic_sl="sl_probleme_4_0.txt";
    lecture_fichier_nb(fic_nb,grille);
    lecture_fichier_sl(fic_sl,grille);
    affichage_mat_nb(grille.nb,grille.n);
    affichage_mat_sl(grille.sl,grille.n);
    compte_jeton(grille);
    std::cout<<grille.J<<" "<<grille.V<<" "<<grille.N<<" "<<grille.B<<" "<<grille.O<<std::endl;
    std::cout<<calcul_score(grille)<<std::endl;
    return 0;
}