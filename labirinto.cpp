#include <stdio.h>
#include <stdlib.h>



//isso aqui precisa ser transformado no construtor
struct Labirinto LerLabirinto(char * NomeArquivo){
    FILE * fp;
    int x, y;
    struct  Labirinto L;
    
    fp = fopen(NomeArquivo,"r+");
    
    fscanf(fp, "%d %d\n",&L.linha, &L.coluna);
    
    L.M = (char**)malloc(sizeof(char*)*L.linha);

    for(x=0;x<L.linha;x++){
        L.M[x] = (char*)malloc(sizeof(char)*L.coluna);
    }

    for(x=0;x<L.linha;x++){
        for(y=0;y<L.coluna;y++){
            fscanf(fp,"%c",&L.M[x][y]);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
    return L;   
}


