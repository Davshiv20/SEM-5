#include <stdio.h>
#include <string.h>

int KeywordFunc(char* a) {
    char* arr[] = {"void", "using", "namespace", "int", "include", "<iostream>",
                   "std", "main()", "cin", "cout", "return", "float", "double",
                   "string", "endl"};
    int i;
    for (i = 0; i < 14; i++) {
        if (strcmp(arr[i], a) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int Op = 0;
    int id = 0;
    int key = 0;
    int sym = 0;
    int c = 0;
    char str[100];
    FILE* file;
    char* filename;
    filename = "./21bcb0107.txt";
    file = fopen(filename, "r");
    while (fscanf(file, "%s", str) != EOF) {
        if (strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 ||
            strcmp(str, "/") == 0 || strcmp(str, "^") == 0 || strcmp(str, "&&") == 0 ||
            strcmp(str, "||") == 0 || strcmp(str, "=") == 0 || strcmp(str, "==") == 0 ||
            strcmp(str, "&") == 0 || strcmp(str, "|") == 0 || strcmp(str, "%") == 0 ||
            strcmp(str, "++") == 0 || strcmp(str, "--") == 0 || strcmp(str, "+=") == 0 ||
            strcmp(str, "-=") == 0 || strcmp(str, "/=") == 0 || strcmp(str, "=") == 0 ||
            strcmp(str, "%=") == 0) {
            printf("%s is an operator\n", str);
            Op++;
        } else if (KeywordFunc(str)) {
            printf("%s is a keyword\n", str);
            key++;
        } else if (strcmp(str, "(") == 0 || strcmp(str, "{") == 0 ||
                   strcmp(str, "[") == 0 || strcmp(str, ")") == 0 ||
                   strcmp(str, "}") == 0 || strcmp(str, "]") == 0 ||
                   strcmp(str, "<") == 0 || strcmp(str, ">") == 0 ||
                   strcmp(str, "()") == 0 || strcmp(str, ";") == 0 ||
                   strcmp(str, "<<") == 0 || strcmp(str, ">>") == 0 ||
                   strcmp(str, ",") == 0 || strcmp(str, "#") == 0) {
            printf("%s is a symbol\n", str);
            sym++;
        } else if (strcmp(str, "\n") == 0 || strcmp(str, " ") == 0 || strcmp(str, "") == 0) {
            // Skip whitespace and empty strings
        } else if (isdigit(str[0])) {
            int x = 0;	
            if (!isdigit(str[x++])) {
                continue;
            } else {
                printf("%s is a constant\n", str);
                c++;
            }
        } else {
            printf("%s is an identifier\n", str);
            id++;
        }
    }
    printf("The number of Keywords is: %d\n", key);
    printf("The number of Symbols is: %d\n", sym);
    printf("The number of constants is: %d\n", c);
    printf("The number of identifiers is: %d\n", id);
    printf("The number of operators is: %d\n", Op);
    return 0;
}

