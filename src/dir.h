#ifndef _DIR_H
#define _DIR_H

#include "structs.h"

TEntry *allocEntry(int path_size);
TEntry *allocEntryArray(int array_size, int path_size);


TDirectory *allocDirectory(int entry_num, int path_size, char *path);

void setEntries(TDirectory *dir);
int getDirSize(const char *dir_path);

#endif
