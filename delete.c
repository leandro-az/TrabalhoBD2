#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int quant_arg_D;
char *nome_arq_tabela_atributos_D;
char *nome_arq_tabela_dados_D;
int tamanho_do_nome_tab_D;
int pos_cursor_na_frase_D;
int tamanho_do_nome_do_arg_D;

typedef struct letra{
   char ch;
   struct letra *prox;
}LL;

typedef struct lista_de_palavras{
      char *letras;
      struct lista_de_palavras  *prox;
}LP;

LL *cria_PL(){
LL *novo=(LL*)malloc(sizeof(LL));

return novo;
}

LP *cria_LP(){

 LP *novo= (LP*)malloc(sizeof(LP));

 return novo;
}
LL *insere_letra(LL *p,char c){



    if(p==NULL){
        LL *nova=cria_PL();
        nova->ch=c;
        nova->prox=NULL;
        return nova;
    }else{
       p->prox=insere_letra(p->prox,c);
       return p;
    }

}
LP *insere_Palavras_D(LP *lp, char *palavra){

    if(lp==NULL){

            LP *novo=cria_LP();
            //printf("%s\n",palavra);
            novo->letras=(char*)malloc(sizeof(char)*(strlen(palavra)));
            strcpy(&novo->letras,&palavra);
            novo->prox=NULL;

            return novo;


    }else{

          lp->prox=insere_Palavras_D(lp->prox,palavra);
          return lp;
    }

}
int retorna_tamanho_de_palavra_D(LL *p){

    if(p==NULL){
        return 0;
    }else{
       return ( 1 + retorna_tamanho_de_palavra_D(p->prox));
    }

}
char *retorna_palavra_D(LL *p){
  int tam= 1+ retorna_tamanho_de_palavra_D(p);
   char *resp=(char*)malloc(sizeof(char)*tam);
   int i=0;
   LL *aux=p;
   while(aux!=NULL){
     resp[i]=aux->ch;
     aux=aux->prox;
     i=i+1;
   }
   resp[i]='\0';

   return resp;
}
char *recupera_nome_tabela_D(char *cmd){

int i=12;
int f=12;
char c=cmd[i];
while(c!=' '){
    c=cmd[f];
    f=f+1;
}

tamanho_do_nome_tab_D=f-i;

char *nome_t=(char*)malloc(sizeof(char)*(tamanho_do_nome_tab_D));
int j=0;
int k;
for(k=i;k<f-1;k++){
    nome_t[j]=cmd[k];
    j=j+1;
}
nome_t[j]='\0';

return nome_t;

}
int verifica_se_existem_tabelas_D(char *nome_ta){

    nome_arq_tabela_atributos_D=(char*)malloc(sizeof(char)*(strlen(nome_ta)+4));
    nome_arq_tabela_dados_D=(char*)malloc(sizeof(char)*(strlen(nome_ta)+4));

    strcpy(nome_arq_tabela_dados_D,nome_ta);
    strcat(nome_arq_tabela_dados_D,".dad");

    strcpy(nome_arq_tabela_atributos_D,nome_ta);
    strcat(nome_arq_tabela_atributos_D,".ctl");



     FILE *in2=fopen(nome_arq_tabela_dados_D,"r");
     FILE *in=fopen(nome_arq_tabela_atributos_D,"r");

     fscanf(in,"%d",&quant_arg_D);

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

void atualiza_quantidade_de_dados_na_de_info_D(){

FILE *out=fopen(nome_arq_tabela_atributos_D,"r");
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
contador=contador-1;

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

out=fopen(nome_arq_tabela_atributos_D,"w");
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
char *recupera_argumento_D(char *cmd){





    while(cmd[pos_cursor_na_frase_D]=='"' || cmd[pos_cursor_na_frase_D]==' ' || cmd[pos_cursor_na_frase_D]==',' || cmd[pos_cursor_na_frase_D]=='(' || cmd[pos_cursor_na_frase_D]=='='  ){
        pos_cursor_na_frase_D=pos_cursor_na_frase_D+1;
    }
    int f = pos_cursor_na_frase_D;

    char c = cmd[f];


    while(c!=',' && c!=')' && c!='"' && c!='='){

        c=cmd[f];
        f=f+1;
    }


tamanho_do_nome_do_arg_D=f-pos_cursor_na_frase_D;

char *nome_arg=(char*)malloc(sizeof(char)*(tamanho_do_nome_do_arg_D));
int j=0;
int k;
for(k=pos_cursor_na_frase_D;k<f-1;k++){
    nome_arg[j]=cmd[k];
    j=j+1;
}
nome_arg[j]='\0';
pos_cursor_na_frase_D=f;

return nome_arg;

}


int verifica_pos_do_atributo(char *at){



FILE *in=fopen(nome_arq_tabela_atributos_D,"r");
int contador=1;
char c='a';
// Pula a primeira linha do arquivo
while(c!='\n'){
    fscanf(in,"%c",&c);
}


char *atributo=(char*)malloc(sizeof(char)*50);

int j=0;
while(fscanf(in,"%c",&c)!=EOF){
               if(c==','){
                atributo[j]='\0';
                 j=0;

                   if(strcmp(atributo,at)!=0){
                        contador=contador+1;
                    }else{
                               fclose(in);
                               return contador;
                            }
                               // vai pra linha seguinte-------------------------------------------------------
                              while(fscanf(in,"%c",&c)!=EOF){
                              if(c=='\n')
                              break;
                              }
                                 free(atributo);
                                atributo=(char*)malloc(sizeof(char)*50);

           }else{
                 atributo[j]=c;
                 j=j+1;


           }

}


fclose(in);
return contador;
}
LP *le_linha(FILE *in){
       LL *p=NULL;
       LP *lis_resp=NULL;
       char c='a';
      while(fscanf(in,"%c",&c)!=EOF){
         if(c!=',' && c!='\n'){

            p=insere_letra(p,c);
         }else{
         if(c==','){

            //char *palav=retorna_palavra_D(p);
            lis_resp=insere_Palavras_D(lis_resp,retorna_palavra_D(p));
            //printf("%s",retorna_palavra_D(p));
            p=NULL;

         }else{
             if( c=='\n'){
            lis_resp=insere_Palavras_D(lis_resp,retorna_palavra_D(p));
           //printf("%s",retorna_palavra_D(p));
                 }
                 break;
             }
           }
    }

    return lis_resp;
}
int verifica_se_linha_tem_valor_D(LP *linha,int resp,char *valor_do_atributo){
   if(resp==0){
  if(linha==NULL){

    return 0;
  }else{

     if(strcmp(linha->letras,valor_do_atributo)==0){
        return 1;

            }else{

              return 0;
           }

          }
      }else{

       return verifica_se_linha_tem_valor_D(linha->prox,resp-1,valor_do_atributo);
      }
}
void salva_linha_D(FILE *out,LP *l){
   LP *aux=l;
    while(aux!=NULL){
        //printf("%s",aux->letras);
        fprintf(out,"%s",aux->letras);
        if(aux->prox!=NULL){
        fprintf(out,",");
        }
        aux=aux->prox;
}
       fprintf(out,"\n");
}
void DELETE( char *comando){


char *nome_tab=recupera_nome_tabela_D(comando);


//Delete from tabela where nome="Victor";;

pos_cursor_na_frase_D=11+tamanho_do_nome_tab_D+7;
//coloca o ponteiro para comecar a ler o argumento -------------------------------------------------------------------------------------



if(verifica_se_existem_tabelas_D(nome_tab)){

            char c;
            char *atributo;
            atributo=recupera_argumento_D(comando);

            char *valor_do_atributo;

            pos_cursor_na_frase_D=11+tamanho_do_nome_tab_D+7;
             while(comando[pos_cursor_na_frase_D]!='='){
                   pos_cursor_na_frase_D=pos_cursor_na_frase_D+1;
                       }
                     pos_cursor_na_frase_D=pos_cursor_na_frase_D+1;
                   valor_do_atributo=recupera_argumento_D(comando);


            int resp=verifica_pos_do_atributo(atributo);


            FILE *in=fopen(nome_arq_tabela_dados_D,"r");
            FILE *out=fopen("temporario.txt","w");

             LP *lista_p=le_linha(in);

             while(lista_p!=NULL){

               if(verifica_se_linha_tem_valor_D(lista_p,resp-1,valor_do_atributo)!=1){
                salva_linha_D(out,lista_p);
               }
                lista_p=le_linha(in);
             }

            fclose(in);
            fclose(out);

            out=fopen(nome_arq_tabela_dados_D,"w");
            in=fopen("temporario.txt","r");


             while(fscanf(in,"%c",&c)!=EOF){
                   fprintf(out,"%c",c);
               }




            fclose(in);
            fclose(out);

            remove("temporario.txt");



}


  atualiza_quantidade_de_dados_na_de_info_D();

}

