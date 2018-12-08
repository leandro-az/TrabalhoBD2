#include <stdio.h>
#include <stdlib.h>
#include <string.h>




char* copiaString(char* s, int inicio, int fim) {
    char *inf = malloc(sizeof(char*)*(fim - inicio));


    int p;
    for (p = inicio; p < fim; p++) {
        inf[p - inicio] = s[p];
    }
    inf[fim - inicio] = '\0';
    return inf;
}


int tamanhoLAtrib(char * s, int inicio, int fim) {
    int p;
    int resp = 0;
    if (fim - inicio > 1) {
        for (p = inicio; p < fim; p++) {
            if (s[p] == ',') {
                resp++;
            }
        }
        resp++;
        return resp;
    } else {
                //printf("%d tamnho la", fim-inicio);
        return fim - inicio;
    }


}


void apagaAtributos(char** at, int tam){
        int i =0;
        while(i<tam){
                free(at[i]);
                i++;
        }
        free(at);
}
char** salvaAtributos(char * s, int inicio, int fim, int tam) {


    char** listaAtrib = malloc(sizeof (char)*(tam));
    int l = 0, c = 0, p = inicio, posIn = inicio, j = 0;
    if (tam >= 1) {
        while (l < tam && p < fim) {
            if (s[p] == ',') {
                if (p - posIn == 0) {
                    //mensagem errroooo
                }
                listaAtrib[l] = (char*) malloc(sizeof (char)*(p - posIn));
                for (j = posIn; j < p; j++) {
                    listaAtrib[l][j - posIn] = s[j];
                }
                listaAtrib[l][p - posIn] = '\0';
                l++;
                posIn = p + 1;
            }


            p++;
        }
        listaAtrib[l] = (char*) malloc(sizeof (char)*(p - posIn));
        for (j = posIn; j < p; j++) {
            listaAtrib[l][j - posIn] = s[j];
        }


        listaAtrib[l][p - posIn] = '\0';
        return listaAtrib;
    } else {
        return listaAtrib;
    }
}


int compara(char* s, char* t, int inicio, int fim) {


    char inf[fim - inicio];
    //printf("%d\n", fim - inicio);
    int p;
    for (p = inicio; p < fim; p++) {
        inf[p - inicio] = s[p];
    }
    inf[fim - inicio] = '\0';


    if (strcasecmp(inf, t) == 0)return 1;
    return 0;


}


int estaOrdenada(char* tabela, char* atri){
        char endTab[100];


        strcpy(endTab, tabela);
        strcat(endTab,".ctl");

        //printf("%s entrou \n", endTab);

        FILE *tab = fopen(endTab, "r");
        char linha[100];
        int i=0;
        int inicio=0;

        fgets(linha, sizeof(linha), tab);
        while( linha!=NULL ){
                        //printf("%s e a linha %d\n", linha,sizeof(linha));
                        fgets(linha, sizeof(linha), tab);
                        while(linha[i]!='\n' && inicio==0){
                                if(linha[i]==','){
                                if(compara(linha, atri, inicio, i)){

                                        if(strstr(linha, ",ord")!=NULL){
                                        //printf("teeem");
                                        return 1;
                                        }else{
                                                                                //printf("nao teeem");


                                        return 0;
                                        }

                                }else{

                                }
                                inicio=i+1;
                                }
                                i++;
                        }
                        inicio=0;
                        i=0;
                        }
                        fclose(tab);
        return 0;
}


void apagaItens(char** itens, int tam){
int i=0;
        while(i<tam){
                free(itens[i]);
                i++;
        }
        free(itens);
}


char** salvaCondicao(char * s, int inicio, int *fim, int *w) {


    char** resp = malloc(sizeof (char)*(2));
    int p = inicio, posIn = inicio;
    int i = 0, j = 0;
    int achouCond = 0;


        if(*w==3){
        //e atributo join
         while (p < *fim && achouCond == 0) {
        if (s[p] == '=') {
                         resp[i] = (char*) malloc(sizeof (char)*(p - posIn));
            for (j = posIn; j < p; j++) {
                resp[i][j - posIn] = s[j];
            }
            resp[i][p - posIn] = '\0';
            i++;


            posIn = p + 1;
                        achouCond=1;
                }
                p++;
        }
        }else{
    while (p < *fim && achouCond == 0) {
        if (s[p] == '=' || s[p] == '<' || s[p] == '>') {
            achouCond = 1;
            if (s[p] == '=') {


                if (s[p + 1] == '=' || s[p + 1] == '<' || s[p + 1] == '>') {
                    printf("Erro coondicao");
                                        *w=-1;
                }
                                        *w=1;


            }
            if (s[p] == '<') {
                *w = 2;
                if (s[p + 1] == '<') {
                    printf("Erro coondicao");
                                        *w=-1;
                }
                if (s[p + 1] == '=') {
                    *w = 3;
                }
                if (s[p + 1] == '>') {
                    *w = 6;
                }


            }


            if (s[p] == '>') {
                *w = 4;
                if (s[p + 1] == '<' || s[p + 1] == '>') {
                    printf("Erro coondicao");
                                        *w=-1;
                }
                if (s[p + 1] == '=') {
                    *w = 5;
                }
            }




            resp[i] = (char*) malloc(sizeof (char)*(p - posIn));


            for (j = posIn; j < p; j++) {
                resp[i][j - posIn] = s[j];
            }
            resp[i][p - posIn] = '\0';
            i++;
            if (*w > 4 || *w == 3)p++;


            posIn = p + 1;
        }
        p++;
    }
        }
        if(i==1){


    if (s[p] != '=' && s[p] != '<' && s[p] != '>') {
                if((*fim-inicio)>1){
                                                                                 if(s[posIn]=='"'){

                                                                        //        printf("\n\n ESTOU salvanaod a condicao: %doi\n", *fim);
                                                                                j=posIn+1;
                                                                                        while(s[j]!='"' && s[j]!='\0' ){
                                                                                                j++;
                                                                                        }
                                                                                        posIn++;
                                                                                        *fim=j;

                                                                                //        printf("\n\n ESTOU salvanaod a condicao: %d\n", *fim);
                                                                                        resp[i] = (char*) malloc(sizeof (char)*(*fim - posIn));

                                                                                        for (j = posIn; j < *fim; j++) {
                                                                                                resp[i][j - posIn] = s[j];
                                                                                        }
                                                                                        resp[i][*fim - posIn] = '\0';
                                                                                        *fim=j+1;

                                                                                        //printf("\n\n ESTOU salvanaod a condicao: %d\n", *fim);
                                                                                }else{
                                                                                        resp[i] = (char*) malloc(sizeof (char)*(*fim - posIn));

                                                                                        for (j = posIn; j < *fim; j++) {
                                                                                                resp[i][j - posIn] = s[j];
                                                                                        }
                                                                                        resp[i][*fim - posIn] = '\0';
                                                                                        }
                }else{
                        //erro
                        *w=-1;
                }
    }else{
                //erroo
                *w=-1;
        }
        }else{
                //erro
                *w=-1;
        }
    return resp;
}


