#pragma once



class maze{
    typedef struct{
        int x,y;
    }point;
    typedef struct{
        int parent_i, parent_j;
        double f,g,h;
    }node;
    private:
        bool isValid(int i, int j);
        bool isUnBlocked(char ** grid, int i,int j);
        double H(int i, int j, point goal);
        bool IsDestination(int x, int y);
        void tracePath (node ** NodeInfo);
        int rows;           
        int columns;
        point start;
        point goal;       
        char ** M;                                  //Matriz dinâmica que guarda a forma do labirinto
        void AStar();
    public:
    void solve(int alg);                            //Resolve o labirinto usando um algoritmo específico
    maze(int rows, int lines, double WallDensity);  //Construtor aleatório
    maze(char*);                                    //Construtor a partir do arquivo
    maze(const maze*);                              //Construtor cópia
    void mazeToFile(char * FileName);               //Salva o labirinto em arquivo
    void print();                                   //Imprime labirinto na tela
};


