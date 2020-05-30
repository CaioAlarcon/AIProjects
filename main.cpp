#include <iostream>
#include "labirinto.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
void help();//Alguém me ajuda

int main(int argc, char * argv[]){
    path p;
    int i=0, alg=0,seed=-1;
    maze * L;
    int height,width;
    double WallDensity;
    bool solve=false, generate=false,showpath=false,log, print = false;
    char * IF=NULL;
    char * OF=NULL;
    
    for (i=1;i<argc;i++){//percorre os argumentos
        if(!strcmp("-s",argv[i])){//solve
            solve = true;
            if(++i!=argc)
                IF = strdup(argv[i]);//input file
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
            if(argc < i + 3){
                cout << "faltam argumentos!\n"; 
                cout << "-g altura largura densidade\n exemplo: -g 20 30 0.3\n";
                exit(0);
            }
            generate = true;
            sscanf(argv[++i],"%d",&height);
            sscanf(argv[++i],"%d",&width);
            sscanf(argv[++i],"%lf",&WallDensity);
            continue;
        }
        if(!strcmp("-p",argv[i])){
            showpath = true;
            continue;
        }
        if(!strcmp("--seed",argv[i])){
            sscanf(argv[++i],"%d",&seed);
            continue;
        }
        if(!strcmp("--log",argv[i])){
            i++;
            log = true;
            continue;
        }
        if(!strcmp("--print",argv[i])){
            i++;
            print = true;
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
        else if (print)
            L->print();
    }
    
    if(solve){
        if(IF)//Arquivo
            L = new maze(IF);
        else
            L = new maze(); 
        p = L->solve(alg);
        if(OF)
            L->print(L,p,OF);
        else if (print)
            L->print(L,p);
    }
    L->log();
    cout << "Tempo para resolver: "<< L->SolveTime() << " ms\n";
    return 0;   
}

void help(){
    printf("página de ajuda\n");    
}