char* removeSubString(char* s, char* t){
        int i =0,j=0, k=0;
        while(s[i]!='\0'){
                if(s[i]=='.'){
                        j=i+1;
                }
                i++;
        }
        char* resp=malloc(sizeof(char)*(i-j));
        i=j;
        while(s[i]!='\0'){
                //printf("removendo %c\n", s[i]);
                resp[k]=s[i];
                k++;
                i++;
        }
        resp[k]='\0';
        return resp;

}




void salvaJuncao(char** condJoin, char* tabela, char* tabelaB, char* tabelaSel, int join,FILE *op){
        char inf[1000]="";
        char **condJuncao = malloc(sizeof(char)*2);
                                        strcpy( inf, "" );
                                        char cond[100]="";


if(join>0){


condJuncao[0]=removeSubString(condJoin[0], tabela);

                condJuncao[1]=removeSubString(condJoin[1], tabelaB);
        if(strstr(condJoin[0], tabela )!=NULL){
                                //printf("Processando Juncao");
                if(estaOrdenada(tabela, condJuncao[0])==1 && estaOrdenada(tabelaB, condJuncao[1])==1){
                                                strcat(inf, "J2(");


                }else{
                                                strcat(inf, "J1(");


                }


                                //printf("cond1: %s e %s\n", condJuncao[0], condJuncao[1]);

                        }else{
                                if(strstr(condJoin[0], tabelaB )!=NULL){
//                                                                printf("Processando Juncao");
                                        if(estaOrdenada(tabela, condJuncao[1])==1 && estaOrdenada(tabelaB, condJuncao[0])==1){
                                                strcat(inf, "J2(");


                }else{
                                                strcat(inf, "J1(");


                }
                                }

                        }

                        if(strcasecmp(tabelaSel, "NULL")){
                        //printf("\n ooooolha \nfoi a tabe selecionada:%s\n\n", tabelaSel);
                        if(strcasecmp(tabela, tabelaSel) == 0){
                                strcat(inf, "SaidaInt");
                                strcat(inf, ",");
                                strcat(inf, tabelaB);
                                strcat(inf, ",");


                        }else{
                                strcat(inf, tabela);
                                strcat(inf, ",");
                                strcat(inf, "SaidaInt");
                                strcat(inf, ",");

                        }
                        }else{
                        strcat(inf, tabela);
                                strcat(inf, ",");
                                strcat(inf, tabelaB);
                                strcat(inf, ",");
                        }

                        //printf("primeiro  join:%s e a tabela sel:%s\n", condJoin[0], *tabelaSel);
                        if(strstr(condJoin[0], tabelaSel) != NULL){

                        //printf("primeiraaaaaaa\n");
                                        strcpy(cond, "SaidaInt.");
                                        strcat(cond, condJuncao[0]);
                                        strcat(inf, cond);

                                        strcat(inf, ",");
                                        strcat(inf, condJoin[1]);
                                        strcat(inf, ",");
                                }else{
                                        if(strstr(condJoin[1], tabelaSel) !=NULL){
                                                strcat(inf, condJoin[0]);
                                                if(join>0){
                                                strcpy(cond, "SaidaInt.");
                                                }else{
                                                        strcpy(cond, "SaidaInt.");


                                                }
                                                strcat(cond, condJuncao[1]);
                                                strcat(inf, ",");
                                                strcat(inf, cond);
                                                strcat(inf, ",");
                                        }else{
                                        strcat(inf, condJoin[0]);
                                strcat(inf, ",");
                                strcat(inf, condJoin[1]);
                                strcat(inf, ",");
                                        }
                                }


                strcat(inf, "Saidajoin)\0");
        //printf("\n-----Resultado do Join--------\n%s\n", inf);
                                        fprintf(op, "%s\n", inf);
                                        apagaItens(condJuncao,2);


        }
        }


void salvaProjecao(char *tabela, int qtdAtrib, int distinct, char**listAtrib,int join, int cont, int onderBy, int *where,FILE *op, char*tabelaSel){
        char inf[1000]="";
        char qtd[10]="\0";
        int i =0;


        strcpy( inf, "" );


        if(distinct==1){
                //tem distinct
                if(cont==4){
                strcat(inf, "P3(");
                }else{
                                                strcat(inf, "P4(");


                }

        }else{
                //nao tem distinct

                if(cont==4){
                strcat(inf, "P1(");
                }
                else{
                                                strcat(inf, "P2(");


                }
        }
        char cond[100]="";
        if(*where!=-1 && *where!=0) strcpy( tabela, "SaidaInt" );
        if(join>0){
        strcpy( tabela, "SaidaJoin" );
        }
        //printf("qtd de atri %d\n", qtdAtrib);



        strcat(inf, tabela);
                strcat(inf, ",");
                itoa(qtdAtrib, qtd, 10);
                strcat(inf, qtd);
                strcat(inf, ",");
                for(i=0;i<qtdAtrib;i++){
                        if(*where!=-1 && *where!=0){
                                //printf("tabela Sel:%s\n", tabelaSel);
        strcat(tabelaSel,".");
                        if(strstr(listAtrib[i], tabelaSel)!=NULL && join>0)
                        {
                                strcpy(cond, "SaidaInt.");

                                strcat(cond, removeSubString(listAtrib[i],""));
                                strcat(inf, cond);

                        }else{
                                strcat(inf, listAtrib[i]);
                                }
                                strcat(inf, ",");
                }else{
                                                strcat(inf, listAtrib[i]);


                strcat(inf, ",");
                }
                }
                strcat(inf, "Saida)\0");
                //printf("Projecao: %s", inf);

                                                fprintf(op, "%s\n", inf);


                }

