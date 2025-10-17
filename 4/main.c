#include <stdio.h>

#define SIZE 1000

struct Pair{
    int value;
    int number;
};

int inputs_load(char* mode, int* n, int* m, int numbers[]){
    
    scanf("%c", mode);
    
    if(*mode != 'h' && *mode != 'v'){
        return 1;
    }

    scanf("%d %d", n, m);

    for(int i = 0; i < *n; i++){
        scanf("%d", &numbers[i]);
    }

    return 0;
}

int digits_count(int num){
    
    int count = 0;

    if (num == 0){
        return 1;
    }

    if (num < 0)
        num = -num;

    while (num > 0) {
        num /= 10;
        count++;
    }

    return count;
}

void histogram_print(struct Pair histogram[], int* invalid){
    
    for(int i = 0; i < 9; i++){
        if(digits_count(histogram[i].value) < digits_count(histogram[8].value)){
            printf(" ");
        }

        printf("%d", histogram[i].value);

        if(histogram[i].number > 0){
            printf(" ");
            for(int j = 1; j <= histogram[i].number; j++){
                printf("#");
            }
        }

        printf("\n");
    }

    if(*invalid > 0){
        printf("invalid: ");

        for(int i = 0; i < *invalid; i++){
            printf("#");
        }
        printf("\n");
    }
}

void histogram_fill(struct Pair histogram[], int n, int m, int numbers[], int* invalid){

    *invalid = 0;
    int range = m + 8;

    for (int i = 0; i < 9; i++) {
        histogram[i].value = i + m;
        histogram[i].number = 0;
    }

    for (int j = 0; j < n; j++) {
        if (numbers[j] < m || numbers[j] > range) {
            (*invalid)++;
        } 
        else {
            histogram[numbers[j] - m].number++;
        }
    }
}

int main(){
    int n, m;
    char mode;
    int numbers[SIZE];
    struct Pair histogram[SIZE];
    int invalid;

    if(inputs_load(&mode, &n, &m, numbers) == 1){
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    histogram_fill(histogram, n, m, numbers, &invalid);
    histogram_print(histogram, &invalid);

    return 0;
}