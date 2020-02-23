#ifndef _QUERRY_H

#define _QUERRY_H

#include "structs.h"
#define TOKEN_SIZE 100


TToken *allocQuerry(int querry_size, int file_num);
void handleOperatorFields(TToken *querry, int querry_size);
void handleFileArray(TToken *querry, int querry_size, TDirectory *dir);
void setQuerry(char *querry_string, TToken *querry, int querry_size, TDirectory *dir);


int *allocFileArray(int array_size);
int getTokenNumber(char *querry_string);


#endif
