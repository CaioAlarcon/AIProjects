#include <iostream>
#include "labirinto.h"
#include <stdlib.h>
#include <time.h>
using namespace std;



int main(){
    srand (time(NULL));
    
    maze * L =  new maze(29, 26  , 0.35);//criar labirinto aleatório com densidade de 40%
    
    //maze * L =  new maze("labirinto.txt");
    //L->mazeToFile("OutroArquivo.maze");//salvar no arquivo
    //maze * M = new maze("OutroArquivo.maze");//ler do arquivo
    //L->print();//mostrar na tela
    
    L->solve(0);

    L->print();

    return 0;

}