#include <iostream>
// #include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
using namespace std;
int isKeyword(char buffer[])
{
    char keywords[100][100] = {"endif", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto",
                           "if", "int", "long", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
                           "while", "include", "main()"};
    int flag = 0;
    for (int i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i],buffer)==0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}
int isNumber(char* str) //check if the given substring is a number or not
{
    int i, len = strlen(str),numOfDecimal = 0;
    if (len == 0)
    {
        return 1;
    }
    for (i = 0 ; i < len ; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return 1;
        } else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            {
                return 1;
            }
    }
    return 0;
}

int main()
{
    char buffer[100];
    char str, words[100];
    string op = "+-=/%><", delimiter = "{}()[],.;:'", comment = "/ */ //";
    // string identifier;
    // string deli;
    // string constants;
    // vector<char>Keywords;
    // string operators;
    ifstream fin("sample_file_21bct0157.txt");
    int j = 0;
    if (!fin.is_open())
    {
        cout << "Having trouble in opening the file"
             << "\n";
        exit(0);
    }
    while (!fin.eof())
    {
        str = fin.get();
        if (isalnum(str))
        {
            words[j++] = str;
        }
        else if ((str == ' ' || str == '\n') && (j != 0))
        {
            words[j] = '\0';
            j = 0;
            if (isKeyword(words) == 1)
            {
                cout << words << " is keyword\n";
            }
            else if (isNumber(words) == 0){
                cout << words << " is constant\n";
            }
            else{
                cout << words << " is an identifier\n";
            }
        }

        for (int i = 0; i < 11; ++i)
        {
            if (str == delimiter[i])
                cout << str << " is delimiter"
                     << "\n";
        }
        for (int i = 0; i < 10; ++i)
        {
            if (str == op[i])
                cout << str << " is an operator"
                     << "\n";
        }
    }
    fin.close();
    return 0;
}