#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main(){
    std::srand(std::time(nullptr));
    int n1,n;
    std::string n2,ch;
    std::cin>>n1;
    std::cin>>n2;
    std::ofstream fic("../fic/probleme_"+n2+"_w.txt");
    fic << n1;
    n=std::rand()%200-100;
    ch=std::to_string(n);
    std::cout<<ch<<std::endl;
    fic << " "+ch;
    fic << std::endl;
    for(int i=0;i<n1;++i){
        for(int j=0;j<n1;++j){
            n=std::rand()%200-100;
            ch=std::to_string(n);
            fic << ch+" ";
        }
        fic << std::endl;
    }
}