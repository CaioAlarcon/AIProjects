#include <stdio.h>
#include <stdlib.h>

struct Labirinto{
    int linha;
    int coluna;
    char ** M;
};

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



int main(){
    struct Labirinto labrinto;
    int i, j;

    labrinto = LerLabirinto("labirinto.txt");
    printf("%d %d\n",labrinto.linha, labrinto.coluna);

    for(i=0;i<labrinto.linha;i++){
        for(j=0;j<labrinto.coluna;j++){
            printf("%c",labrinto.M[i][j]);
        }
        printf("\n");
    }

    
    return 0;
}