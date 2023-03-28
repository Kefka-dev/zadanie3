#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000
int main()
{
    //dynamicka alokacia jedneho stringu
    //char *string = malloc(sizeof(char) * lenght);

    char **strings;
    int initial = 2;

    // printf("Zadaj pocet stringov: ");
    // scanf("%d", &initial);

    strings = (char**)malloc(initial * sizeof(char *));

    char buffer[1000];
    int lenght = 0; //lenght of string from user

    //while (getchar() != '\n');

    printf("\n");
    // for (int i = 0; i < initial; i++)
    // {
    //     printf("Enter string %d: ", i+1);
    //     fgets(buffer, BUFFER_SIZE, stdin);
    //     lenght = strlen(buffer);
    //     buffer[lenght - 1] = '/0';//odstranenie \n z konca
    //     strings[i] = malloc(lenght * sizeof(char));
    //     strcpy(strings[i], buffer);
    printf("sizeof(buffer) = %d\n", sizeof(buffer));
    int prazdnyR =0, count =0;

    while (prazdnyR < 2)
    {   
        if (count == 2)
        {
            initial++;
            strings = (char**)realloc(strings, initial * sizeof(char));
        }
        
        fgets(buffer, sizeof(buffer), stdin);
        
        if (buffer[0] == '\n')
        {
            prazdnyR++;
            lenght = strlen(buffer);   
        }
        else
        {
            lenght = strlen(buffer) -1;
            buffer[lenght] = '\0';
            prazdnyR = 0;
        }

        strings[count] = (char*)malloc(lenght * sizeof(char));
        strcpy(strings[count], buffer);
        count++;
    }
    
    printf("vypis stringov\n");

    for (int i = 0; i < initial; i++)
    {
        printf("%s\n", strings[i]);
    }
    

    // printf("\nResulting strings array:\n\n");
    // for (int i = 0; i < initial; i++)
    // {
    //     printf("strings[%d] = %s\n", i, strings[i]);
    // }
    
    // for (int i = 0; i < initial; i++)
    // {
    //     free(strings[i]);
    // }
    // free(strings);
    
    return 0;
}