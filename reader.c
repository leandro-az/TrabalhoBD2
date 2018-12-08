#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create.h"
#include "select.h"
#include "delete.h"
#include "insert.h"
#include "update.h"

/*Estrutura que contem cada Código a ser executado e
um ponteiro para o próximo código da lista*/
typedef struct SQL{
    char * code;
    struct SQL * next;
}SQL;

void FIND(SQL * list){
    if(!list)return;
    FIND(list->next);
    CALL(list->code);
    free(list);
}

//Inicia a leitura do arquivo contendo os comandos SQL
void START(filename){
    FILE* fh;
    fh = fopen(filename, "r");

    //verifica se o arquivo existe
    if (fh == NULL){
        printf("o arquivo informado não existe\n%s", filename);
        return 0;
    }

    //lendo linha por linha
    const size_t line_size = 300;
    char* line = malloc(line_size);
    SQL * ini = NULL ,*aux = NULL;

    char * current;
    while (fgets(line, line_size, fh) != NULL)  {
        current = (char*)malloc(sizeof(char)*500);
        strcpy(current,line);
        printf(current);
        aux = (SQL*)malloc(sizeof(SQL));
        aux->code = current;
        aux->next = ini;
        ini = aux;
    }
    FIND(ini);
    fclose(fh);
}

//seleciona qual comando sql a ser executado
void CALL(char * comando){
    //primeira letra do comando SQL
    char letra = toupper(comando[0]);
    //solucionar o comando aqui
    switch(letra)
    {
        case 'S':
        SELECT(comando);
        break;

        case 'C':
        CREATE(comando);
        break;

        case 'D':
        DELETE(comando);
        break;

        case 'U':
        UPDATE(comando);
        break;

        case 'I':
        INSERT(comando);
        break;
    }
}
