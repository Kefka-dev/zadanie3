#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE_LENGHT 1000
#define INITIAL_SIZE 16
#define SECTION_SEPARATOR '.'

int userInput(int size, char ***p_input);
void printLines(int amount, char **lines);
void extractSection(int size,char **p_section);

int main(int argc, char* argv[])
{
    int opt;
    char* optstring = ":k:s:u:";
    int isU = 0;

    int lineCount = 0, size = INITIAL_SIZE;
    char **input = NULL;

    input = (char**)malloc(size * sizeof(char *));
    
    lineCount = userInput(size, &input);

    while((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt)
        {
        case 'k':
            char *section;
            //ak má section
            if (strchr(optarg, SECTION_SEPARATOR) != NULL)
            {
                extractSection(size, &section);
                // printf("%s\n", section);
                
                
            }
            else
            {
                printf("pipik");
            }
            
            
            break;
        case 's':
            printf("Prepinac -s a jeho povinny argument %s\n", optarg);
            break;
        case 'u':
            printf("Prepinac -u\n");
            isU = 1;
            break;
        case '?':
            printf("E1\n");
            return 0;
        case ':':
            printf("E2\n");
            return 0;
        }
    }
    if (optind + 1 == argc && isU == 1)
    {
        printf("bol zadany jeden non-option argument a to %s\n", argv[optind]);
    }
    else if(isU == 1)
    {
        printf("E3\n");
        return 0;
    } 

    if (optind == argc)
    {
        printLines(lineCount, input); 
        return 0;
    }

    //uvolnenie naalokovanej pamete
    for (int i = 0; i < lineCount; i++)
    {
        free(input[i]);
    }
    free(input);

    return 0;
}

int userInput(int size, char ***p_input)
{
    int count = 0, dvaPrazdne =0, lenght =0;
    char **resizedInput;
    char buffer[MAX_LINE_LENGHT];
    do
    {
        fgets(buffer, MAX_LINE_LENGHT, stdin);
        
        if (count == size)
        {
            size = size + 16;
            resizedInput = (char**)realloc(*p_input, size * sizeof(char*));
            *p_input = resizedInput;
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

void printLines(int amount, char **lines)
{
    for (int i = 0; i < amount; i++)
    {
        printf("%s", lines[i]);
    }   
}

void extractSection(int size , char **p_section)
{
    int charCount = 0;
    while (optarg[charCount] != SECTION_SEPARATOR)
    {
        charCount++;
    }
    *p_section = (char*)malloc((charCount+1)* sizeof(char));
    memcpy(*p_section, optarg, charCount);
}