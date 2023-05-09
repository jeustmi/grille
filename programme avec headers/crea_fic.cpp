#include <fstream>
#include <iostream>
#include <string>

int main(){
    int n1;
    std::string n2;
    std::cin>>n1;
    std::cin>>n2;
    std::ofstream fic("fic/probleme_"+n2+"_w.txt");
    fic << n1;
    fic << " -1";
    fic << std::endl;
    for(int i=0;i<n1;++i){
        for(int j=0;j<n1;++j){
            fic << "-1 ";
        }
        fic << std::endl;
    }
}