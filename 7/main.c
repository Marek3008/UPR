#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int index;
    char* name;
    float value_start;
    float value_end;
    int trades_num;
} Stock;

int digit_count(int number){
    int len = 0;

    while(number != 0){
        number /= 10;
        len++;
    }

    return len;
}

Stock parse_data(char* input){
    Stock stock;
    char* token;

    if(input[strlen(input) - 1] == '\n') input[strlen(input) - 1] = '\0';

    token = strtok(input, ",");
    if(token != NULL) stock.index = atoi(token);

    token = strtok(NULL, ",");
    if(token != NULL){
        stock.name = malloc(strlen(token) + 1);
        strcpy(stock.name, token);
    }

    token = strtok(NULL, ",");
    if(token != NULL) stock.value_start = (float)atof(token);

    token = strtok(NULL, ",");
    if(token != NULL) stock.value_end = (float)atof(token);

    token = strtok(NULL, ",");
    if(token != NULL) stock.trades_num = atoi(token);

    return stock;
}

void stock_print(Stock stock){
    printf("Index: %d\n", stock.index);
    printf("Name: %s\n", stock.name);
    printf("Value at start of the day: %.2f\n", stock.value_start);
    printf("Value at start of the day: %.2f\n", stock.value_end);
    printf("Number of trades: %d\n", stock.trades_num);
}
Stock* find_stock_with_highest_trades(Stock* stocks, char* target_stock, int count){
    Stock* max_stock = NULL;

    for(int i = 0; i < count; i++){
        if(strcmp(stocks[i].name, target_stock) == 0){
            if(max_stock == NULL || stocks[i].trades_num > max_stock->trades_num){
                max_stock = &stocks[i];
            }
        }
    }

    return max_stock;
}
char* int_format(int number){
    char buffer[20];
    sprintf(buffer, "%d", number);

    size_t len = strlen(buffer);
    size_t num_underscores = (len - 1) / 3;
    size_t final_len = len + num_underscores + 1;

    char* result = malloc(final_len);

    int i = len - 1;
    int j = final_len - 2;
    result[final_len - 1] = '\0';

    int count = 0;
    while(i >= 0){
        result[j--] = buffer[i--];
        count++;
        if(count == 3 && i >= 0){
            result[j--] = '_';
            count = 0;
        }
    }

    return result;
}

void highest_trades_stock_html(Stock* highest_trades_stock){
    char* volume_formatted = int_format(highest_trades_stock->trades_num);

    printf("<h1>%s: highest volume</h1>\n"
           "<div>Day: %d</div>\n"
           "<div>Start price: %.2f</div>\n"
           "<div>End price: %.2f</div>\n"
           "<div>Volume: %s</div>\n",
           highest_trades_stock->name, highest_trades_stock->index, highest_trades_stock->value_start, highest_trades_stock->value_end, volume_formatted);

    free(volume_formatted);
}

void output_html(Stock* stocks, Stock* highest_trades_stock, int count, char* target_stock_name){
    printf("<html>\n"
           "<body>\n");

    printf("<div>\n");
    if(highest_trades_stock != NULL) highest_trades_stock_html(highest_trades_stock);
    else printf("Ticker %s was not found\n", target_stock_name);
    printf("</div>\n");

    printf("<table>\n"
           "<thead>\n"
           "<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n"
           "</thead>\n"
           "<tbody>\n");

    for(int i = count - 1; i >= 0; i--){
        char* volume_str = int_format(stocks[i].trades_num);
        bool print_bold = false;

        if(highest_trades_stock){
            if(strcmp(stocks[i].name, highest_trades_stock->name) == 0) print_bold = true;
        }

        printf("<tr>\n");

        printf("\t<td>");
        if(print_bold) printf("<b>");
        printf("%d", stocks[i].index);
        if(print_bold) printf("</b>");
        printf("</td>\n");

        printf("\t<td>");
        if(print_bold) printf("<b>");
        printf("%s", stocks[i].name);
        if(print_bold) printf("</b>");
        printf("</td>\n");

        printf("\t<td>");
        if(print_bold) printf("<b>");
        printf("%.2f", stocks[i].value_start);
        if(print_bold) printf("</b>");
        printf("</td>\n");

        printf("\t<td>");
        if(print_bold) printf("<b>");
        printf("%.2f", stocks[i].value_end);
        if(print_bold) printf("</b>");
        printf("</td>\n");

        printf("\t<td>");
        if(print_bold) printf("<b>");
        printf("%.2f", stocks[i].value_end - stocks[i].value_start);
        if(print_bold) printf("</b>");
        printf("</td>\n");

        printf("\t<td>");
        if(print_bold) printf("<b>");
        printf("%s", volume_str);
        if(print_bold) printf("</b>");
        printf("</td>\n");

        printf("</tr>\n");

        free(volume_str);
    }

    printf("</tbody>\n"
           "</table>\n"
           "</body>\n"
           "</html>\n");
}

int main(int argc, char** argv){
    if(argc != 3){
        printf("Wrong parameters\n");
        
        return 1;
    }

    char* target_stock_name = malloc(strlen(argv[1]) + 1);
    strcpy(target_stock_name, argv[1]);
    int inputs_num = atoi(argv[2]);

    Stock* stocks = malloc(sizeof(Stock) * inputs_num);

    for(int i = 0; i < inputs_num; i++){
        char input[100];
        fgets(input, sizeof(input), stdin);

        stocks[i] = parse_data(input);
    }

    Stock* max_stock = find_stock_with_highest_trades(stocks, target_stock_name, inputs_num);
    output_html(stocks, max_stock, inputs_num, target_stock_name);
    
    for(int i = 0; i < inputs_num; i++){
        free(stocks[i].name);
    }
    free(target_stock_name);
    free(stocks);

    return 0;
}