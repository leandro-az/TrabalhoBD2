#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int quant_arg;
char *nome_arq_tabela_arg;
char *nome_arq_tabela_dados;
int tamanho_do_nome_tab;
int pos_cursor_na_frase;
int tamanho_do_nome_do_arg;

char *recupera_argumento(char *cmd){


    while(cmd[pos_cursor_na_frase]=='"' || cmd[pos_cursor_na_frase]==',' || cmd[pos_cursor_na_frase]=='(' ){
        pos_cursor_na_frase=pos_cursor_na_frase+1;
    }
    int f = pos_cursor_na_frase;

    char c = cmd[f];


    while(c!=',' && c!=')' && c!='"'){

        c=cmd[f];
        f=f+1;
    }


tamanho_do_nome_do_arg=f-pos_cursor_na_frase;
//insert into tabela values ("valor1",NULLO,"valor2");
char *nome_arg=(char*)malloc(sizeof(char)*(tamanho_do_nome_do_arg));
int j=0;
int k;
for(k=pos_cursor_na_frase;k<f-1;k++){
    nome_arg[j]=cmd[k];
    j=j+1;
}
nome_arg[j]='\0';
pos_cursor_na_frase=f;

return nome_arg;

}


char *recupera_nome_tabela(char *cmd){
int i=12;
int f=12;
char c=cmd[i];
while(c!=' '){
    c=cmd[f];
    f=f+1;
}

tamanho_do_nome_tab=f-i;

char *nome_t=(char*)malloc(sizeof(char)*(tamanho_do_nome_tab));
int j=0;
int k;
for(k=i;k<f-1;k++){
    nome_t[j]=cmd[k];
    j=j+1;
}
nome_t[j]='\0';

return nome_t;

}

void atualiza_quantidade_de_dados_na_de_info(){

FILE *out=fopen(nome_arq_tabela_arg,"r");
FILE *out2=fopen("temporario.txt","w");
// salva a cardinalidade e a virgula
char aux;
fscanf(out,"%c",&aux);
fprintf(out2,"%c",aux);

fscanf(out,"%c",&aux);
fprintf(out2,"%c",aux);
//-----------------------------------------------



//fread(aux,sizeof(char),1,out);
//fread(aux,sizeof(char),1,out);
//fread(&contador,sizeof(int),1,out);

//altera a cardinalidade;-------------------------------------
int contador;
fscanf(out,"%d",&contador);
contador=contador+1;

fprintf(out2,"%d",contador);
//fscanf(out,"%c",&aux);
//fprintf(out2,"%c",aux);
//---------------------------------------------------------------

//termina de copiar para o temporario-------------------------------------------
while(fscanf(out,"%c", &aux)!=EOF){
    fprintf(out2,"%c",aux);
}

fclose(out);
fclose(out2);
//--------------------------------------------------------------------------------


//copia do temporario de volta para o original e deleta o temporario ---------------------------

out=fopen(nome_arq_tabela_arg,"w");
out2=fopen("temporario.txt","r");

while(fscanf(out2,"%c", &aux)!=EOF){
    fprintf(out,"%c",aux);
}

fclose(out);
fclose(out2);
remove("temporario.txt");


//fscanf(out,"%c",&aux);
//fscanf(out,"%c",&aux);
//fread(aux,sizeof(char),1,out);
//fread(aux,sizeof(char),1,out);
//fwrite(&contador,sizeof(int),1,out);

}

int verifica_se_existem_tabelas(char *nome_ta){
    nome_arq_tabela_arg=(char*)malloc(sizeof(char)*(strlen(nome_ta)+4));
    nome_arq_tabela_dados=(char*)malloc(sizeof(char)*(strlen(nome_ta)+4));

    strcpy(nome_arq_tabela_dados,nome_ta);
    strcat(nome_arq_tabela_dados,".dad");

    strcpy(nome_arq_tabela_arg,nome_ta);
    strcat(nome_arq_tabela_arg,".ctl");



     FILE *in2=fopen(nome_arq_tabela_dados,"r");
     FILE *in=fopen(nome_arq_tabela_arg,"r");

     fscanf(in,"%d",&quant_arg);

     if(in==NULL || in2==NULL){
      fclose(in2);
      fclose(in);
      return 0;
     }else{
       fclose(in2);
       fclose(in);
       return 1;
     }

}

void INSERT(char *comando){
    int i;
    char *nome_tab=recupera_nome_tabela(comando);

    //coloca o ponteiro para comecar a ler o argumento -------------------------------------------------------------------------------------
    pos_cursor_na_frase=11+tamanho_do_nome_tab+9;

    if(verifica_se_existem_tabelas(nome_tab)){
        FILE *saida=fopen(nome_arq_tabela_dados,"a+");
        char *argumento;
        for(i=0;i<quant_arg;i++){
            //aqui estou escrevendo no arquivo de dados para alterar o formado da gravacao mecher nas linhas a seguir ------------------------------------------
            argumento=recupera_argumento(comando);
            fprintf(saida,"%s",argumento);

            if(i!=quant_arg-1)
                fprintf(saida,",");
            }

        fprintf(saida,"\n");
        fclose(saida);
    }
    atualiza_quantidade_de_dados_na_de_info();
}


