#include <set>
#include <time.h>

typedef struct{
    int x,y;
}point;

typedef struct{
    int steps;
    point * P;  //vetor contendo os pontos referentes aos passos
}path;

class maze{

    typedef struct{
        int parent_i, parent_j;
        float f,g,h;
    }node;

    private:
        char * FN;
        int Alg;
        char Algname[15];
        bool foundDest;
        path PATH;
        bool isValid(point);
        bool isUnBlocked(char ** grid, point);
        double H(int i, int j, point goal);
        bool IsDestination(point);
        path tracePath (node ** NodeInfo);
        node ** NodeInfo;
        int rows;           
        int columns;
        point start;
        point goal;       
        char ** M;                                      //Matriz dinâmica que guarda a forma do labirinto
        path HillClimbing(path p);
        path Search(int);
        void criteria(int, int, int, point, std::set<std::pair<double, std::pair<int, int> > > *);   //Aplica aos algoritmos seus respectivos critérios
    public:
        void AlgName(char name[10]);
        char * AlgName();
        double SolveTime();
        maze();                                         //Construtor a partir do stdio
        maze(int rows, int lines, double WallDensity);  //Construtor aleatório
        maze(char*);                                    //Construtor a partir do arquivo
        maze(const maze*);                              //Construtor cópia
        ~maze();
        path solve(int alg);                            //Resolve o labirinto usando um algoritmo específico
        void mazeToFile(const char* FileName);          //Salva o labirinto em arquivo
        void print();                                   //Imprime labirinto na tela
        void print(path p);                             //imprime o caminho na tela
        void print(path p,char * FileName);             //Imprime caminho no arquivo.
        void print(path p,void * fp);                   //Imprime caminho no arquivo.
        void print(maze m, path p);                     //imprime o caminho no labirinto
        void print(maze m, path p,char * FileName);     //imprime no arquivo o caminho no labirinto
        void renew(double);                             //reinicia o labirinto 
        void log();
};


