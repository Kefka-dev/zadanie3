#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char* argv[])
{
    int opt;
    char* optstring = ":k:s:u:";
    int isU = 0;
    while((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt)
        {
        case 'k':
            printf("Prepinac -k\n");
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

    // if (optind == argc && isU == 1){
    //     printf("E3");
    //     return 0;
    // }
    
    return 0;
}