char* salvaSelect(char* tabela, char* tabelaB, char** condWhere,int *where,int join, FILE *op){
        char inf[1000]="";
        char *tabelaSel=malloc(sizeof(char)*(sizeof(tabela)*3));
        char qtd[10]="\0";




                if(join>0)
                {
                //salvaSelect(tabela, tabelaB, condWhere, where, join);
                //printf("!");
                        if(strstr(condWhere[0], tabela )!=NULL){

                //printf("!");
                                strcpy(tabelaSel, tabela);
                        }else{
                                if(strstr(condWhere[0], tabelaB )!=NULL){
                                        strcpy(tabelaSel, tabelaB);
                                }
                        }


                                condWhere[0]=removeSubString(condWhere[0], tabelaSel);
                }else{
                        strcpy(tabelaSel, tabela);
                }
                //printf("Fazendo a selecao %s", tabelaSel);
                if(estaOrdenada(tabelaSel, condWhere[0])==1){
                                //printf("!\n\n");


                                                                strcat(inf, "O");


                                }else{
                                                //printf("!");


                                strcat(inf, "S");
                                }
                                itoa(*where, qtd, 10);
                                strcat(inf, qtd);
                                strcat(inf, "(");
                                strcat(inf, tabelaSel);
                                strcat(inf, ",");
                                strcat(inf, condWhere[0]);
                                strcat(inf, ",");
                                strcat(inf, condWhere[1]);
                                strcat(inf, ",");
                                strcat(inf, "SaidaInt)\0");

                                //printf("Selecao %s\n",inf);
                                fprintf(op, "%s\n", inf);
                                apagaItens(condWhere,2);

                                return tabelaSel;
}
int salvaSelectArquivo(int tipo, int where,int orderBy,char** listAtrib, int qtdAtrib, char ** listOrdem, int qtdAtribOrdem, char** condWhere, int distinct, char* tabela, char *tabelaB, int join, char** condJoin,FILE *op){
        if(tipo==-1){
                //printf("nao foi possivel salvar o comando\n");
        }

        char inf[1000]="";
        int i=0, fim=0;
        char qtd[10]="\0";
        char* tabelaSel="NULL";
        //printf("entrooou");
        while(fim==0){
        if(tipo==4){
        //select simples sem order by ou where pode ter ou nao distinct

                                //printf("e 4444");
                                if(join>0){
                                salvaJuncao(condJoin,tabela,tabelaB, tabelaSel, join,op);


                                                }
                                                if(where==10){
                                                                        tabelaSel=salvaSelect(tabela, tabelaB, condWhere, &where, join,op);


                                                }



        salvaProjecao(tabela, qtdAtrib, distinct, listAtrib,join, tipo, orderBy, &where,op, tabelaSel);
//printf("e 4444");
                fim=1;
        }
        if(tipo==5){
                //tem order by ou where ou os dois
                if (where>0 && orderBy>0){
                //printf("ESTAMOS!!!");
                        free(tabelaSel);
                        tabelaSel=salvaSelect(tabela, tabelaB, condWhere, &where, join,op);
                        //printf("aaa tabela %s\n\n", tabelaSel);
                        if(join>0)salvaJuncao(condJoin, tabela, tabelaB,tabelaSel, join,op);
                        salvaProjecao(tabela, qtdAtrib, distinct, listAtrib,join, tipo, orderBy, &where,op,tabelaSel);


                        fim=1;
                        orderBy=0;
                //tem os dois
                }else{
                        if(where>0){
                                        free(tabelaSel);


                                tabelaSel=salvaSelect(tabela, tabelaB, condWhere, &where, join,op);


                                if(join>0)salvaJuncao(condJoin,tabela,tabelaB, tabelaSel, join,op);


                                                //printf("estou aqui no where!! %d \n", where);



        salvaProjecao(tabela, qtdAtrib, distinct, listAtrib,join, tipo, orderBy, &where,op, tabelaSel);

                                //tem só o where
                                fim=1;
                                //where=-10;

                        }
                        if(orderBy>0){
                                //tem so o order by
                                                //free(tabelaSel);


                                if(join>0)salvaJuncao(condJoin, tabela, tabelaB,"NULL", join,op);

                                salvaProjecao(tabela, qtdAtrib, distinct, listAtrib,join, tipo, orderBy, &where,op,tabelaSel);
                                //printf("\n\nA juncao %s\n\n",inf);
                        fim=1;
                        orderBy=0;
                        }
                }
        }
        }
        free(tabelaSel);
}
int Insert(char *sql, FILE *op) {

    int i = 0, inicio = 0;
    int cont = 0;
    int dist = 0;
    char **atrib, **atribOrdem;
    int qtdAtrib;
    char* tabela;
    char* tabelaB;
        char **condJuncao;
    int k = 0;
    int orderBy = 0, qtdAtribOrdem = 0;
    int where = 0;
    char **condWhere;
        int join=0;


    //solucionar o comando aqui


        if(strstr(sql, " JOIN ")!=NULL){
        join=1;
        //printf("tem join");
        }
    while (sql[i] != '\0') {


        if (sql[i] == ' ' || sql[i] == ';') {


            if (cont == 0) {
                if (compara(sql, "SELECT", inicio, i)) {
                    cont++;
                   // printf("SELECT!!!\n");
                }else{
                                        //erro
                                        cont=-1;
                                        printf("erro no SELECT\n");

                                }
            } else {
                if (cont == 1) {
                    if (compara(sql, "DISTINCT", inicio, i) && dist == 0) {
                        dist = 1;


                        //printf("DISTINCT!!!\n");
                    } else {
                        qtdAtrib = tamanhoLAtrib(sql, inicio, i);
                        cont++;
                        //printf("numero de at:%d\n", qtdAtrib);
                        if (qtdAtrib > 0) {
                           // printf("Tem atributos\n");
                            atrib = salvaAtributos(sql, inicio, i, qtdAtrib);
                           // printf("%s\n", atrib[0]);
                           // printf("%s\n", atrib[1]);
                           // printf("%s\n", atrib[2]);
                        } else {
                            //erroooooooo
                                                                                        cont=-1;
                                                                                        printf("erro no DISTINCT\n");

                        }
                    }




                } else {
                    if (cont == 2) {
                        if (compara(sql, "FROM", inicio, i)) {
                            cont++;
                           // printf("FROM!!!\n");
                        }else{
                                                        //erro
                                                        cont=-1;
                                                        printf("erro no From\n");

                                                }
                    } else {
                        if (cont == 3) {
                                                        if(join>0){

                                                                if(join==3){
                                                                        condJuncao = salvaCondicao(sql, inicio, &i, &join);

                                    //printf("%s \n", condJuncao[0]);
                                   // printf("%s\n", condJuncao[1]);
                                                                        cont++;
                                                                }
                                                                if(compara(sql, "ON", inicio, i)){
                                                                        join++;
                                                                }
                                                                if(join==2){
                                                                        tabelaB = copiaString(sql, inicio, i);
                                                                        //printf("Tabela: %s\n", tabelaB);
                                                                        //cont++;
                                                                }



                                                                if(compara(sql, "JOIN", inicio, i)){
                                                                        join++;
                                                                }
                                                                if(join==1){
                                                                        tabela = copiaString(sql, inicio, i);
                                                                }
                                                        }else{
                                                                if(join==0){
                                                                        tabela = copiaString(sql, inicio, i);
                                                                        cont++;
                                                                }

                                                        }
                          //  printf("Tabela: %s\n", tabela);
                        } else {
                            if (cont == 4) {
                                                        if (orderBy == 2) {
                                                qtdAtribOrdem = tamanhoLAtrib(sql, inicio, i);


                                               // printf("numero de at:%d\n", qtdAtribOrdem);
                                                if (qtdAtribOrdem > 0) {
                                                   // printf("Tem atributos para ordenar\n");
                                                    cont++;
                                                    atribOrdem = salvaAtributos(sql, inicio, i, qtdAtribOrdem);
                                                   // printf("atrviutoo %s\n\n", atribOrdem[0]);


                                                } else {
                                                    //print de erro
                                                                                                        cont=-1;
                                                                                                        printf("erro no order By\n");
                                                }
                                            }

                                                                                        if (orderBy == 1) {
                                            if (compara(sql, "BY", inicio, i)) {
                                                orderBy = 2;
                                               // printf("BY!!!\n");
                                            }else{
                                                                                                cont=-1;
                                                                                                printf("erro no order BY\n");
                                                                                        }
                                        }

                                                                                if (orderBy == 0 && where!=10 && where!=0) {
                                                                                        if (compara(sql, "ORDER", inicio, i)) {
                                                                                                        orderBy = 1;
                                                                                                        //printf("ORDER!!!\n");
                                                                                                }else{
                                                                                                cont=-1;
                                                                                                orderBy=-1;
                                                                                                //printf(" aruiiiierro no order By%cooi\n",sql[inicio]);
                                                                                                }
                                    }

                                                                         if (where == 10 && orderBy == 0) {

                                                                                //printf("\n\n ESTOU NO WHERE: %c\n", sql[inicio]);

                                        condWhere = salvaCondicao(sql, inicio, &i, &where);

                                                                                //printf("esse e o where=%d",where);

                                        //printf("%s\n", condWhere[0]);
                                       // printf("%s\n", condWhere[1]);
                                        //cont++;
                                    }
                                if (where == 0) {
                                                                        //printf("aquiiii %cooi\n",sql[inicio]);
                                    if (compara(sql, "WHERE", inicio, i)) {
                                        where = 10;
                                        //printf("WHERE11!!!\n");
                                    } else {
                                                                        //printf("hahahaer By%cooi\n",sql[inicio]);
                                        where = -1;
                                                                                if (compara(sql, "ORDER", inicio, i)) {
                                                                                                        orderBy = 1;
                                                                                                        //printf("ORDER!!!\n");
                                                                                                }else{
                                                                                                cont=-1;
                                                                                                orderBy=-1;
                                                                                                //printf("errokkkkkkno order By%cooi\n",sql[inicio]);
                                                                                                }
                                    }
                                }
                            }


                        }
                    }
                }
            }
            inicio = i + 1;


        }


        i++;


    }
        //printf("cont =%d", cont);
        if(where>=1 && cont==4){
        cont=5;
        }

        //printf("contador =%d  where %d order %d\n\n", cont, where, orderBy);




        salvaSelectArquivo(cont,where, orderBy, atrib, qtdAtrib, atribOrdem, qtdAtribOrdem, condWhere, dist, tabela, tabelaB, join, condJuncao,op);

        apagaAtributos(atrib,qtdAtrib);
        //printf("apagando itens");


        if(orderBy!=-1 && orderBy!=0){
        //printf("apagando atrib");


        apagaAtributos(atribOrdem,qtdAtribOrdem);
        }
        if(join>0){//printf("apagando joins");


        apagaItens(condJuncao,2);
        }
        if(where!=-1 && where!=0){
        //printf("apagando itens");
        apagaItens(condWhere,2);
        }
        free(tabela);
        if(join>0){
        free(tabelaB);
        }
        return cont;
}


