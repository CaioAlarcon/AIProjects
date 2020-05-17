#include <iostream>
#include "labirinto.h"
#include <stdlib.h>
#include <time.h>
using namespace std;



int main(){
    srand (time(NULL));
    maze * L =  new maze(30, 60, 0.4);//criar labirinto aleatório com densidade de 40%
    L->mazeToFile("OutroArquivo.maze");//salvar no arquivo
    maze * M = new maze("OutroArquivo.maze");//ler do arquivo
    M->print();//mostrar na tela
    
    
    return 0;

}