#include <iostream>
#include "labirinto.h"
using namespace std;



int main(){
    maze * L =  new maze("labirinto.txt");
    L->print();
    
    
    return 0;
}
