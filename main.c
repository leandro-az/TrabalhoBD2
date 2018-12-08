#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"


int main()
{
    //alocando memoria para o arquivo contendo o comando sql
    char * arquivo = (char*)malloc(sizeof(char)*400);

    //lendo o arquivo contendo o comando SQL
    scanf("%[^\n]" , arquivo);

    //processar o comando SQL
    START(arquivo);

    //liberar memoria alocada para o arquivo
    free(arquivo);

    return 0;
}

