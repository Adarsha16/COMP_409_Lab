#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char lexeme[100];
    char tokenType[20];
} Token;

Token tokens[1000];
int tokenCount = 0;

// Function to check if a string is a keyword
int isKeyword(char buffer[])
{
    char keywords[10][10] = {"int", "float", "char", "if", "else", "while", "return", "void", "for", "do"};
    for (int i = 0; i < 10; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a delimiter
int isDelimiter(char ch)
{
    char delimiters[] = "{;(),}";
    for (int i = 0; i < strlen(delimiters); ++i)
    {
        if (ch == delimiters[i])
        {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch)
{
    char operators[] = "+-*/=<>!";
    for (int i = 0; i < strlen(operators); ++i)
    {
        if (ch == operators[i])
        {
            return 1;
        }
    }
    return 0;
}

// Helper to add tokens to the array
void addToken(const char *lex, const char *type)
{
    strcpy(tokens[tokenCount].lexeme, lex);
    strcpy(tokens[tokenCount].tokenType, type);
    tokenCount++;
}

int main()
{
    FILE *fp;
    char ch, buffer[100];
    int j = 0;

    // file operation to open input file
    fp = fopen("file.txt", "r");
    if (fp == NULL)
    {
        printf("Error: Could not open File.txt\n");
        return 1;
    }

    // reading characters until eof
    while ((ch = fgetc(fp)) != EOF)
    {

        // Ignore whitespace and quotes
        if (isspace(ch))
        {
            continue;
        }

        if (ch == '"')
        {
            continue;
        }

        // Check for Delimiters
        if (isDelimiter(ch))
        {
            buffer[0] = ch;
            buffer[1] = '\0';
            addToken(buffer, "DELIMITER");
            continue;
        }

        // Check for Operators
        if (isOperator(ch))
        {
            buffer[0] = ch;
            buffer[1] = '\0';

            // Check for double operators
            char next_ch = fgetc(fp);
            if (isOperator(next_ch))
            {
                buffer[1] = next_ch;
                buffer[2] = '\0';
                addToken(buffer, "OPERATOR");
            }
            else
            {
                addToken(buffer, "OPERATOR");
                // Put the non-operator character back into the stream
                ungetc(next_ch, fp);
            }
            continue;
        }

        // Check for Keywords and Identifiers
        if (isalpha(ch) || ch == '_')
        {
            j = 0;
            buffer[j++] = ch;
            ch = fgetc(fp);

            while (isalnum(ch) || ch == '_')
            {
                buffer[j++] = ch;
                ch = fgetc(fp);
            }
            buffer[j] = '\0';
            ungetc(ch, fp); // Put the last read character back

            if (isKeyword(buffer))
            {
                addToken(buffer, "KEYWORD");
            }
            else
            {
                addToken(buffer, "IDENTIFIER");
            }
            continue;
        }

        // Check for Numbers
        if (isdigit(ch))
        {
            j = 0;
            buffer[j++] = ch;
            ch = fgetc(fp);

            while (isdigit(ch))
            {
                buffer[j++] = ch;
                ch = fgetc(fp);
            }
            buffer[j] = '\0';
            ungetc(ch, fp); // Put the last read character back

            addToken(buffer, "NUMBER");
            continue;
        }
    }

    fclose(fp);

    // Display the stored tokens
    printf("Tokens:\n");
    printf("| %-12s | %-15s |\n", "LEXEME", "TOKEN");
    printf("\n");
    for (int i = 0; i < tokenCount; i++)
    {
        printf("| %-12s | %-15s |\n", tokens[i].lexeme, tokens[i].tokenType);
    }
    printf("-----------------------------------\n");

    return 0;
}