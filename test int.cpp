#include <iostream>

int main(){
    //int a[1000][1000][3];
    int i,j,k;
    int *** a;
    int ** b;
    a=new int **[4096];
    for(i=0;i<4096;++i){
        a[i]=new int*[4096];
        for(j=0;j<4096;++j){
            a[i][j]=new int[3];
        }
    }
    b=a[0];
    int n=5;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            for(k=0;k<3;++k){
                a[i][0][0]=i;
                std::cout<<a[i][j][k]<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
    for(j=0;j<5;++j){
        for(k=0;k<3;++k){
            std::cout<<b[j][k]<<" ";  
        }
        std::cout<<std::endl;
    }
}

        val_1comb=new int*[4096];
        for(int j=0;j<4096;++j){
            val_1comb[j]=new int[3];
        }

    int *** val_comb_vert;
    val_comb_vert=new int **[4096];
    for(i=0;i<4096;++i){
        val_comb_vert[i]=new int*[4096];
        for(j=0;j<4096;++j){
            val_comb_vert[i][j]=new int[3];
        }
    }