char** salvaItens(char* s, int qtd){
char** itens=malloc(sizeof(char)*qtd);
int cont=0,i=3,inicio=3;
while(s[i]!=')' && cont<qtd){
                if(s[i]==','){

                                itens[cont]=copiaString(s,inicio, i);
                                //printf("iten %d=%s", cont, itens[cont]);
                        cont++;
                        inicio=i+1;
                }

                i++;
        }
        itens[cont]=copiaString(s,inicio, i);
return itens;
}


void modificaString(char* s, char* extensao, char* nome){

        strcpy(s, nome);
        strcat(s,extensao);

}




int* pegarGrauCard(char* linha){
        int i=0, inicio=0;
        int *resp= malloc(sizeof(int)*2);
        char* s;
        while(linha[i]!='\n'){
                if(linha[i]==','){
                s=copiaString(linha, inicio,i);
                        resp[0]=atoi(s);

                        inicio=i+1;
                        //break;
                }
                i++;
        }
        s=copiaString(linha, inicio,i);
        resp[1]=atoi(s);

        return resp;
}


int* encontrarAtrib(FILE *tab, int qtd , char* atrib){
        int cont=0, i=0, achou=0, inicio=0;
        char linha[1000];
        int *resp=malloc(sizeof(int)*2);

        fseek(tab, SEEK_SET, 0);
        fgets(linha, sizeof(linha), tab);
        while( cont<qtd && linha!=NULL ){

                        fgets(linha, sizeof(linha), tab);
                        while(i<sizeof(linha)){
                                if(linha[i]==','){
                                if(compara(linha, atrib, inicio, i)){
                                        resp[0]=cont;
                                        achou=1;
                                        if(linha[i+1]=='C'){
                                        resp[1]=0;
                                        }else{
                                        resp[1]=1;
                                        }
                                inicio=i+1;
                                }else{

                                i=1000;

                                }

                                }
                                i++;
                        }
                        i=0;
                        cont++;
        }
        return resp;




}


