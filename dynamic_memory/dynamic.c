#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGHT 1000
int main()
{
    //printf("test");
    int count = 0, dvaPrazdne =0, lenght =0, size = 16;
    char **intput = NULL;
    char buffer[MAX_LINE_LENGHT];

    intput = (char**)malloc(size * sizeof(char *));
    
    do
    {
        fgets(buffer, MAX_LINE_LENGHT, stdin);
        
        if (count == size)
        {
            size = size *2;
            intput = (char**)realloc(intput, size * sizeof(char*));
        }
        
        lenght = strlen(buffer);
        
        if (buffer[0] == '\n')
        {
            //printf("dlzka riadku je: %d\n", lenght);
            intput[count] = (char*)malloc(2 * sizeof(char));
            dvaPrazdne++;
        }
        else
        {
            dvaPrazdne = 0;
            intput[count] = (char*)malloc((lenght + 1) * sizeof(char));
        }
        
        //printf("velkost input[%d] = %d\n",count, sizeof(intput[count]));
        strcpy(intput[count], buffer);
        //printf("input[%d] = '%s'\n",count, intput[count]);
        //printf("velkost input = %d", sizeof(intput));
        count++;
    } while (dvaPrazdne <2);
    
    // printf("riadkov %d\n", count);
    // for (int i = 0; i < count; i++)
    // {
    //     printf("%s", intput[i]);
    // }

    return 0;
}