#include <iostream>
#include <array>
using vec=std::array<int,2>;
using mat=std::array<vec,10>;
using mat3=std::array<mat,10>;

void fonc(mat3 mat3){
    for(int i=0;i<10;++i){
        //std::cout<<vec[i]<<std::endl;
        for(int j=0;j<10;++j){
            //std::cout<<mat[i][j];
            for(int k=0;k<2;k++){
                std::cout<<mat3[i][j][k]<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<std::endl;
    }
}

int main(){
    vec vec;
    mat mat;
    mat3 mat3;
    //vec={1,2};
    mat={1,-1,2};
    //mat3={1,-1,2,-1};
    mat3[0][1][0]=12;
    fonc(mat3);
}