int salvaSelecao(FILE *tabDados, char* nomeArqSaida, int numLinhas, int pos, int tipo, char num, char* atrib){
        int resp= 0;
        char *valorAt;
        char linha[1000];
                FILE *saida=  fopen(nomeArqSaida,"w");

        int valorAtI,  valorCond, cont=0, i=0, posAtual=0, inicio=0;
while( cont<numLinhas ){
                        //fscanf(tabDados,"%s \n", linha);
                        fgets(linha, sizeof(linha), tabDados);
                        //printf("peguei a linha:%s",linha);


                        while(linha[i]!='\n'){
                                if(linha[i]==','){
                                        if(posAtual==pos){
                                                if(tipo==0){
                                                //printf("\ne charrr primeiro if\n");
                                                        valorAt=copiaString(linha, inicio+1,i-1);
                                                }else{
                                                        valorAt=copiaString(linha, inicio,i);
                                                        valorAtI=atoi(valorAt);
                                                        valorCond=atoi(atrib);
                                                }
                                                if(num=='1'){
                                                if(tipo==0){
                                                                if(strcmp(atrib,valorAt)==0) {fprintf(saida, "%s", linha);
                                                                resp++;
}
                                                        }else{
                                                                if(valorAtI==valorCond){
                                                                fprintf(saida, "%s", linha);
                                                                                                                resp++;


                                                                }
                                                        }
                                                }
                                                if(num=='2'){
                                                if(tipo==0){
                                                                if(strcmp(atrib,valorAt)>0){ fprintf(saida, "%s", linha);
                                                resp++;


                                                                }
                                                        }else{
                                                                if(valorAtI<valorCond){
                                                                fprintf(saida, "%s", linha);
                                                                                                                resp++;


                                                                }
                                                        }
                                                }
                                                if(num=='3'){
                                                if(tipo==0){
                                                        // printf("achei a linha %s\n\n",valorAt);
                                                        if(strcmp(atrib,valorAt)>0 ||   strcmp(atrib,valorAt)==0) {
                                                        fprintf(saida, "%s", linha);
                                                                                                        resp++;
}
                                                }else{

                                                        if(valorAtI<=valorCond){
                                                        fprintf(saida, "%s", linha);
                                                                                                        resp++;
}
                                                }
                                                }
                                                if(num=='4'){
                                                        //printf("e quatrooooo");

                                                if(tipo==0){
                                                        //printf("\ne char!!");
                                                        if(strcmp(atrib,valorAt)<0){
                                                        fprintf(saida, "%s", linha);
                                                                                                        resp++;
}
                                                }else{

                                                        if(valorAtI>valorCond) {
                                                        fprintf(saida, "%s", linha);
                                                                                                        resp++;
}
                                                }

                                                }
                                                if(num=='5'){
                                                if(tipo==0){
                                                        if(strcmp(atrib,valorAt)<0 || strcmp(atrib,valorAt)==0) {
                                                        fprintf(saida, "%s", linha);
                                                resp++;
}
                                                }else{

                                                        if(valorAtI>=valorCond) {
                                                        fprintf(saida, "%s", linha);
                                                                                                        resp++;
}
                                                }
                                                }
                                                if(num=='6'){
                                                if(tipo==0){
                                                                if(strcmp(atrib,valorAt)!=0){
                                                                fprintf(saida, "%s", linha);
                                                resp++;
}
                                                        }else{
                                                                if(valorAtI!=valorCond) {
                                                                fprintf(saida, "%s", linha);
                                                                                                                resp++;
}
                                                        }

                                                }
                                                }

                                posAtual++;
                                inicio=i+1;
                                }
                                i++;
                        }
                        posAtual=0;
                        i=0;
                        cont++;
                        inicio=0;
        }
        free(valorAt);
        fclose(saida);
        return resp;
}


