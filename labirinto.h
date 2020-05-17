#pragma once 

class maze{
    typedef struct{
        int x,y;
    }point;

    private:
        int rows;           
        int columns;
        point start;
        point goal;       
        char ** M;                      //Matriz dinâmica que guarda a forma do labirinto
    public:
    maze(int rows, int lines, double WallDensity); //Construtor aleatório
    maze(char*);                        //Construtor a partir do arquivo
    maze(const maze*);                  //Construtor cópia
    void mazeToFile(char * FileName);        //Salva o labirinto em arquivo
    void print();                       //Imprime labirinto na tela
};


