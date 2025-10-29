#include <stdio.h>
#include <stdbool.h>


struct LineStatistics{
    int lowercase;
    int uppercase;
    int spaces_num;
};

bool is_upper(char c){if(c >= 'A' && c <= 'Z') return true; return false;}
bool is_lower(char c){if(c >= 'a' && c <= 'z') return true; return false;}

int str_len(char* string){
    int i = 0;

    while(string[i] != '\0'){
        i++;
    }
    return i;
}

int str_to_int(char* string){
    int value = 0;
    for(int i = 0; string[i] != '\0'; i++){
        value = value * 10 + (string[i] - '0');
    }
    return value;
}

void line_normalize(char* line){
    int len = str_len(line);

    // medzery ba zaciatku
    int start = 0;
    while(line[start] == ' ') start++;

    if(start > 0){
        for(int i = 0; i <= len - start; i++){
            line[i] = line[i + start];
        }
        len -= start;
    }

    // medzery na konci
    while(len > 0 && line[len - 1] == ' ') {
        line[len - 1] = '\0';
        len--;
    }

    // medzery medzi slovami
    for(int i = 0; i < len - 1; i++){
        if(line[i] == ' ' && line[i + 1] == ' '){
            for(int j = i; j < len; j++){
                line[j] = line[j + 1];
            }
            len--;
            i--;
        }
    }
}

void words_normalize(char* line) {
    int start = 0;
    int end = 0;
    int len = str_len(line);
    
    while(start < len){
        bool has_upper = false;
        while(line[end] != ' ' && line[end] !=  '\0') end++;

        //hladanie velkeho pismena
        for(int i = start; i < end; i++){
            if(is_upper(line[i])) has_upper = true;
        }

        if(has_upper){
            //prve velke ostatne male
            if(is_lower(line[start])) line[start] -= 32;
            for(int j = start + 1; j < end; j++) {
                if(is_upper(line[j])) line[j] += 32;
            }
        }

        //vsetky velke
        else{
            for(int j = start; j < end; j++) {
                if(is_lower(line[j])) line[j] -= 32;
            }
        }

        //mazanie duplikatov
        for(int i = start; i < end; i++){
            if(line[i] == line[i + 1]){
                for(int j = i; j < len; j++){
                    line[j] = line[j + 1];
                }
                len--;
                end--;
                i--;
            }
        }

        start = end + 1;
        end = start;
    }
}

struct LineStatistics* line_stat_process(char* line, struct LineStatistics* stats){
    stats->lowercase = stats->uppercase = stats->spaces_num = 0;
    int len = str_len(line);
    for(int i = 0; i < len; i++){
        if(line[i] == ' ') stats->spaces_num++;
        else if(is_upper(line[i])) stats->uppercase++;
        else if(is_lower(line[i])) stats->lowercase++;
    }
    return stats;
}

void stats_print(struct LineStatistics stats_before, struct LineStatistics stats_after){
    printf("lowercase: %d -> %d\n", stats_before.lowercase, stats_after.lowercase);
    printf("uppercase: %d -> %d\n", stats_before.uppercase, stats_after.uppercase);
    printf("spaces: %d -> %d\n", stats_before.spaces_num, stats_after.spaces_num);
}

int main(){
    int num;
    char c_num[51];
    
    fgets(c_num, sizeof(c_num), stdin);

    //odstranenie new line z cisla
    c_num[str_len(c_num) - 1] = '\0';
    num = str_to_int(c_num);
    
    for(int i = 0; i < num; i++){
        char line[51];

        fgets(line, sizeof(line), stdin);
        struct LineStatistics before, after;
    
        //odstrani new line zo stringu
        if(line[str_len(line) - 1] == '\n') line[str_len(line) - 1] = '\0';

        line_stat_process(line, &before);
        
        line_normalize(line);
        words_normalize(line);

        printf("%s\n", line);
        line_stat_process(line, &after);
        stats_print(before, after);
        if(i != num - 1) printf("\n");
    }    

    return 0;
}