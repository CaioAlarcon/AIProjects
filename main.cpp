#include <iostream>
#include "labirinto.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;



int main(){
    path p;
    int i=0;
    srand (time(NULL));
    
    
    while (1){
        /* code */
        maze * L =  new maze(29, 26  , 0.35);//criar labirinto aleatório com densidade de 40%
        p = L->solve(0);                     //resolver
        
        if(i<p.steps){//Se o numero de passos do labirinto anterior for menor
            L->print();//mostra o novo na tela
            L->mazeToFile("CaminhoGrande.maze");//Salva no arquivo
            i=p.steps;
        }
        //printf("%d\n",p.steps);
        //L->print(p);
    }
    return 0;

}

        //maze * L =  new maze("labirinto.txt");
        //L->mazeToFile("OutroArquivo.maze");//salvar no arquivo
        //maze * M = new maze("OutroArquivo.maze");//ler do arquivo
        //L->print();//mostrar na tela