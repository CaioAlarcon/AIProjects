#include <iostream>
#include "labirinto.h"
using namespace std;



int main(){
    maze * L =  new maze("labirinto.txt");
    maze * M = new maze(L);
    M->print();
    
    
    return 0;
}