void selecaoOrd(char* inf){
int i =3, inicio=3;


        int cont=0;
        //printf("entrou no selecaodesord\n\n");

        //printf("%s operacao\n", inf);
        char **itens=salvaItens(inf, 4);
        /*
        printf("tabela:%s\n", itens[0]);
        printf("tabela:%s\n", itens[1]);
        printf("tabela:%s\n", itens[2]);
        printf("tabela:%s\n", itens[3]);*/


        char dadosTab[100],  tabela[100], tabSaida[100],dadosTabSaida[100];
        modificaString(dadosTab, ".dad", itens[0]);
        modificaString(tabela, ".ctl", itens[0]);
        modificaString(dadosTabSaida, ".dad", itens[3]);
        modificaString(tabSaida, ".ctl", itens[3]);
        FILE *tab  = fopen(tabela,"r");
        FILE *tabDados  = fopen(dadosTab,"r");
        char linha[1000];

                        fgets(linha, sizeof(linha), tab);
        int *qtds;
        qtds=pegarGrauCard(linha);
        //printf("Tem grau %d  cardinalidade %d \n",qtds[0], qtds[1]);
        //FILE *saida=  fopen(dadosTabSaida,"w");
        //FILE *saidaInf=  fopen(tabSaida,"w");

        i=0;


        cont=0;
        int *posAt=encontrarAtrib(tab, qtds[0], itens[1]);


        //printf("Achou o atributo %s do tipo %d na linha %d\n", itens[1], posAt[1], posAt[0]);


        cont=0;
        int posAtual=0;
        inicio=0;
        i=0;
        char *valorAt;
        int valorAtI,  valorCond;

        //salva as linhas de interesse no arquivo de resposta
        salvaSelecao(tabDados,dadosTabSaida, qtds[0],posAt[0],posAt[1],inf[1],itens[2]);

        /*printf("tabela:%s\n", itens[0]);
        printf("tabela:%s\n", itens[1]);
        printf("tabela:%s\n", itens[2]);

        printf("tabela:%s\n", itens[3]);*/
        free(qtds);
        apagaItens(itens,4);
        fclose(tab);
        fclose(tabDados);

}




void selecaoDesord(char* inf){
        int i =3, inicio=3;


        int cont=0;
        //printf("entrou no selecaodesord\n\n");

        printf("%s operacao\n", inf);
        char **itens=salvaItens(inf, 4);

        printf("tabela:%s\n", itens[0]);
        printf("tabela:%s\n", itens[1]);
        printf("tabela:%s\n", itens[2]);
        printf("tabela:%s\n", itens[3]);



        char dadosTab[100],  tabela[100], tabSaida[100],dadosTabSaida[100];
        modificaString(dadosTab, ".dad", itens[0]);
        modificaString(tabela, ".ctl", itens[0]);
        modificaString(dadosTabSaida, ".dad", itens[3]);
        modificaString(tabSaida, ".ctl", itens[3]);
        FILE *tab  = fopen(tabela,"r");
        FILE *tabDados  = fopen(dadosTab,"r");
        char linha[1000];


                        fgets(linha, sizeof(linha), tab);
        int *qtds;
        qtds=pegarGrauCard(linha);
        //printf("Tem grau %d  cardinalidade %d \n",qtds[0], qtds[1]);
        //FILE *saida=  fopen(dadosTabSaida,"w");


        i=0;


        cont=0;
        int *posAt=encontrarAtrib(tab, qtds[0], itens[1]);


        //printf("Achou o atributo %s do tipo %d na linha %d\n", itens[3], posAt[1], posAt[0]);


        cont=0;
        int posAtual=0;
        inicio=0;
        i=0;
        char *valorAt;
        int valorAtI,  valorCond;

        //salva as linhas de interesse no arquivo de resposta
        int         card=salvaSelecao(tabDados,dadosTabSaida, qtds[0],posAt[0],posAt[1],inf[1],itens[2]);

        printf("tabela:%s\n", itens[0]);
        printf("tabela:%s\n", itens[1]);
        printf("tabela:%s\n", itens[2]);
        printf("tabela:%s\n", itens[3]);
        FILE *saidaInf=  fopen(tabSaida,"w");
       // printf("teeem %d ", card);
        fprintf(saidaInf,"%d,%d\n", qtds[0], card);
        i=0;
        fseek(tab, SEEK_SET,0);
                fgets(linha,sizeof(linha), tab);


        while(i<qtds[0])
        {
        fgets(linha,sizeof(linha), tab);
        fprintf(saidaInf,"%s", linha);
                i++;
        }


                apagaItens(itens,4);
free(qtds);
        fclose(tab);
        fclose(tabDados);
        fclose(saidaInf);

        }





