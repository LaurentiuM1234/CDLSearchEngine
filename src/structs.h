#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>

#define CONTENT_SIZE 5000
#define FOUND 1
#define NOT_FOUND 0
#define TOKENS " {}[]();:\",.'-"
#define QUERRY_SIZE 100
#define PATH_SIZE 100


#pragma pack(1)

typedef struct
{
    size_t _field_size;
    size_t _content_size;
    void *_content;
    void *_last;
}TStack;

typedef struct
{
    size_t _field_size;
    size_t _content_size;
    int _is_empty_flag;
    void *_content;
    void *_rear;
    void *_front;
    
}TQueue;

typedef struct
{
    char *_path;
    int _fd;
    
}TEntry;

typedef struct
{
    char *_dir_path;
    TEntry *_entries;
    int _entry_num;
    
}TDirectory;

typedef struct
{
    char *_string;
    int *_file_array;
    int _file_num;
    int _is_operator;
    int _precedence;
    
}TToken;


typedef struct
{
    GtkWidget *_window; 
    GtkWidget *_search_button; 
    GtkWidget *_quit_button;
    GtkTextBuffer *_output_buffer;

}TWidgets;


#pragma pack()


GtkWidget *FIRST_SEARCH_BAR;
GtkWidget *SECOND_SEARCH_BAR;

char *allocString(int string_size);
int checkForWord(char *word, char *f_path);
TQueue *getRPNForm(TToken *querry, int querry_size);
int *getExprResult(TQueue *output_queue);
char *getMatchesString(int *result_array, int array_size, TDirectory *dir);
char *taskSolver(char *querry_string, char *dir_path);
void readQuerryString(char *querry_string);
void handleGUI(void);
void on_main_window_destroy(void);
void on_quit_button_clicked(void);
void on_search_button_clicked(GtkWidget *widget, gpointer user_data);


#endif
