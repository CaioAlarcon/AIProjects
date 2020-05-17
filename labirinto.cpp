#include "labirinto.h"
#include <stdlib.h>
#include <stdio.h>


maze::maze(char * FileName){
    FILE * fp;
    int x, y;
    
    //Abrir arquivo para ler dimensões do labirinto
    fp = fopen(FileName,"r+");
    fscanf(fp, "%d %d\n",&this->rows, &this->columns);
    

    //Criar array dinâmico para conter o labirinto
    this->M = (char**)malloc(sizeof(char*)*this->rows);
    for(x=0;x<this->rows;x++){
        this->M[x] = (char*)malloc(sizeof(char)*this->columns);
    }

    //Ler do arquivo o labirinto
    for(x=0;x<this->rows;x++){
        for(y=0;y<this->columns;y++){
            fscanf(fp,"%c",&this->M[x][y]);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
   
}

void maze::print(){
    int i,j;
    for(j=0;j<this->rows;j++){
        for(i=0;i<this->columns;i++)
            printf("%c",this->M[j][i]);
        printf("\n");
    }
}
