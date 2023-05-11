#include <array>
#include <iostream>

int main(){
    std::array<int,32> oui;
    oui={0};
    long i,j;
    for(i=0;i<4294967296;++i){
        j=0;
        while(oui[j]==1){
            oui[j]=0;
            ++j;
        }
        oui[j]=1;
        for(j=0;j<32;++j){
            std::cout<<oui[j];
        }
        std::cout<<" "<<i<<" "<<100*i/4294967296<<"%"<<std::endl;
    }
}

void bruteforce(grille_complete & g){
    mat2 brute={0},sol;
    int brute_n=1;
    bool fin;
    for(int i=0;i<g.n;i++){
        for(int j=0;j<g.n;j++){
            if(g.sl[i][j]=='1'){
                brute[i+1]={i,j,0};
                brute_n++;
            }
        }
    }
    fin=true;
    for(int i=1;i<brute_n;++i){
        if(brute[i][2]==0){
            g.sl[brute[i][0]][brute[i][1]]='B';
            fin=false;
        }
        else if(brute[i][2]==1){
            g.sl[brute[i][0]][brute[i][1]]='J';
        }
    }
}


int calcul_b_j(grille_complete &grille){
    int i,j;
    int poi_tot=0,pen_tot=0;
    char jeton;
    mat_sl save_grille_sl;
    save_grille_sl=grille.sl;
    jeton_b(grille,pen_tot,i,j);
    for(i=0;i<grille.n;++i){
        for(j=0;j<grille.n;++j){
            if(jeton=='V'){
                jeton_v(grille,poi_tot,pen_tot,i,j);
                grille.sl[i][j]='v';
            }
        }
    }
    grille.sl=save_grille_sl;
    return poi_tot-pen_tot;
}