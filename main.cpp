#include <iostream>
#include "labirinto.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
using namespace std;
void help();

int main(int argc, char * argv[]){
    path p;
    int i=0, alg;
    maze * L;
    int height,width;
    double WallDensity;
    bool solve=false, generate=false,showpath=false;
    char * IF=NULL;
    char * OF=NULL;
    
    for (i=1;i<argc;i++){//percorre os argumentos
        if(!strcmp("-s",argv[i])){//solve
            solve = true;
            IF = strdup(argv[++i]);//input file
            sscanf(argv[++i],"%d",&alg);
            continue;
        }

        if(!strcmp("-w",argv[i])){
            OF = strdup(argv[++i]);
            continue;
        }

        if(!strcmp("-g",argv[i])){
            generate = true;
            sscanf(argv[++i],"%d",&height);
            sscanf(argv[++i],"%d",&width);
            sscanf(argv[++i],"%lf",&WallDensity);
            continue;
        }
        if(!strcmp("-p",argv[i])){
            showpath = true;
        }

        printf("\"%s\" foi inesperado!\n",argv[i]);
        exit(0);
    }

    if(argc==1)help();
    
    if(generate){
        L =  new maze(height, width , WallDensity);
        if(OF)
            L->mazeToFile(OF);
        else
            L->print();
    }
    
    if(solve){
        if(IF){//Arquivo
            L = new maze(IF);
            p = L->solve(alg);
        }
        //else
            //L = new maze(); precisa ter um construtor a partir do stdio...
        
        if(OF)
            L->mazeToFile(OF);
        else
            L->print(L,p);

    }




    return 0;   
    
    
    i=0;
    srand (time(NULL));

    L =  new maze(20, 30 , 0.35);

    while (1){
        p = L->solve(2);                            //resolver
        
        if(i<p.steps){                              //Se o numero de passos do labirinto anterior for menor
            i=p.steps;
            printf("%d\n",i);
            L->print(L,p);                          //mostra o novo na tela
            L->mazeToFile("CaminhoGrande.maze");    //Salva no arquivo
        }
        L->renew(0.35);
    }
    return 0;
}

        //maze * L =  new maze("labirinto.txt");
        //L->mazeToFile("OutroArquivo.maze");//salvar no arquivo
        //maze * M = new maze("OutroArquivo.maze");//ler do arquivo
        //L->print();//mostrar na tela

void help(){
    printf("página de ajuda\n");    

}