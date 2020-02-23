#include "dir.h"

TEntry *allocEntry(int path_size)
{
    TEntry *entry = calloc(1, sizeof(TEntry));
    
    if(!entry)
    {
        fprintf(stderr ,"Failed to alloc entry!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
    
    entry->_path = allocString(path_size);
    entry->_fd = 0;

    return entry;
}


TEntry *allocEntryArray(int array_size, int path_size)
{
    TEntry *entry_array = calloc(array_size, sizeof(TEntry));
    
    if(!entry_array)
    {
        fprintf(stderr ,"Failed to alloc entry array!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < array_size; i++)
    {
        entry_array[i]._path = allocString(path_size);
    }
    
    return entry_array;
}

TDirectory *allocDirectory(int entry_num, int path_size, char *path)
{
    TDirectory *dir = calloc(1, sizeof(TDirectory));
    
    if(!dir)
    {
        fprintf(stderr ,"Failed to alloc dir!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
    
    dir->_entries = allocEntryArray(entry_num, path_size);
    dir->_entry_num = entry_num;
    dir->_dir_path = allocString(path_size);
    strcat(dir->_dir_path, path);
    
    
    return dir;
}

int getDirSize(const char *dir_path)
{
    int entry_num = 0;
    
    struct dirent *dir_entry;
       
    DIR *input_dir = opendir(dir_path);
       
    if(!input_dir)
    {
        fprintf(stderr, "Failed to open directory!");
        exit(EXIT_FAILURE);
    }
       
    while((dir_entry = readdir(input_dir)))
    {
        if(strstr(dir_entry->d_name, ".txt"))
        {
            entry_num++;
        }
    }
    
    closedir(input_dir);
    
    return entry_num;
}

void setEntries(TDirectory *dir)
{
    struct dirent *dir_entry;
    
    DIR *input_dir = opendir(dir->_dir_path);
    
    if(!input_dir)
    {
        fprintf(stderr, "Failed to open directory!");
        exit(EXIT_FAILURE);
    }
    
    int index = 0;
    
    while((dir_entry = readdir(input_dir)) != NULL)
    {
        if(strstr(dir_entry->d_name, ".txt") != NULL)
        {
            snprintf(dir->_entries[index]._path, strlen(dir->_dir_path) + strlen(dir_entry->d_name) + 2, "%s/%s", dir->_dir_path, dir_entry->d_name);
            
            dir->_entries[index]._fd = index;
            
            index++;
        }
    }
}
