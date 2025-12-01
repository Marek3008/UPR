#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


char* input_process(int argc, char** argv, char** input_path, char** target_string, char** output_path, bool* ignore_case){
    bool i_provided = false;
    bool o_provided = false;
    int mandatory_params_count = 0;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-i") == 0){
            if(i_provided) return "Parameter -i provided multiple times";
            i_provided = true;
            *ignore_case = true;
        }
        else if(strcmp(argv[i], "-o") == 0){
            if(o_provided) return "Parameter -o provided multiple times";
            if((i + 1) >= argc) return "Missing output path";

            o_provided = true;
            *output_path = argv[++i];
        }
        else{
            if(mandatory_params_count == 0) *input_path = argv[i];
            else if(mandatory_params_count == 1) *target_string = argv[i];
            else return "Too many parameters provided";
    
            mandatory_params_count++;
        }
    }

    if(*input_path == NULL) return "Input path not provided";
    if(*target_string == NULL) return "Needle not provided";

    return NULL;
}

char* convert_to_lower(char* string){
    size_t string_len = strlen(string);
    char* string_copy = malloc(string_len + 1);
    strcpy(string_copy, string);

    for(int i = 0; i < string_len; i++){
        string_copy[i] = tolower(string_copy[i]);
    }
    
    return string_copy;
}

int main(int argc, char** argv){
    char* input_path = NULL;
    char* target_string = NULL;
    char* output_path = NULL;
    bool ignore_case = false;

    char* error = input_process(argc, argv, &input_path, &target_string, &output_path, &ignore_case);
    if(error != NULL){
        printf("%s\n", error);
        return 1;
    }

    FILE* file = fopen(input_path, "r");
    FILE* out = NULL;
    if(output_path != NULL) out = fopen(output_path, "wt");

    char line[101];

    while(fgets(line, sizeof(line), file)){
        char* found_substring = NULL;
        if(ignore_case){
            char* line_lower = convert_to_lower(line);
            char* target_string_lower = convert_to_lower(target_string);

            found_substring = strstr(line_lower, target_string_lower);

            free(line_lower);
            free(target_string_lower);
        }
        else found_substring = strstr(line, target_string);
        
        if(found_substring != NULL && output_path != NULL){
            fprintf(out, "%s", line);
        } 
        else if(found_substring != NULL && output_path == NULL) printf("%s", line);
    }

    fclose(file);
    if(out != NULL) fclose(out);

    return 0;
}
