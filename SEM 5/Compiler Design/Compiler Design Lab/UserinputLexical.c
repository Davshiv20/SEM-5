#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token types
typedef enum {
    TOK_IDENTIFIER,
    TOK_NUMBER,
    TOK_OPERATOR,
    TOK_DELIMITER,
    TOK_KEYWORD,
    TOK_UNKNOWN
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[50];
} Token;

// Function to check if a character is a delimiter
int isDelimiter(char ch) {
    char delimiters[] = " \t\n,;(){}[]";
    int i;
    for ( i = 0; i < strlen(delimiters); i++) {
        if (ch == delimiters[i])
            return 1;
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    char operators[] = "+-*/%=";
    int i;
    for (i = 0; i < strlen(operators); i++) {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}

// Function to check if a string is a keyword
int isKeyword(char* str) {
    char keywords[][10] = {"int", "float", "char", "if", "else", "for", "while", "do", "return"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    int i;
    for (i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to tokenize the input string
void tokenize(char* input) {
    int length = strlen(input);
    int i = 0;

    while (i < length) {
        // Skip whitespace
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // Handle identifiers and keywords
        if (isalpha(input[i])) {
            int j = 0;
            char identifier[50];

            while (isalnum(input[i])) {
                identifier[j] = input[i];
                i++;
                j++;
            }
            identifier[j] = '\0';

            Token token;
            strcpy(token.value, identifier);

            if (isKeyword(identifier)) {
                token.type = TOK_KEYWORD;
                printf("Keyword: %s\n", token.value);
            } else {
                token.type = TOK_IDENTIFIER;
                printf("Identifier: %s\n", token.value);
            }
            continue;
        }

        // Handle numbers
        if (isdigit(input[i])) {
            int j = 0;
            char number[50];

            while (isdigit(input[i])) {
                number[j] = input[i];
                i++;
                j++;
            }
            number[j] = '\0';

            Token token;
            strcpy(token.value, number);
            token.type = TOK_NUMBER;

            printf("Number: %s\n", token.value);
            continue;
        }

        // Handle operators
        if (isOperator(input[i])) {
            Token token;
            token.value[0] = input[i];
            token.value[1] = '\0';
            token.type = TOK_OPERATOR;

            printf("Operator: %s\n", token.value);
            i++;
            continue;
        }

        // Handle delimiters
        if (isDelimiter(input[i])) {
            Token token;
            token.value[0] = input[i];
            token.value[1] = '\0';
            token.type = TOK_DELIMITER;

            printf("Delimiter: %s\n", token.value);
            i++;
            continue;
        }

        // Handle unknown characters
		Token token;
		token.value[0] = input[i];
		token.value[1] = '\0';
		token.type = TOK_UNKNOWN;
	    printf("Unknown: %s\n", token.value);
	    i++;
}
}

// Main function
int main() {
	char input[100];
	printf("Enter input string: ");
	fgets(input, sizeof(input), stdin);

	// Remove trailing newline character
	input[strcspn(input, "\n")] = '\0';
	
	// Tokenize the input string
	tokenize(input);

	return 0;
}

