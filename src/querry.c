#include "querry.h"

TToken *allocQuerry(int querry_size, int file_num)
{
    TToken *querry = calloc(querry_size, sizeof(TToken));
    
    if(!querry)
    {
        fprintf(stderr, "Failed to alloc querry!\nExiting...\n!");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < querry_size; i++)
    {
        querry[i]._file_array = allocFileArray(file_num);
        querry[i]._file_num = file_num;
        querry[i]._string = allocString(TOKEN_SIZE);
        querry[i]._is_operator = 0;
        querry[i]._precedence = 0;
    }
    
    return querry;
}
int *allocFileArray(int array_size)
{
    int *file_array = calloc(array_size, sizeof(int));
    
    if(!file_array)
    {
        fprintf(stderr, "Failed to alloc file array!\nExiting...\n!");
        exit(EXIT_FAILURE);
    }
    
    return file_array;
}

void handleOperatorFields(TToken *querry, int querry_size)
{
    for(int i = 0; i < querry_size; i++)
    {
        if(strcmp(querry[i]._string, "&&") == 0)
        {
            querry[i]._is_operator = 1;
            querry[i]._precedence = 2;
        }
        else
        {
            if(strcmp(querry[i]._string, "||") == 0)
            {
                querry[i]._is_operator = 1;
                querry[i]._precedence = 1;
            }
            else
            {
                if(strcmp(querry[i]._string, "!") == 0)
                {
                    querry[i]._is_operator = 1;
                    querry[i]._precedence = 3;
                }
                else
                {
                    if(strcmp(querry[i]._string, ")") == 0 || strcmp(querry[i]._string, "(") == 0)
                    {
                        querry[i]._is_operator = 1;
                        querry[i]._precedence = 0;
                    }
                    else
                    {
                        querry[i]._is_operator = 0;
                    }
                }
            }
        }
    }
}

void setQuerry(char *querry_string, TToken *querry, int querry_size, TDirectory *dir)
{
    char *c_ptr = strtok(querry_string, " ");
    
    for(int i = 0; c_ptr != NULL; i++)
    {
        strcat(querry[i]._string, c_ptr);
        
        c_ptr = strtok(NULL, " ");
    }
    
    handleOperatorFields(querry, querry_size);
    handleFileArray(querry, querry_size, dir);
}

int getTokenNumber(char *querry_string)
{
    int token_num = 0;
    
    char *c_ptr = strtok(querry_string, " ");
    
    for(int i = 0; c_ptr != NULL; i++)
    {
        token_num++;
        
        c_ptr = strtok(NULL, " ");
    }
    
    return token_num;
}

void handleFileArray(TToken *querry, int querry_size, TDirectory *dir)
{
    for(int i = 0; i < querry_size; i++)
    {
        for(int j = 0; j < querry[i]._file_num; j++)
        {
            if(querry[i]._is_operator == 0)
            {
                querry[i]._file_array[j] = checkForWord(querry[i]._string, dir->_entries[j]._path);
            }
        }
    }
}
