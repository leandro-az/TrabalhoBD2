#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//Degree of the relation
int degree(char * text,int size)
{
    int i , total = 0;
    for( i = 0; i < size; i++)
        if(text[i]== ',') total++;
    if(total > 0)total++;
    return total;
}

//Makes the hole string upper case
void upperCase(char * text)
{
    int i = 0;
    while(text[i])
    {
        text[i] = toupper(text[i++]);
    }
}
char * make(char * str , int ini, int j)
{
    if(!str)return;
    int total = (j - ini) +1;
    int h = 0;

    char * aux = (char*)malloc(sizeof(char)*total);
    for( h=0 ; h<total;h++)
    {
        aux[h] = str[ini+h];
    }aux[h]='\0';
    return aux;
}
//get the next word from the text
char * nextWord(char * text , int i )
{
    int upper = 0;
    if(i == 13)upper = 1;
    char *novo = (char*)malloc(sizeof(char)*100);
    int a = 0;
    while(text[i]!=' ' && text[i]!=')' && text[i]!=',' && text[i]!='('){
        if(upper){
            novo[a++] = (toupper(text[i++]));
        }
        else{
            novo[a++] = text[i++];
        }
    }
    novo[a]='\0';
    return novo;
}
//Get the name of the colum and the type associated with it
void getColum(char ** values , int position , char * text )
{
    int i = 0;
    char * var;

    while(text[i]!='(')i++;i++;
    while(text[i]==' ')i++;

    int startName = i;//position of the first character for the colum
    int currPos = 0;

    //finding the correct position on the sql command
    while(currPos != position)
    {
        if(text[i] ==',')
        {
            currPos++;
            do{i++;}while(text[i]==' ');
            startName = i;
        }
        else i++;
    }

    while(text[i]!=' ' && text[i]!=')')i++;
    values[1] = make(text,startName,i-1);

    do{i++;}while(text[i]==' ');
    int ini = i;
    do{i++;}while(text[i]!=',' && text[i]!=')' && text[i]!=' ');
    int end = i -1;

    values[0] = make(text,ini,end);

    int curr = 2,a = 0;
    while(text[i] == ' ' && text[i+1] != ')' && text[i+1]!=','){
        i++;
        char * elemento = (char*)malloc(sizeof(char)*100);
        a = 0;
        while(text[i]!=' ' && text[i]!=')' && text[i]!=','){
            elemento[a++] = text[i++];
        }
        elemento[a]='\0';
        values[curr++] = elemento;
    }
    return;

}
void CREATE(char * sql)
{
    char spc = ',' , line ='\n' , pt = ':';
    char * tableName = nextWord(sql,13); //name of the table
    char extdad[100];//arquivo de extensao .dad
    strcpy(extdad,tableName);

    FILE * file = fopen(strcat(tableName,".ctl"),"w+b");
    FILE * dad = fopen(strcat(extdad,".dad"),"w+b");
    fclose(dad);

    //finding the degree of the relation and the cardinilaty
    int deg = degree(sql,strlen(sql));
    char card = '0';
    char n[32];
    sprintf(n,"%d",deg);

    //writing the information formated on the file
    fwrite(&n,sizeof(char)*strlen(n),1,file);
    fwrite(&spc,sizeof(char),1,file);
    fwrite(&card,sizeof(char),1,file);
    fwrite(&line,sizeof(char),1,file);

    int i = 0;
    char ** values = (char**)malloc(sizeof(char*)*7);


    //Reading each argument for the create table and writing on the file
    for( i =0; i<deg; i++)
    {
        getColum(values,i,sql);
        fwrite(values[0],sizeof(char)*strlen(values[0]),1,file);
        fwrite(&spc,sizeof(char),1,file);
        free(values[0]);

        fwrite(values[1],sizeof(char)*strlen(values[1]),1,file);
        free(values[1]);

        int x = 2;
        while(values[x]){
            if(x==5){
                fwrite(&pt,sizeof(char),1,file);
            }
            else{
              fwrite(&spc,sizeof(char),1,file);
            }
            fwrite(values[x],sizeof(char)*strlen(values[x]),1,file);

            free(values[x]);
            values[x++] = NULL;
        }
        fwrite(&line,sizeof(char),1,file);

    }
    fclose(file);

}


