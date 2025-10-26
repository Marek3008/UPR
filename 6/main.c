#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void line_normalize(char* line){
    int i = 0;
    while(line[i] == ' ') i++;

    //medzery na zaciatku
    for(int j = 0; j < i; j++){
        for(int k = 0; k < strlen(line); k++){
            line[k] = line[k + 1];
        }
    }

    //medzery na konci
    i = strlen(line) - 1;
    while(line[i] == ' ' || line[i] == '\n') i--;
    line[i + 1] = '\0';

    //medzery medzi slovami
    int line_len = strlen(line);
    for(int j = 0; j < line_len; j++){
        if(line[j] == ' ' && line[j + 1] == ' '){
            for(int k = j; k < line_len; k++){
                line[k] = line[k + 1];
            }
            line_len = strlen(line);
            j--;
        }
    }
}

char** line_split(char* line, int* words_num){
    char* temp = strdup(line);
    char* splitter = strtok(temp, " ");
    char** words = malloc(50 * sizeof(char*));
    *words_num = 0;
    
    while(splitter != NULL){
        words[*words_num] = strdup(splitter);
        (*words_num)++;
        splitter = strtok(NULL, " ");
    }

    words[*words_num] = NULL;
    free(temp);
    return words;
}

bool is_upper(char c){
    if(c >= 'A' && c <= 'Z') return 1;

    return 0;
}

bool is_lower(char c){
    if(c >= 'a' && c <= 'z') return 1;

    return 0;
}

void words_normalize(char** words, int words_num){
    for(int i = 0; i < words_num; i++){
        int word_len = strlen(words[i]);
        bool has_upper = 0;

        for(int j = 0; j < word_len; j++){
            if(is_upper(words[i][j])){
                has_upper = 1;
            }
        }

        if(has_upper){
            if(is_lower(words[i][0])) words[i][0] -= 32;
            for(int j = 1; j < word_len; j++){
                if(is_upper(words[i][j])) words[i][j] += 32;
            }
        }
        else{
            for(int j = 0; j < word_len; j++){
                words[i][j] -= 32;
            }
        }

        for(int j = 0; j < word_len; j++){
            if(words[i][j] == words[i][j + 1]){
                for(int k = j; k < word_len; k++){
                    words[i][k] = words[i][k + 1];
                }
                word_len--;
                j--;
            }
        }
    }
}

int main(){
    int num, words_num;
    char line[51];
    char** words;

    scanf("%d", &num);
    getchar();
    
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';


    printf("Pred:  %p: %s\n", line, line);
    printf("Dlzka: %d\n\n", strlen(line));

    line_normalize(line);
    words = line_split(line, &words_num);
    words_normalize(words, words_num);

    printf("Po:    %p: %s\n", line, line);
    printf("Dlzka: %d\n", strlen(line));

    for(int i = 0; i < words_num; i++){
        printf("%s\n", words[i]);
    }
    


    for(int i = 0; words[i] != NULL; i++){
        free(words[i]);
    }
    free(words);

    return 0;
}