char* pegarValor(char* s, int pos, int tipo){
        int i =0, cont=0,j=0, inicio, achou=0;
        char*resp=malloc(sizeof(char)*20);
        while(s[i]!='\n'){


                if(cont==pos && s[i]!=','){
                        if(tipo==0 && achou==0){
                                i++;
                                resp[j]=s[i];
                                j++;
                                achou=1;
                        }else{
                                resp[j]=s[i];
                                j++;
                        }

                }
                if(s[i]==','){

                cont++;
                }
                i++;
        }
        if(tipo==1){
        resp[j]='\0';
        }else{
        resp[j-1]='\0';
        }
        s[i]='\0';

        return resp;
}
void salvaTabJuncao(char* tabelaA, char* tabelaB,  char* condA, char* condB, char*tabelaJoin, int tipo){
        char dadosTabA[100],  tabA[100],dadosTabB[100],  tabB[100], tabSaida[100],dadosTabSaida[100] ;
        int resp=0;
        modificaString(dadosTabA, ".dad", tabelaA);
        modificaString(tabA, ".ctl", tabelaA);
        modificaString(dadosTabB, ".dad", tabelaB);
        modificaString(tabB, ".ctl", tabelaB);
        modificaString(tabSaida, ".dad", tabelaJoin);
        modificaString(dadosTabSaida, ".ctl", tabelaJoin);
        //if(tipo==1)printf("ta ordenado!!!");
        //modificaString(dadosTabSaida, ".ctl", tabelaB);
        //printf("arquivo: %s\n",tabA);

        FILE *arqTabA  = fopen(tabA,"r");
        FILE *arqTabB  = fopen(tabB,"r");
        FILE *arqTabDadosB = fopen(dadosTabB,"r");
        FILE *arqTabDadosJoin = fopen(tabSaida,"w");
        FILE *arqTabJoin = fopen(dadosTabSaida,"w");
        char linhaA[1000], linhaB[1000];

        fgets(linhaA, sizeof(linhaA), arqTabA);
        //printf("Primeira Linha%s", linhaA);
        int* grauCardA=pegarGrauCard(linhaA);
        fgets(linhaB, sizeof(linhaB), arqTabB);
                //printf("Primeira Linha%s", linhaB);


        int* grauCardB=pegarGrauCard(linhaB);





        int* infA=encontrarAtrib(arqTabA, grauCardA[0], condA);
        int* infB=encontrarAtrib(arqTabB, grauCardB[0], condB);

        //printf("Achou o atributo de tabela1 %s do tipo %d na linha %d\n", condA, infA[1], infA[0]);
        int atualAtI;
        char atualAt;
        int i=0,j=0;

        FILE *arqTabDadosA  = fopen(dadosTabA,"r");
        char *valorA, *valorB;
        int valorAI, valorBI;
        while(i<grauCardA[1]){
fgets(linhaA, sizeof(linhaA), arqTabDadosA);
        //printf("Primeira Linha de dad:%s\n", linhaA);


                valorA=pegarValor(linhaA, infA[0], infA[1]);

        fseek(arqTabDadosB, SEEK_SET, 0);
                while(j<grauCardB[1]){

                        fgets(linhaB, sizeof(linhaB), arqTabDadosB);
                        valorB=pegarValor(linhaB, infB[0], infB[1]);
                                //printf("Primeira Linha de Bdad:%s\n", linhaB);


                        if(infB[1]==1){
                        //e inteiro
                                valorAI=atoi(valorA);
                                valorBI=atoi(valorB);

                                if(valorAI==valorBI){
                                strcat(linhaA,",");
                                        strcat(linhaA, linhaB);
                                        fprintf(arqTabDadosJoin,"%s\n", linhaA);
                                        resp++;
                                        //printf("Salvou  a linha %s\n",  linhaA);
                                }
                        }else{
                                if(infB[1]==0){
                                //printf("valooor%s\n", valorA);
                                //printf("valooordo B%s\n", valorB);
                                //e string
                                if(strcmp(valorA,valorB)==0){
                                        strcat(linhaA, linhaB);
                                        fprintf(arqTabDadosJoin,"%s\n", linhaA);
                                        resp++;
                                        //printf("Salvou  a sting linha %s\n",  linhaA);


                                }

                                }
                        }
                        j++;
                }
                j=0;
                i++;

        }
        //free(grauCardA);
        //free(grauCardB);
//        printf("Cardinalidade:%s\n\n", cardCA);
        i=0;
        fprintf(arqTabJoin,"%d,%d\n", grauCardA[0]+grauCardB[0], resp);
        fseek(arqTabA, SEEK_SET,0);
        fseek(arqTabB, SEEK_SET,0);
                fgets(linhaA,sizeof(linhaA), arqTabA);


        fgets(linhaA,sizeof(linhaA), arqTabB);
char inform[1000]="";
        while(i<grauCardA[0]){

                strcpy(inform, tabelaA);
                strcat(inform,".");
                fgets(linhaA,sizeof(linhaA), arqTabA);
                strcat(inform,linhaA);
                fprintf(arqTabJoin,"%s", inform);
                i++;
        }
        i=0;
        while(i<grauCardB[0]){
        strcpy(inform, tabelaB);
                strcat(inform,".");
                fgets(linhaA,sizeof(linhaA), arqTabB);
        strcat(inform,linhaA);
                fprintf(arqTabJoin,"%s", inform);
                i++;
        }
fclose(arqTabA);
fclose(arqTabB);
fclose(arqTabDadosA);
fclose(arqTabDadosB);
fclose(arqTabDadosJoin);
fclose(arqTabJoin);




}

void juncao(char* inf){
                int i =3, inicio=3;

        int cont=0;
        printf("entrou na JUNCAO\n\n");
        int tipo;
        if(inf[1]=='2'){
                tipo =2;
        }else{
                tipo=1;
        }
        char **itens=salvaItens(inf, 5);

        //printf("tabela:%s\n", itens[0]);
        //printf("tabela:%s\n", itens[1]);
        //printf("tabela:%s\n", itens[2]);
        //printf("tabela:%s\n", itens[3]);
        //printf("tabela:%s\n", itens[4]);

        char **condJuncao = malloc(sizeof(char)*2);
                        int card;


        if(strstr(itens[2], itens[0] )!=NULL){

                condJuncao[0]=removeSubString(itens[2], itens[0]);

                condJuncao[1]=removeSubString(itens[3], itens[1]);
        //printf("\n\nprimeriso tabela %s\n\n", condJuncao[0]);
        salvaTabJuncao(itens[0], itens[1], condJuncao[0], condJuncao[1], itens[4], tipo);

        }else{
                if(strstr(itens[2], itens[1] )!=NULL){
                        condJuncao[0]=removeSubString(itens[2], itens[1]);
                        condJuncao[1]=removeSubString(itens[3], itens[0]);
                        salvaTabJuncao(itens[0], itens[1], condJuncao[1], condJuncao[0], itens[4], tipo);
                }

        }

        /*printf("atributo 1:%s\n", condJuncao[0]);
        printf("atributo 2:%s\n", condJuncao[1]);*/


        apagaItens(itens,5);
        apagaItens(condJuncao,2);

}






