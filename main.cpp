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
    bool solve=false, generate=false,showpath=false,log=false, print = false;
    char * IF=NULL;
    char * OF=NULL;
    
    for (i=1;i<argc;i++){//percorre os argumentos
        if(!strcmp("-s",argv[i])){//solve
            solve = true;
            if(++i!=argc)
                IF = strdup(argv[i++]);//input file
            if(i!=argc)
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
            log = true;
            continue;
        }
        if(!strcmp("--print",argv[i])){
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
        else if (print){
            L->print(L,p);   
        }
        if(showpath)
            L->print(p);
        if(log)
            L->log();
        
        cout << "Tempo para resolver: "<< L->SolveTime() << " ms\n";
        cout << "Algoritmo usado: "<< L->AlgName() << "\n";
    }
    
    
    
    return 0;   
}

void help(){
   cout << "usage: maze [options] \n" << 
"\n"<< 
"-s\t\t:resolve\t\t(-s alg)\n"<< 
"-g\t\t:gera o labirinto\t(-g h w wd)\n"<< 
"-w\t\t:escreve no arquivo\t(-w arquivo)\n"<< 
"-p\t\t:mostrar passos\n"<< 
"--seed\t\t:especifica a seed\t(--seed 465015)\n"<< 
"--log\t\t:habilita o arquivo de log\n"<< 
"--print\t\t:mostra na tela\n"<< 
"\n"<< 
"alg\t\t:0-6\n"<< 
"0\t\t:rand\n"<< 
"1\t\t:profundidade\n"<< 
"2\t\t:largura\n"<< 
"3\t\t:BestFirst\n"<< 
"4\t\t:AStar\n"<< 
"5\t\t:Dijkstra\n"<< 
"6\t\t:Hill Climbing\n"<< 
"\n"<< 
"h\t\t:altura do labirinto\n"<< 
"w\t\t:largura do labirinto\n"<< 
"wd\t\t:densidade de obstáculos\n"<< 
"\n"<< 
"Exemplo:\n"<< 
"Gerar um labirinto 50X50 com densidade 20% e salvar no arquivo maze.txt:\n"<< 
"./maze -g 50 50 0.2 -w maze.txt\n"<< 
"\n"<< 
"Resolver o labirinto salvo em maze.txt usando AStar e mostrar os passos na tela:\n"<< 
"./maze -s maze.txt 4 -p \n"<<
"\n"<< 
"Resolver o labirinto salvo em maze.txt usando AStar e mostrar o caminho na tela:\n"<< 
"./maze -s maze.txt 4 --print \n\n";

}