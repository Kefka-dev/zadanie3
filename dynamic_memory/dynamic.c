#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGHT 1000
#define INITIAL_SIZE 16

int userInput(int size, char ***p_input);

int main()
{
    //printf("test");
    int count = 0, size = INITIAL_SIZE;
    char **input;
    input = (char**)malloc(size * sizeof(char *));
    
    count = userInput(size, &input);
    
    printf("riadkov %d\n", count);
    
    for (int i = 0; i < count; i++)
    {
        printf("%s", input[i]);
        free(input[i]);
    }
    free(input);
    return 0;
}

int userInput(int size, char ***p_input)
{
    int count = 0, dvaPrazdne =0, lenght =0;
    char **new_array;
    char buffer[MAX_LINE_LENGHT];
    do
    {
        fgets(buffer, MAX_LINE_LENGHT, stdin);
        
        if (count == size)
        {
            size = size *2;
            new_array = (char**)realloc(*p_input, size * sizeof(char*));
            *p_input = new_array;
        }
        
        lenght = strlen(buffer);
        
        if (buffer[0] == '\n')
        {
            (*p_input)[count] = (char*)malloc(4 * sizeof(char));
            dvaPrazdne++;
        }
        else
        {
            dvaPrazdne = 0;
            (*p_input)[count] = (char*)malloc((lenght + 1) * sizeof(char));
        }
        
        strcpy((*p_input)[count], buffer);
        count++;
    } while (dvaPrazdne <2);
    return count-2;
}