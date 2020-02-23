#include "queue.h"
#include "stack.h"
#include "array_op.h"
#include "dir.h"
#include "querry.h"

char *allocString(int string_size)
{
    char *string = calloc(string_size, sizeof(char));
    
    if(!string)
    {
        fprintf(stderr ,"Failed to alloc string!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
    
    return string;
}

int checkForWord(char *word, char *f_path)
{
    FILE *input_file = fopen(f_path, "rt");
    
    char *input_word_copy = calloc(strlen(word) + 1, sizeof(char));
    
    strcat(input_word_copy, word);
    
    if(!input_file)
    {
        fprintf(stderr, "Failed to open file!");
        exit(EXIT_FAILURE);
    }
    
    char *file_content = allocString(CONTENT_SIZE);
    
    int index = 0;
    
    while(fscanf(input_file, "%c", &file_content[index]) != EOF)
    {
        index++;
    }
    
    for(int i = 0; i < index; i++)
    {
        file_content[i] = tolower(file_content[i]);
    }
    
    for(int i = 0; i < strlen(word); i++)
    {
        input_word_copy[i] = tolower(input_word_copy[i]);
    }
   
    
    fclose(input_file);
    
    char *c_ptr = strtok(file_content, TOKENS);
    
    while(c_ptr != NULL)
    {
        if(strcmp(c_ptr, input_word_copy) == 0)
        {
            return FOUND;
        }
        
        c_ptr = strtok(NULL, TOKENS);
    }
    
        return NOT_FOUND;
    
}

TQueue *getRPNForm(TToken *querry, int querry_size)
{
    TQueue *output_queue = createQueue(sizeof(TToken), querry_size);
    TStack *operator_stack = createStack(sizeof(TToken), querry_size);
    
    for(int i = 0; i < querry_size; i++)
    {
        if(querry[i]._is_operator == 0)
        {
            pushQueue(querry + i, output_queue);
        }
        else
        {
            if(querry[i]._precedence == 0)
            {
                 if(strcmp(querry[i]._string, "(") == 0)
                 {
                     pushStack(querry + i, operator_stack);
                 }
                else
                {
                    if(strcmp(querry[i]._string, ")") == 0)
                    {
                        while(strcmp((*(TToken *)(operator_stack->_last - operator_stack->_field_size))._string, "(") != 0)
                        {
                            pushQueue((operator_stack->_last - operator_stack->_field_size), output_queue);
                            popStack(operator_stack);
                        }
                        popStack(operator_stack);
                    }
                    else
                    {
                        if((*(TToken *)(operator_stack->_last - operator_stack->_field_size))._precedence >= querry[i]._precedence)
                        {
                            pushQueue((operator_stack->_last - operator_stack->_field_size), output_queue);
                            popStack(operator_stack);
                        }
                        else
                        {
                            pushStack(querry + i, operator_stack);
                        }
                    }
                }
            }
            else
            {
                if(STACK_EMPTY(operator_stack))
                {
                    pushStack(querry + i, operator_stack);
                }
                else
                {
                    if((*(TToken *)(operator_stack->_last - operator_stack->_field_size))._precedence >= querry[i]._precedence)
                    {
                        pushQueue((operator_stack->_last - operator_stack->_field_size), output_queue);
                        popStack(operator_stack);
                        pushStack(querry + i, operator_stack);
                    }
                    else
                    {
                        pushStack(querry + i, operator_stack);
                    }
                }
            }
        }
    }
    
    while(!STACK_EMPTY(operator_stack))
    {
        pushQueue(operator_stack->_last - operator_stack->_field_size, output_queue);
        popStack(operator_stack);
    }
    
    return output_queue;
}


int *getExprResult(TQueue *output_queue)
{
    int file_num = (*(TToken *)(output_queue->_content))._file_num;
    
    int *result_array = calloc(file_num, sizeof(int));
    
    int *operand1, *operand2;
    
    if(!result_array)
    {
        fprintf(stderr, "Failed to alloc result array !");
        exit(EXIT_FAILURE);
    }
    
    TStack *aux_stack = createStack(file_num * sizeof(int), file_num);
    
    while(!QUEUE_EMPTY(output_queue))
    {
       if((*(TToken *)(output_queue->_rear))._is_operator == 0)
       {
           pushStack((*(TToken *)(output_queue->_rear))._file_array, aux_stack);
           popQueue(output_queue);
       }
       else
       {
           if((*(TToken *)(output_queue->_rear))._precedence == 3)
           {
               operand1 = (int *)(aux_stack->_last - aux_stack->_field_size);
               popStack(aux_stack);
               result_array = arrayNOT(operand1, file_num);
               pushStack(result_array, aux_stack);
               popQueue(output_queue);
           }
           else
           {
               if((*(TToken *)(output_queue->_rear))._precedence == 2)
               {
                   operand1 = (int *)(aux_stack->_last - aux_stack->_field_size);
                   popStack(aux_stack);
                   operand2 = (int *)(aux_stack->_last - aux_stack->_field_size);
                   popStack(aux_stack);
                   result_array = arrayAND(operand1, operand2, file_num);
                   pushStack(result_array, aux_stack);
                   popQueue(output_queue);
               }
               else
               {
                   if((*(TToken *)(output_queue->_rear))._precedence == 1)
                   {
                       operand1 = (int *)(aux_stack->_last - aux_stack->_field_size);
                       popStack(aux_stack);
                       operand2 = (int *)(aux_stack->_last - aux_stack->_field_size);
                       popStack(aux_stack);
                       result_array = arrayOR(operand1, operand2, file_num);
                       pushStack(result_array, aux_stack);
                       popQueue(output_queue);
                   }
               }
           }
       }
    }
    
    return (int*)(aux_stack->_last - aux_stack->_field_size);
}

char *getMatchesString(int *result_array, int array_size, TDirectory *dir)
{
    char *matches_string = allocString(1000);
    snprintf(matches_string, 1000, "Search results:\n");
    
    for(int i = 0; i < array_size; i++)
    {
        if(result_array[i] != 0)
        {
            strcat(matches_string, dir->_entries[i]._path);
            strcat(matches_string, "\n");
        }
    }
    return matches_string;
}

char *taskSolver(char *querry_string, char *dir_path)
{
    int entry_num = getDirSize(dir_path);

	if(entry_num == 0)
	{
		fprintf(stderr, "No .txt files detected or dir is empty!\n");
		exit(EXIT_FAILURE);
	}

    TDirectory *dir = allocDirectory(entry_num, PATH_SIZE, dir_path);
    setEntries(dir);
    
    char *querry_string_copy = calloc(QUERRY_SIZE, sizeof(char));
    snprintf(querry_string_copy, QUERRY_SIZE, "%s", querry_string);
    int querry_size = getTokenNumber(querry_string_copy);

	if(querry_size == 0)
	{
		fprintf(stderr, "Querry cannot be empty!\n");
		exit(EXIT_FAILURE);
	}
	
	TToken *querry = allocQuerry(querry_size, entry_num);
   	setQuerry(querry_string, querry, querry_size, dir);
    
    TQueue *rpn_queue;
    rpn_queue = getRPNForm(querry, querry_size);
    	
    int *result;
    result = getExprResult(rpn_queue);
	return getMatchesString(result, entry_num, dir);
	
}

void readQuerryString(char *querry_string)
{
    char ch;
    
    scanf("%c", &ch);
    
    for(int i = 0; ch != '\n'; i++)
    {
        querry_string[i] = ch;
        
        scanf("%c", &ch);
    }
}

void handleGUI(void)
{
    GtkBuilder *builder = gtk_builder_new();
    TWidgets *app_widgets = g_slice_new(TWidgets);

    gtk_builder_add_from_file(builder, "GUI.glade", NULL);
    app_widgets->_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    app_widgets->_quit_button = GTK_WIDGET(gtk_builder_get_object(builder, "quit_button"));
    app_widgets->_search_button = GTK_WIDGET(gtk_builder_get_object(builder, "search_button"));
    app_widgets->_output_buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "output_buffer"));
   FIRST_SEARCH_BAR = GTK_WIDGET(gtk_builder_get_object(builder, "first_search_bar"));
   SECOND_SEARCH_BAR = GTK_WIDGET(gtk_builder_get_object(builder, "second_search_bar"));
    
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(app_widgets->_window);

    g_slice_free(TWidgets, app_widgets);

}

void on_main_window_destroy()
{
    gtk_main_quit();
}


void on_quit_button_clicked()
{
    gtk_main_quit();
}
void on_search_button_clicked(GtkWidget *widget, gpointer user_data)
{
    gtk_text_buffer_set_text((GtkTextBuffer*)user_data, "", -1);
    char *querry_string = (char*)gtk_entry_get_text(GTK_ENTRY(FIRST_SEARCH_BAR));
    char *dir_path = (char*)gtk_entry_get_text(GTK_ENTRY(SECOND_SEARCH_BAR));
    char *output_string = taskSolver(querry_string, dir_path);
    gtk_text_buffer_set_text((GtkTextBuffer*)user_data, output_string, strlen(output_string));


    
}
