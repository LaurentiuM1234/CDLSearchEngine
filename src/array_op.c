#include "array_op.h"
#include <stdlib.h>
#include <stdio.h>

int *arrayAND(int *array1, int *array2, int size)
{
    int *result_array = calloc(size, sizeof(int));
    
    if(!result_array)
    {
        fprintf(stderr, "Failed to alloc result array!");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < size; i++)
    {
        result_array[i] = array1[i] && array2[i];
    }
    
    
    return result_array;
}

int *arrayOR(int *array1, int *array2, int size)
{
    int *result_array = calloc(size, sizeof(int));
    
    if(!result_array)
    {
        fprintf(stderr, "Failed to alloc result array!");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < size; i++)
    {
        result_array[i] = array1[i] || array2[i];
    }
    
    
    return result_array;
}

int *arrayNOT(int *array, int size)
{
    int *result_array = calloc(size, sizeof(int));
    
    if(!result_array)
    {
        fprintf(stderr, "Failed to alloc result array!");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < size; i++)
    {
        result_array[i] = !array[i];
    }
    
    return result_array;
}
