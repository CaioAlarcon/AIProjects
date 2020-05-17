#pragma once 

class maze{

    private:
        int rows;           
        int columns;       
        char ** M;          //Matriz dinâmica que guarda a forma do labirinto
    public:
    maze(char*);           //Construtor a partir do nome do arquivo
    maze(const maze*); 
    void print();           //Imprime labirinto na tela
};


