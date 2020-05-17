#pragma once 

class maze{

    private:
        int rows;           
        int columns;       
        char ** M;          //Matriz dinâmica que guarda a forma do labirinto
    public:
    maze(char * FileName);  //Construtor a partir do nome do arquivo

    void print();           //Imprime labirinto na tela



};


