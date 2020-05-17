#include "labirinto.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>

char ** DinArray(int rows, int columns){//Criar array dinâmico para conter o labirinto
    int x, y;
    char ** A;
    A = (char**)malloc(sizeof(char*)*rows);
    for(x=0;x<rows;x++){
        A[x] = (char*)malloc(sizeof(char)*columns);
    }
    return A;
}

maze::maze(int rows, int columns, double WallDensity){//Cria labirinto com densidade de paresdes específica
    int x, y;
    this->M = DinArray(rows,columns);
    this->rows = rows;
    this->columns = columns;
    //criar
    for(x=0;x<this->rows;x++){
        for(y=0;y<this->columns;y++){
            this->M[x][y] = ((double)rand()/RAND_MAX) < WallDensity? '-':'*'    ;
        }
    }
    this->start = {0,rand()%columns};
    this->goal = {rows-1,rand()%rows};
    this->M[this->start.x ][this->start.y]='#';
    this->M[this->goal.x ][this->goal.y]='$';
}

maze::maze(char * FileName){//  Construtor a partir de arquivo
    FILE * fp;
    int x, y;
    
    //Abrir arquivo para ler dimensões do labirinto
    fp = fopen(FileName,"r+");
    fscanf(fp, "%d %d\n",&this->rows, &this->columns);
    

    //Criar array dinâmico para conter o labirinto
    this->M = DinArray(this->rows,this->columns);

    //Ler do arquivo o labirinto
    for(x=0;x<this->rows;x++){
        for(y=0;y<this->columns;y++){
            fscanf(fp,"%c",&this->M[x][y]);
            if(this->M[x][y]=='#') this->start = {x,y};
            if(this->M[x][y]=='$') this->goal = {x,y};
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
   
}

maze::maze(const maze* mz){//    Construtor cópia
    int x, y;
    *this = *mz;
    
    this->M = DinArray(this->rows,this->columns);

    //copiar
    for(x=0;x<this->rows;x++){
        for(y=0;y<this->columns;y++){
            this->M[x][y] = mz->M[x][y];
        }
    }
}

void maze::print(){
    int i,j;
    for(j=0;j<this->rows;j++){
        for(i=0;i<this->columns;i++)
            printf("%c",this->M[j][i]);
        printf("\n");
    }
}
