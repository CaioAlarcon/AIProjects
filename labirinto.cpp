#pragma once
#include "labirinto.h"

#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <list>
#include<bits/stdc++.h>

using namespace std;

void maze::solve(int algs){
    
    AStar();
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

maze::maze(char * FileName){//Construtor a partir de arquivo
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

maze::maze(const maze* mz){//Construtor cópia
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
void maze::tracePath (node ** NodeInfo){    
    int row = this->goal.x;
    int col = this->goal.y; 
    point * n;
    stack<point*> Path; 
    
    while (!(NodeInfo[row][col].parent_i == row  && NodeInfo[row][col].parent_j == col )){ 
        n = (point*)malloc(sizeof(point));
        n->x = row;
        n->y = col;
        Path.push (n);
        int temp_row = NodeInfo[row][col].parent_i; 
        int temp_col = NodeInfo[row][col].parent_j; 
        row = temp_row; 
        col = temp_col; 
    }
    n = (point*)malloc(sizeof(point));
    n->x = row;
    n->y = col;
    Path.push (n); 
    printf("[");
    while (!Path.empty()){ 
        n = Path.top(); 
        Path.pop();
        this->M[n->x][n->y]='@';
        printf("(%d,%d)",n->x,n->y);
        if(!Path.empty())
            printf(",");
        free(n);
    }
    printf("]");
    printf("\n");
}

void maze::AStar(){
    int i,j;
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
    open.insert(make_pair (0.0, make_pair (i, j))); 
  
 
    bool foundDest = false; 
  
    while (!open.empty()){
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
                 
                tracePath ((node**)NodeInfo); 
                foundDest = true; 
                return; 
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
                // Set the Parent of the destination cell 
                NodeInfo[i+1][j].parent_i = i; 
                NodeInfo[i+1][j].parent_j = j; 
                 
                tracePath ((node**)NodeInfo); 
                foundDest = true; 
                return; 
            }   
            else if (!closed[i+1][j] &&  isUnBlocked(this->M, i+1, j)){ 
                gNew = NodeInfo[i][j].g + 1.0; 
                hNew = H(i+1, j, this->goal); 
                fNew = gNew + hNew; 
  
                 
                if (NodeInfo[i+1][j].f == FLT_MAX || NodeInfo[i+1][j].f > fNew){ 
                    open.insert( make_pair(fNew, make_pair(i+1, j))); 
  
                    // Update the details of this cell 
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
                // Set the Parent of the destination cell 
                NodeInfo[i][j-1].parent_i = i; 
                NodeInfo[i][j-1].parent_j = j; 
                 
                tracePath ((node**)NodeInfo); 
                foundDest = true; 
                return; 
            }   
            else if (!closed[i][j-1] &&  isUnBlocked(this->M, i, j-1)){ 
                gNew = NodeInfo[i][j].g + 1.0; 
                hNew = H(i, j-1, this->goal); 
                fNew = gNew + hNew; 
  
                 
                if (NodeInfo[i][j-1].f == FLT_MAX || NodeInfo[i][j-1].f > fNew){ 
                    open.insert( make_pair(fNew, make_pair(i, j-1))); 
  
                    // Update the details of this cell 
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
                // Set the Parent of the destination cell 
                NodeInfo[i][j+1].parent_i = i; 
                NodeInfo[i][j+1].parent_j = j; 
                 
                tracePath ((node**)NodeInfo); 
                foundDest = true; 
                return; 
            }   
            else if (!closed[i][j+1] &&  isUnBlocked(this->M, i, j+1)){ 
                gNew = NodeInfo[i][j].g + 1.0; 
                hNew = H(i, j+1, this->goal); 
                fNew = gNew + hNew; 
  
                 
                if (NodeInfo[i][j+1].f == FLT_MAX || NodeInfo[i][j+1].f > fNew){ 
                    open.insert( make_pair(fNew, make_pair(i, j+1))); 
  
                    // Update the details of this cell 
                    NodeInfo[i][j+1].f = fNew; 
                    NodeInfo[i][j+1].g = gNew; 
                    NodeInfo[i][j+1].h = hNew; 
                    NodeInfo[i][j+1].parent_i = i; 
                    NodeInfo[i][j+1].parent_j = j; 
                } 
            } 

        } 

    }

    if (foundDest == false) 
        printf("Falhou\n");


}

