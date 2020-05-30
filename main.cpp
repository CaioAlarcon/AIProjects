#include <iostream>
#include "labirinto.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
void help();

int main(int argc, char * argv[]){
    path p;
    int i=0, alg,seed=-1;
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
            if(++i!=argc)
                sscanf(argv[i],"%d",&alg);
            else alg = 0;
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
        if(!strcmp("--seed",argv[i])){
            sscanf(argv[++i],"%d",&seed);
            continue;
        }
        printf("\"%s\" foi inesperado!\n",argv[i]);
        exit(0);
    }

    if(seed==-1)
        srand (time(NULL));
    else
        srand(seed);

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
            L->mazeToFile(OF);//fazer a versão que salva a solução tbm 
        else
            L->print(L,p);

    }
    cout << "Tempo para resolver: "<< L->SolveTime() << " ms\n";
    return 0;   
}

void help(){
    printf("página de ajuda\n");    

}