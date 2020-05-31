 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Este programa cria um script para criar labirintos diversos que serão testados posteriormente

int main(){
	int i,k,l,n=0;
    float j;
	FILE * p=0;
    FILE * p2=0;
    
	p = fopen ("criatestes.sh","w");
    p2 = fopen ("testatudo.sh","w");
	
                        //densidade
        for(k=10;k<=10000;k*=10)               //altura
            for(l=k;l<=10000;l*=10)
                for(j=0.0;j<0.40;j+=0.05){
                    fprintf(p,"./maze -g %d %d %lf -w arquivo%d.maze --seed %u ",k,l,j,n,(unsigned int)rand());
                    if(k<100)fprintf(p,"& disown\n");
                        else fprintf(p,"\n");
                    for(i=0;i<=5;i++) {                       //algoritmo   
                        fprintf(p2,"./maze -s arquivo%d.maze %u --log ",n,i);
                        if(k<100)fprintf(p2,"& disown\n");
                        else fprintf(p2,"\n");
                    }
                n++;         
            }
	fclose (p);
    fclose (p2);
    
}