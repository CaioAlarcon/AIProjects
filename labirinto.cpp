#include "labirinto.h"
#include <stdlib.h>
#include <stdio.h>


char ** DinArray(int rows, int columns){//Criar array dinâmico para conter o labirinto
    int x, y;
    char ** A;
    A = (char**)malloc(sizeof(char*)*rows);
    for(x=0;x<rows;x++){
        A[x] = (char*)malloc(sizeof(char)*columns);
    }
    return A;
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
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
   
}

maze::maze(const maze* mz){//    Construtor cópia
    int x, y;
    //*this = *mz;
    //this->columns = mz->columns;
    
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
