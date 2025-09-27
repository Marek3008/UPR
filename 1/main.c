#include <stdio.h>
#include <stdlib.h>

struct Bankovka{
    int value;
    int num;
};

int main(){

    system("clear");

    int cislo = 9420;
    struct Bankovka bankovky[] = {
        {5000, 0},
        {2000, 0},
        {1000, 0},
        {500, 0},
        {200, 0},
        {100, 0}
    };

    for(int i = 0; i < 6; i++){
        while(cislo >= bankovky[i].value){
            cislo -= bankovky[i].value;
            bankovky[i].num++;
        }
        printf("Bankovka %d: %d\n", bankovky[i].value, bankovky[i].num);
    }
    
    return 0;
}