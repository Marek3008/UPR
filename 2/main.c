#include <stdio.h>


int image, x, y;

void rectangle(){
    for(int i = 1; i <= y; i++){
        for(int j = 1; j <= x; j++){
            printf("x");
        }
        printf("\n");
    }
}

void rectangleHollow(){
    for(int i = 1; i <= y; i++){
        for(int j = 1; j <= x; j++){
            if((i > 1 && i < y) && (j > 1 && j < x)){
                printf(" ");
            }
            else{
                printf("x");
            }
        }
        printf("\n");
    } 
}

void rectangleNumbersRow(){
    int num = 0;

    for(int i = 1; i <= y; i++){
        for(int j = 1; j <= x; j++){
            if((i > 1 && i < y) && (j > 1 && j < x)){
                printf("%d", num);
                num++;

                if(num > 9){
                    num = 0;
                }
            }
            else{
                printf("x");
            }
        }
        printf("\n");
    } 
}

void diagonalDown(){
    for(int i = 1; i <= x; i++){
        for(int j = 1; j <= x; j++){
            if(i == j){
                printf("x");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");    
    }
}

void diagonalUp(){
    for(int i = 1; i <= x; i++){
        for(int j = 1; j <= x; j++){
            if((i + j) == (x + 1)){
                printf("x");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");    
    }
}

void triangle(){
    int width = x + (x - 1);
    int offset = 0;

    for(int i = 1; i <= x; i++){
        for(int j = 1; j <= width; j++){
            if(i != x){
                if(j == (x + offset) || j == (x - offset)){
                    printf("x");
                }
                else{
                    printf(" ");
                }
            }
            else{
                printf("x");
            }
        }
        printf("\n");
        offset++;
    }
}

void letterT(){
    int midpoint = (x + 1) / 2;

    for(int i = 1; i <= y; i++){
        for(int j = 1; j <= x; j++){
            if(i == 1){
                printf("x");
            }
            else{
                if(j == midpoint){
                    printf("x");
                }
                else{
                    printf(" ");
                }
            }
        }
        printf("\n");    
    }
}

void letterP(){
    int midpoint = (y + 1) / 2;

    for(int i = 1; i <= y; i++){
        for(int j = 1; j <= x; j++){
            if(i == 1 || i == midpoint){
                printf("x");
            }
            else if(i > 1 && i < midpoint){
                if(j == 1 || j == x){
                    printf("x");
                }
                else{
                    printf(" ");
                }
            }
            else if(i > midpoint && j == 1){
                printf("x");
            }
        }
        printf("\n");    
    }
}

void rectangleNumbersColumn(){
    int increment = y - 2;
    int num = 0 - increment - 1;
    int value;

    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){

            value = num + (increment * j);
            
            if((i == 0 || i == (y - 1)) || (j == 0 || j == (x - 1))){
                printf("x");
            }
            else{                
                printf("%d", value % 10);
            }
        }
        printf("\n");
        num++;
    } 
}



int main(void){
    
    scanf("%d%d%d", &image, &x, &y);


    switch (image){
        case 0:
            rectangle();
            break;
        
        case 1:
            rectangleHollow();
            break;
        
        case 2:
            rectangleNumbersRow();
            break;

        case 3:
            diagonalDown();
            break;

        case 4:
            diagonalUp();
            break;

        case 5:
            triangle();
            break;

        case 6:
            letterT();
            break;

        case 7:
            letterP();
            break;

        case 9:
            rectangleNumbersColumn();
            break;

        default:
            printf("Neznamy obrazec\n");
            break;
    }

    return 0;
}