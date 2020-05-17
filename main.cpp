#include <iostream>
#include "labirinto.h"
#include <stdlib.h>
#include <time.h>
using namespace std;



int main(){
    srand (time(NULL));
    maze * L =  new maze(30, 60, 0.4);
    maze * M = new maze(L);
    
    M->print();
    
    
    return 0;

}