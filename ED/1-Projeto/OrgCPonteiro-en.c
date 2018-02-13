/*
@author: Caio E. C. de Oliveira.

Objetive: to organize an array:
    Without creating another one;
    Using only two pointers.

What's left: understand lines 45 and 65;
*/
#include <stdio.h>
 
#define N 8
//Functions declaration
void get_data(int *array);
void shows_original(int *array);
void shows_increasing(int *DataArray);
void shows_decreasing(int *DataArray);

int main()
{
    int DataArray[N];
    get_data(DataArray);
    shows_original(DataArray);
    shows_increasing(DataArray);
    shows_decreasing(DataArray);
    printf("\n");
    return 0;
}

//lib.
void get_data(int *array)
{
    int i;
    printf("Include integers in the array:\n");
    for(i=0;i<N;i++)
    {
        scanf("%d", &array[i]);
    }
}
void shows_original(int *array)
{
    int i;
    printf("array: original.\n");
    for(i=0;i<N;i++)
        printf("Inteiros: %d   || Endereco: %p\n", array[i], &array[i]);
    printf("\n");
}
void shows_increasing(int* DataArray)
{
    int *next = DataArray, *ptr, *lastShown;
    int *end = DataArray + N;
    printf("Array, increasing_order:\n");
    for(ptr=DataArray; ptr<end; ptr++)
    {
        if(*ptr<*next)  next = ptr;  //finds the smallest
    }
    for(lastShown=next, next = NULL; lastShown!=NULL; lastShown = next, next = NULL)
    {
        for(ptr = DataArray; ptr<end; ptr++)
        {
            if(*ptr==*lastShown)
                printf("%p: %d\n", ptr, *ptr);
            else if(*ptr>*lastShown && (next==NULL || *ptr<*next))
                next = ptr;
        }
    }
}
void shows_decreasing(int* DataArray)
{
    int *next = DataArray, *ptr, *lastShown;
    int *end = DataArray + N;
    printf("Array, decreasing_order:\n");
    for(ptr=DataArray; ptr<end;ptr++)
    {
        if(*ptr>*next)  next=ptr; //finds the greatest
    }
    for(lastShown=next, next=NULL; lastShown!=NULL; lastShown = next, next =NULL)
    {
        for(ptr=DataArray;ptr<end; ptr++)
        {
            if(*ptr==*lastShown)
                printf("%p: %d\n", ptr, *ptr);
            else if(*ptr<*lastShown && (next==NULL || *ptr>*next))
                next = ptr;
        }
    }
}