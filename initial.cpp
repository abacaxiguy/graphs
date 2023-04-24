#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc - 1 == 0)
        printf("ERRO, nenhum argumento foi mandado!\n");

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h"))
            printf("***** HELP *****\n");
        if (!strcmp(argv[i], "-s"))
            printf("***** ORDEM CRESCENTE *****\n");
        if (argc - 1 < 2 && (!strcmp(argv[i], "-o") || !strcmp(argv[i], "-f") || !strcmp(argv[i], "-i") || !strcmp(argv[i], "-l")))
        {
            printf("ERRO, USE MAIS UM ARGUMENTO COMO DITO NO HELP (-h)\n");
            break;
        }
        if (!strcmp(argv[i], "-o"))
            printf("OUTPUT, SEU ARQUIVO É: %s\n", argv[i + 1]);
        if (!strcmp(argv[i], "-f"))
            printf("FILE, SEU ARQUIVO É: %s\n", argv[i + 1]);
        if (!strcmp(argv[i], "-i"))
            printf("VERTICE INICIAL: %d\n", atoi(argv[i + 1]));
        if (!strcmp(argv[i], "-l"))
            printf("VERTICE FINAL: %d\n", atoi(argv[i + 1]));
    }
    printf("********* FINALIZANDO **********\n");
}