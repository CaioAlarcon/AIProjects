#pragma once
#include "labirinto.h"

#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <list>
#include<bits/stdc++.h>

using namespace std;

void maze::print(path p){
    int i;
    printf("[");
    for(i=0;i<p.steps-1;i++)
        printf("(%d,%d),",p.P[i].x,p.P[i].y);
    printf("(%d,%d)]\n",p.P[i].x,p.P[i].y);
}
void maze::print(){
    int i,j;
    for(j=0;j<this->rows;j++){
        for(i=0;i<this->columns;i++)
            printf("%c",this->M[j][i]);
        printf("\n");
    }
}

void maze::print(maze m, path p){
    char M[m.rows][m.columns];
    int i,j;
    for(i=0;i<m.rows;i++){
        for(j=0;j<m.columns;j++){
            M[i][j] = m.M[i][j];
        }
    }
    for(i=0;i<p.steps;i++)
        M[p.P[i].x][p.P[i].y]='@';
    
    for(i=0;i<m.rows;i++){
        for(j=0;j<m.columns;j++)
            printf("%c",M[i][j]);
    printf("\n");
    }
    printf("\n");

}
path maze::solve(int algs){
    return AStar();
}

void maze::mazeToFile(char * FileName){
    FILE * fp;
    int x, y;
    
    //Abrir arquivo para gravar dimensões do labirinto
    fp = fopen(FileName,"w+");
    fprintf(fp, "%d %d\n",this->rows, this->columns);
    
    //Gravar labirinto em disco
    for(x=0;x<this->rows;x++){
        for(y=0;y<this->columns;y++){
            fprintf(fp,"%c",this->M[x][y]);
            if(this->M[x][y]=='#') this->start = {x,y};
            if(this->M[x][y]=='$') this->goal = {x,y};
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
char ** DinArray(int rows, int columns){//Criar array dinâmico para conter o labirinto
    int x, y;
    char ** A;
    A = (char**)malloc(sizeof(char*)*rows);

    for(x=0;x<rows;x++){
        A[x] = (char*)malloc(sizeof(char)*columns);
    }
    return A;
}

void maze::renew(double WallDensity){
    int x, y;
    for(x=0;x<this->rows;x++){
        for(y=0;y<this->columns;y++){
            this->M[x][y] = ((double)rand()/RAND_MAX) < WallDensity? '-':'*';
        }
    }
    this->start = {0,rand()%columns};
    this->goal = {rows-1,rand()%rows};
    this->M[this->start.x ][this->start.y]='#';
    this->M[this->goal.x ][this->goal.y]='$';
    
}



maze::maze(int rows, int columns, double WallDensity){//Cria labirinto com densidade de paresdes específica
    int x, y;
    this->M = DinArray(rows,columns);
    this->rows = rows;
    this->columns = columns;
    PATH.P=NULL;
    PATH.steps=-1;
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

maze::maze(char * FileName){//Construtor a partir de arquivo
    FILE * fp;
    int x, y;
    PATH.P=NULL;
    PATH.steps=-1;
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

maze::maze(const maze* mz){//Construtor cópia
    int x, y;
    *this = *mz;
    PATH.P=NULL;
    PATH.steps=-1;
    this->M = DinArray(this->rows,this->columns);

    //copiar
    for(x=0;x<this->rows;x++){
        for(y=0;y<this->columns;y++){
            this->M[x][y] = mz->M[x][y];
        }
    }
}

maze::~maze(){//Destrutor
    int x;//Libera heap usado para armazenar o labirinto
    
    for(x=0;x<rows;x++)
        free(M[x]);
    
    free(M);
}

typedef pair<double, pair<int, int> > pPair;

bool maze::isValid(int i, int j){
    return (i >= 0) && (i < this->rows) && (j >= 0) && (j < this->columns);
}
bool maze::isUnBlocked(char ** grid, int i,int j){
    return (grid[i][j]=='-'?false:true);
}

double maze::H(int i, int j, point goal){ //Efetua o calculo da heuristica
    return ((double)sqrt ((i - goal.x)*(i - goal.x) + (j - goal.y)*(j - goal.y))); 
}
bool maze::IsDestination(int x, int y){
    return (this->goal.x == x && this->goal.y == y);
}
path maze::tracePath (node ** NodeInfo  ){    
    int row = this->goal.x;
    int col = this->goal.y; 
    int i=0,steps=0;
    point * n;
    stack<point*> Path; 
    steps = 0; 
    while (!(NodeInfo[row][col].parent_i == row  && NodeInfo[row][col].parent_j == col )){ 
        n = (point*)malloc(sizeof(point));
        n->x = row;
        n->y = col;
        Path.push (n);
        steps++;
        int temp_row = NodeInfo[row][col].parent_i; 
        int temp_col = NodeInfo[row][col].parent_j; 
        row = temp_row; 
        col = temp_col; 
    }
    n = (point*)malloc(sizeof(point));
    n->x = row;
    n->y = col;
    Path.push (n);
    steps++;
    
    if(PATH.steps < steps){
        PATH.steps = steps;
        PATH.P = (point*)realloc(PATH.P, sizeof(point)*PATH.steps);//reserva na heap espaço para o caminho
    }
    
    
    while (!Path.empty()){ 
        n = Path.top(); 
        Path.pop();
        //this->M[n->x][n->y]='@';//Criar função que, em vez de fazer isso, imprima sem precisar alterar o labirinto
        PATH.P[i++]=*n;//isso copia o valor, não o endereço
        //printf("(%d,%d)",n->x,n->y);//usa sprintf envez
        //if(!Path.empty())
        //    printf(",");
        free(n);
    }

    
    return PATH;
}

path maze::AStar(){
    int i,j;
    path ret;
    ret.steps = -1;//indica que não tem caminho
    std::list <int> a;
    bool ** closed;
    
    closed = (bool**)malloc(sizeof(bool*)*this->rows);
    for(i=0;i<this->rows;i++)
        closed[i]=(bool*)malloc(sizeof(bool)*this->columns);
    
    node ** NodeInfo;
    NodeInfo = (node**)malloc(sizeof(node*)*this->rows);
    for(i=0;i<this->rows;i++)
        NodeInfo[i]=(node*)malloc(sizeof(node)*this->columns);

    for (i=0; i<this->rows; i++) { 
        for (j=0; j<this->columns; j++){ 
            NodeInfo[i][j].f = FLT_MAX; 
            NodeInfo[i][j].g = FLT_MAX; 
            NodeInfo[i][j].h = FLT_MAX; 
            NodeInfo[i][j].parent_i = -1; 
            NodeInfo[i][j].parent_j = -1; 
        } 
    } 

    i = this->start.x;
    j = this->start.y;

    NodeInfo[i][j].f = 0.0; 
    NodeInfo[i][j].g = 0.0; 
    NodeInfo[i][j].h = 0.0; 
    NodeInfo[i][j].parent_i = i; 
    NodeInfo[i][j].parent_j = j; 

    set<pPair> open; 
    open.insert(make_pair(0.0, make_pair (i, j))); 
  
 
    bool foundDest = false; 
  
    while (!open.empty() && !foundDest ){
        pPair p = *open.begin(); 

        open.erase(open.begin()); 
  
        // Add this vertex to the closed list 
        i = p.second.first; 
        j = p.second.second; 
        closed[i][j] = true;

        double gNew, hNew, fNew; 

        if (isValid(i-1, j)){
            if (IsDestination(i-1,j)){ 
                // Set the Parent of the destination cell 
                NodeInfo[i-1][j].parent_i = i; 
                NodeInfo[i-1][j].parent_j = j; 
                foundDest = true;
                ret = tracePath ((node**)NodeInfo);
                continue;

            }   
            else if (!closed[i-1][j] &&  isUnBlocked(this->M, i-1, j)){ 
                gNew = NodeInfo[i][j].g + 1.0; 
                hNew = H(i-1, j, this->goal); 
                fNew = gNew + hNew; 
  
                 
                if (NodeInfo[i-1][j].f == FLT_MAX || NodeInfo[i-1][j].f > fNew){ 
                    open.insert( make_pair(fNew, make_pair(i-1, j))); 
  
                    // Update the details of this cell 
                    NodeInfo[i-1][j].f = fNew; 
                    NodeInfo[i-1][j].g = gNew; 
                    NodeInfo[i-1][j].h = hNew; 
                    NodeInfo[i-1][j].parent_i = i; 
                    NodeInfo[i-1][j].parent_j = j; 
                } 
            } 
        }
        

        if (isValid(i+1, j)){
            if (IsDestination(i+1,j)){ 
                NodeInfo[i+1][j].parent_i = i; 
                NodeInfo[i+1][j].parent_j = j; 
                foundDest = true; 
                ret = tracePath ((node**)NodeInfo);
                continue;
            }   
            else if (!closed[i+1][j] &&  isUnBlocked(this->M, i+1, j)){ 
                gNew = NodeInfo[i][j].g + 1.0; 
                hNew = H(i+1, j, this->goal); 
                fNew = gNew + hNew; 
  
                 
                if (NodeInfo[i+1][j].f == FLT_MAX || NodeInfo[i+1][j].f > fNew){ 
                    open.insert( make_pair(fNew, make_pair(i+1, j))); 
  
                    NodeInfo[i+1][j].f = fNew; 
                    NodeInfo[i+1][j].g = gNew; 
                    NodeInfo[i+1][j].h = hNew; 
                    NodeInfo[i+1][j].parent_i = i; 
                    NodeInfo[i+1][j].parent_j = j; 
                } 
            } 

        }

        
        if (isValid(i, j-1)){
            if (IsDestination(i,j-1)){ 
                NodeInfo[i][j-1].parent_i = i; 
                NodeInfo[i][j-1].parent_j = j; 
                foundDest = true; 
                ret = tracePath ((node**)NodeInfo);
                continue;
            }   
            else if (!closed[i][j-1] &&  isUnBlocked(this->M, i, j-1)){ 
                gNew = NodeInfo[i][j].g + 1.0; 
                hNew = H(i, j-1, this->goal); 
                fNew = gNew + hNew; 
  
                 
                if (NodeInfo[i][j-1].f == FLT_MAX || NodeInfo[i][j-1].f > fNew){ 
                    open.insert( make_pair(fNew, make_pair(i, j-1))); 
  
                    
                    NodeInfo[i][j-1].f = fNew; 
                    NodeInfo[i][j-1].g = gNew; 
                    NodeInfo[i][j-1].h = hNew; 
                    NodeInfo[i][j-1].parent_i = i; 
                    NodeInfo[i][j-1].parent_j = j; 
                } 
            } 
        }
        

        if (isValid(i, j+1)){
            if (IsDestination(i,j+1)){ 
                NodeInfo[i][j+1].parent_i = i; 
                NodeInfo[i][j+1].parent_j = j; 
                foundDest = true;  
                ret = tracePath ((node**)NodeInfo);
                continue; 
            }   
            else if (!closed[i][j+1] &&  isUnBlocked(this->M, i, j+1)){ 
                gNew = NodeInfo[i][j].g + 1.0; 
                hNew = H(i, j+1, this->goal); 
                fNew = gNew + hNew; 
  
                 
                if (NodeInfo[i][j+1].f == FLT_MAX || NodeInfo[i][j+1].f > fNew){ 
                    open.insert( make_pair(fNew, make_pair(i, j+1))); 
  
                    NodeInfo[i][j+1].f = fNew; 
                    NodeInfo[i][j+1].g = gNew; 
                    NodeInfo[i][j+1].h = hNew; 
                    NodeInfo[i][j+1].parent_i = i; 
                    NodeInfo[i][j+1].parent_j = j; 
                } 
            }
        }
    }

    //desalocar tudo o que foi usad

    //Liberar closed list
    for(i=0;i<this->rows;i++)
        free(closed[i]);
    free(closed);
    
    //Liberar NodeInfo
    for(i=0;i<this->rows;i++)
        free(NodeInfo[i]);
    free(NodeInfo);

    return ret;
}

