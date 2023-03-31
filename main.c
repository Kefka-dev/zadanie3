#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_LINE_LENGHT 1000
#define INITIAL_SIZE 16
#define SECTION_SEPARATOR '.'
#define TRUE 1
#define FALSE 0
#define SECTION_NOT_FOUND -1
#define KEY_VALUE_SEPARATOR '='

int userInput(int size, char ***p_input);
void printLines(int amount, char **lines);
void extractSectionAndKey(int size,char **p_section, char** p_key);
int findSectionLine(int lineAmount, char **p_input, char *p_section);
int checkKey(char***p_input,char**p_key ,int lineToCheck, int keyLenght);
void printKeyValue(char ***p_input, int lineNumber);

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
            char *key;
            int currentLine =0, keyLenght, isWantedKey;
            //ak je zadana nepovinna cast povinneho argumentu
            // printf("%s\n", optarg);
            if (strchr(optarg, SECTION_SEPARATOR) != NULL)
            {
                
                extractSectionAndKey(size, &section, &key);
                // printf("%s\n", section);
                // printf("%s\n", key);
                keyLenght = strlen(key);
                int sectionLine = findSectionLine(lineCount, input, section);
                printf("section line = %d\n", sectionLine);
                if (sectionLine != SECTION_NOT_FOUND)
                {
                    currentLine = sectionLine +1;
                    while (input[currentLine][0] != '[')
                    {
                        if (input[currentLine][0] == ';')
                        {
                            currentLine++;
                            continue;
                        }
                        isWantedKey = checkKey(&input, &key, currentLine, keyLenght);
                        
                        if (isWantedKey == TRUE)
                        {
                            // printf("kluc je tu %d\n", currentLine);
                            printKeyValue(&input,  currentLine);
                            break;
                        }
                        currentLine++;
                    }
                }
                free(section);
                free(key);
            }
            else
            {
                keyLenght = strlen(optarg);
                while (currentLine < lineCount)
                {
                    if (input[currentLine][0] == ';')
                    {
                        currentLine++;
                        continue;
                    }

                    if ( input[currentLine][0] == '[')
                    {
                        currentLine++;
                        continue;
                    }

                    if ( input[currentLine][0] == '\n')
                    {
                        currentLine++;
                        continue;
                    }
                    
                    isWantedKey = checkKey(&input, &optarg, currentLine, keyLenght);
                    
                    if (isWantedKey == TRUE)
                    {
                        // printf("kluc je tu %d\n", currentLine);
                        printKeyValue(&input,  currentLine);
                    }
                    currentLine++;
                }
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

    if (argc == 1)
    {
        printLines(lineCount, input); 
        return 0;
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

void extractSectionAndKey(int size , char **p_section, char**p_key)
{
    int charCount = 0, optargLenght, keyLenght;
    optargLenght = strlen(optarg);
    
    //vypocet dlžky section
    while (optarg[charCount] != SECTION_SEPARATOR)
    {
        charCount++;
    }

    keyLenght = optargLenght - charCount;
    *p_section = (char*)malloc((charCount+1)* sizeof(char));
    *p_key = (char*)malloc((keyLenght + 1) * sizeof(char));
    strncpy(*p_section, optarg, charCount);
    strncpy(*p_key, optarg+(charCount+1), keyLenght);
}

int findSectionLine(int lineAmount, char **p_input, char *p_section)
{
    int exists = FALSE;
    for (int i = 0; i < lineAmount; i++)
    {
        if( ((strchr(p_input[i], '[') != NULL) && (strstr(p_input[i], p_section) != NULL)))
        {
            return i;
        }
    }
    if (exists = FALSE)
    {
        return SECTION_NOT_FOUND;
    }
    
}

int checkKey(char***p_input, char**p_key , int lineToCheck, int keyLenght)
{
    int charCount = 0, keyStart = 0, whiteSpaceCount = 0;
    while (isspace((*p_input)[lineToCheck][keyStart]) != FALSE)
    {
        keyStart++;
    }
    //printf("keyStart = %d, pre %s", keyStart, (*p_input)[lineToCheck]);
    while (whiteSpaceCount<2 && (*p_input)[lineToCheck][charCount] != '=')
    {
        if ((*p_input)[lineToCheck][(charCount + keyStart)] == ' ')
        {
            whiteSpaceCount++;
            //printf("whiteSpaceCount = %d\n", whiteSpaceCount);
        }
        charCount++;
    }
    //printf("charCount = %d, pre %s", charCount, (*p_input)[lineToCheck]);
    //strncmp vrati 0 ak sa stringi rovnaju
    if (charCount == keyLenght)
    {
        if (strncmp(*p_key, (*p_input)[lineToCheck], keyLenght) == 0)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    
}

void printKeyValue(char ***p_input, int lineNumber)
{
    int charCount = 0, valueStart = 0, whiteSpaceCount = 0, lenghtAfterRovnitko;
    char* p_zaRovnitkom;
    p_zaRovnitkom = strchr((*p_input)[lineNumber], KEY_VALUE_SEPARATOR)+1;

    while (isspace(p_zaRovnitkom[valueStart]) != FALSE)
    {
        valueStart++;
    }
    p_zaRovnitkom = p_zaRovnitkom+valueStart;
    //odstranenie whitespaces za rovnitkom
    lenghtAfterRovnitko = strlen(p_zaRovnitkom);    
    while (lenghtAfterRovnitko > 0 && isspace(p_zaRovnitkom[lenghtAfterRovnitko-1]))
    {
        lenghtAfterRovnitko--;
    }
    p_zaRovnitkom[lenghtAfterRovnitko] = '\0';

    printf("%s\n", p_zaRovnitkom);

}