int temLinha(FILE *arqTabSaida, char* resultado, int pos){


        int tem=1, i=0;

        fseek(arqTabSaida, SEEK_SET, 0);
        char linha[1000];
        while(i<pos){

                fgets(linha, sizeof(linha), arqTabSaida);
                 if (strcasecmp(linha, resultado) == 0) tem =0;
                i++;
        }
        return tem;
}
void projecao(char* inf){
        int i =3, cont =0, inicio=3;
        while(inf[i]!='\n' && cont!=2){

                if(inf[i]==','){
                if(cont==0)inicio=i+1;
                cont++;
                }
                i++;
        }

        int qtdAt=atoi(copiaString(inf, inicio,i-1));

        ///char **itens=salvaItens(inf, qtdAt+3);
char** itens=malloc(sizeof(char)*(qtdAt+3));
cont=0;
i=3;
inicio=3;
while(inf[i]!=')'){
                if(inf[i]==','){

                                itens[cont]=copiaString(inf,inicio, i);
                                //printf("iten %d=%s", cont, itens[cont]);
                        cont++;
                        inicio=i+1;
                }

                i++;
        }
        itens[cont]=copiaString(inf,inicio, i);
                        //printf("estou na linha: %s \n\n", itens[0]);
        //printf("PROJECAO qtd:%d\n", qtdAt);
        char dadosTab[100],  tab[100], tabSaida[100],tabDadosSaida[100];


        modificaString(dadosTab, ".dad", itens[0]);
        modificaString(tab, ".ctl", itens[0]);
        modificaString(tabSaida, ".dad", itens[qtdAt+2]);
        modificaString(tabDadosSaida, ".ctl", itens[qtdAt+2]);
                                //printf("estooooou :::: %s \n\n", tabSaida);



        FILE *arqTab  = fopen(tab,"r");
        FILE *arqTabDados = fopen(dadosTab,"r");
        FILE *arqTabSaida = fopen(tabSaida,"w+");
        FILE *arqTabDadosSaida = fopen(tabDadosSaida,"w");

        char linhaA[1000];

        fgets(linhaA, sizeof(linhaA), arqTab);


        int* grauCardA=pegarGrauCard(linhaA);
        printf("%d\n", grauCardA[0]);
        int pos=0;
        int j=0;
        int* posAt[qtdAt];
        while(pos<qtdAt){
        //printf("ooooooooi");
                posAt[pos]=encontrarAtrib(arqTab, grauCardA[0], itens[2+pos]);
                //fprintf(arqTabSaida,"Atributo  %s na posicao %d", itens[2+pos], posAt[pos][0]);
        pos++;

        }
        i=0;
        char* valorAt[qtdAt];
        char resultado[1000]="";
        int posRes=0;

        while(i<grauCardA[1]){

        fgets(linhaA, sizeof(linhaA), arqTabDados);

                //printf("estou na linha: %s \n\n", linhaA);
                while(j<qtdAt){
                        valorAt[j]=pegarValor(linhaA, posAt[j][0],1);
                        strcat(resultado, valorAt[j]);
                        //fprintf(arqTabSaida,"%s", valorAt[j]);

                        j++;
                        if(j!=qtdAt){
                        strcat(resultado, ",");
                        //fprintf(arqTabSaida,",");
                        }
                }
                if(inf[1]=='2'){
                                        if(temLinha(arqTabSaida, resultado, posRes)==1){
                                                                                strcat(resultado,"\n");
                                        fprintf(arqTabSaida,"%s", resultado);
                                        posRes++;
                                        }
                                        }else{
                                                                        strcat(resultado,"\n");
                                        fprintf(arqTabSaida,"%s", resultado);
                                        posRes++;
                                        }
        strcpy(resultado,"");
                //fprintf(arqTabSaida,"\n");
                j=0;
                i++;
        }
                                        /*        fprintf(arqTabDadosSaida,"%d,%d\n",qtdAt, posRes);
                                                j=0;
                                                fseek(arqTab, SEEK_SET,0);
                                                        fgets(linhaA, sizeof(linhaA), arqTab);

                                                while(j<qtdAt &&  j<grauCardA[0]){
                                                                                                        fgets(linhaA, sizeof(linhaA), arqTab);



                                                        if(strstr(linhaA, itens[qtdAt] )!=NULL){
                                                        printf("\nENTROU\n");

                                                        fprintf(arqTabDadosSaida,"%s",linhaA);

                                                                j++;

                                                                }
                                                        if(j==1){
                                                        if(strstr(linhaA, itens[qtdAt+1] )!=NULL){
                                                        printf("\nENTROU\n");

                                                        fprintf(arqTabDadosSaida,"%s",linhaA);

                                                                j++;

                                                                }
                                                                }

                                                }*/


        fclose(arqTab);
        fclose(arqTabDadosSaida);
        fclose(arqTabDados);
        fclose(arqTabSaida);







}
void executaSelect(FILE *op){
        char inf[1000];
        fseek(op, SEEK_SET, 0);
        while(fgets(inf, sizeof(inf), op)!=NULL){

        //printf("ooooi %s\n\n", inf);
        if(inf[0]=='S'){
                selecaoDesord(inf);
        }
        if(inf[0]=='O'){
                selecaoDesord(inf);
        }
        if(inf[0]=='J'){
                juncao(inf);
        }
        if(inf[0]=='P'){
                projecao(inf);
        }
        }
}


void SELECT( char * comando ){
        FILE *opAlg = fopen("opAlg.alg","w");
         //fprintf(opAlg, "testeeeeeeeee");
    char sql[1000]= "SELECT tab.a,tabb.bx FROM tab JOIN tabb ON tab.a=tabb.bx where tab.bx>20;";

   int tipo = Insert(comando, opAlg);
   //printf("tipo%d", tipo);
        fclose(opAlg);
        opAlg= fopen("opAlg.alg","r");
        executaSelect(opAlg);
        fclose(opAlg);
}

