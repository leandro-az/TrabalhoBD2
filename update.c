//selects the items solicited
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int quant_arg_U;
char *nome_arq_tabela_atributos_U;
char *nome_arq_tabela_dados_U;
int tamanho_do_nome_tab_U;
int pos_cursor_na_frase_U;
int tamanho_do_nome_do_arg_U;

typedef struct letra_U{
   char ch;
   struct letra_U *prox;
}LL_U;

typedef struct lista_de_palavras_U{
      char *letras;
      struct lista_de_palavras_U  *prox;
}LP_U;

LL_U *cria_LL_U(){
LL_U *novo=(LL_U*)malloc(sizeof(LL_U));

return novo;
}

LP_U *cria_LP_U(){

 LP_U *novo= (LP_U*)malloc(sizeof(LP_U));

 return novo;
}
LL_U *insere_letra_U(LL_U *p,char c){



    if(p==NULL){
        LL_U *nova=cria_LL_U();
        nova->ch=c;
        nova->prox=NULL;
        return nova;
    }else{
       p->prox=insere_letra_U(p->prox,c);
       return p;
    }

}
LP_U *insere_Palavras_U(LP_U *lp, char *palavra){

    if(lp==NULL){

            LP_U *novo=cria_LP_U();
            //printf("%s\n",palavra);
            novo->letras=(char*)malloc(sizeof(char)*(strlen(palavra)));
            strcpy(&novo->letras,&palavra);
            novo->prox=NULL;

            return novo;


    }else{

          lp->prox=insere_Palavras_U(lp->prox,palavra);
          return lp;
    }

}
int retorna_tamanho_de_palavra_U(LL_U *p){

    if(p==NULL){
        return 0;
    }else{
       return ( 1 + retorna_tamanho_de_palavra_U(p->prox));
    }

}
char *retorna_palavra_U(LL_U *p){
  int tam= 1+ retorna_tamanho_de_palavra_U(p);
   char *resp=(char*)malloc(sizeof(char)*tam);
   int i=0;
   LL_U *aux=p;
   while(aux!=NULL){
     resp[i]=aux->ch;
     aux=aux->prox;
     i=i+1;
   }
   resp[i]='\0';

   return resp;
}
char *recupera_nome_tabela_U(char *cmd){

int i=6;
int f=6;
char c=cmd[i];
while(c!=' '){
    c=cmd[f];
    f=f+1;
}

tamanho_do_nome_tab_U=f-i;

char *nome_t=(char*)malloc(sizeof(char)*(tamanho_do_nome_tab_U));
int j=0;
int k;
for(k=i;k<f-1;k++){
    nome_t[j]=cmd[k];
    j=j+1;
}
nome_t[j]='\0';

return nome_t;

}
int verifica_se_existem_tabelas_U(char *nome_ta){

    nome_arq_tabela_atributos_U=(char*)malloc(sizeof(char)*(strlen(nome_ta)+4));
    nome_arq_tabela_dados_U=(char*)malloc(sizeof(char)*(strlen(nome_ta)+4));

    strcpy(nome_arq_tabela_dados_U,nome_ta);
    strcat(nome_arq_tabela_dados_U,".dad");

    strcpy(nome_arq_tabela_atributos_U,nome_ta);
    strcat(nome_arq_tabela_atributos_U,".ctl");



     FILE *in2=fopen(nome_arq_tabela_dados_U,"r");
     FILE *in=fopen(nome_arq_tabela_atributos_U,"r");

     fscanf(in,"%d",&quant_arg_U);

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

void atualiza_quantidade_de_dados_na_de_info_U(){

FILE *out=fopen(nome_arq_tabela_atributos_U,"r");
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

out=fopen(nome_arq_tabela_atributos_U,"w");
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
char *recupera_argumento_U(char *cmd){





    while(cmd[pos_cursor_na_frase_U]=='"' || cmd[pos_cursor_na_frase_U]==' ' || cmd[pos_cursor_na_frase_U]==',' || cmd[pos_cursor_na_frase_U]=='(' || cmd[pos_cursor_na_frase_U]=='='  ){
        pos_cursor_na_frase_U=pos_cursor_na_frase_U+1;
    }
    int f = pos_cursor_na_frase_U;

    char c = cmd[f];


    while(c!=',' && c!=')' && c!='"' && c!='=' && c!=' '){

        c=cmd[f];
        f=f+1;
    }


tamanho_do_nome_do_arg_U=f-pos_cursor_na_frase_U;

char *nome_arg=(char*)malloc(sizeof(char)*(tamanho_do_nome_do_arg_U));
int j=0;
int k;
for(k=pos_cursor_na_frase_U;k<f-1;k++){
    nome_arg[j]=cmd[k];
    j=j+1;
}
nome_arg[j]='\0';
pos_cursor_na_frase_U=f;

return nome_arg;

}


int verifica_pos_do_atributo_U(char *at){



FILE *in=fopen(nome_arq_tabela_atributos_U,"r");
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
LP_U *le_linha_U(FILE *in){
       LL_U *p=NULL;
       LP_U *lis_resp=NULL;
       char c='a';
      while(fscanf(in,"%c",&c)!=EOF){
         if(c!=',' && c!='\n'){

            p=insere_letra_U(p,c);
         }else{
         if(c==','){

            //char *palav=retorna_palavra_D(p);
            lis_resp=insere_Palavras_U(lis_resp,retorna_palavra_U(p));
            //printf("%s",retorna_palavra_D(p));
            p=NULL;

         }else{
             if( c=='\n'){
            lis_resp=insere_Palavras_U(lis_resp,retorna_palavra_U(p));
           //printf("%s",retorna_palavra_D(p));
                 }
                 break;
             }
           }
    }

    return lis_resp;
}
int verifica_se_linha_tem_valor_U(LP_U *linha,int resp,char *valor_do_atributo){
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

       return verifica_se_linha_tem_valor_U(linha->prox,resp-1,valor_do_atributo);
      }
}
void altera_valor(LP_U *lista_p,int resp,char *valor_do_atributo){

 if(resp==0){
  if(lista_p==NULL){

    return ;
  }else{
       lista_p->letras=(char*)malloc(sizeof(char)*strlen(valor_do_atributo));
       strcpy(lista_p->letras,valor_do_atributo);
       return;
      }
}else{

        altera_valor(lista_p->prox,resp-1,valor_do_atributo);
      }
}

void salva_linha_U(FILE *out,LP_U *l){

   LP_U *aux=l;
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
void UPDATE( char *comando){


pos_cursor_na_frase_U=6;
char *nome_tab=recupera_argumento_U(comando);


//update ALUNO set nome="Ronaldo" where nome="Victor";;

pos_cursor_na_frase_U=5+strlen(nome_tab)+6;
//coloca o ponteiro para comecar a ler o argumento -------------------------------------------------------------------------------------



if(verifica_se_existem_tabelas_U(nome_tab)){
      // o que vai mudar pega aqui ---------------------------------------------------------------------
            char c;
            char *atributo;
            atributo=recupera_argumento_U(comando);

            char *valor_do_atributo;

            pos_cursor_na_frase_U=5+strlen(nome_tab)+6;
             while(comando[pos_cursor_na_frase_U]!='='){
                   pos_cursor_na_frase_U=pos_cursor_na_frase_U+1;
                       }
                     pos_cursor_na_frase_U=pos_cursor_na_frase_U+1;
                   valor_do_atributo=recupera_argumento_U(comando);


            int resp=verifica_pos_do_atributo_U(atributo);

// onde vai mudar pega aqui -------------------------------------------------------------------------------------------------------------------------------------
            char *atributo2;
            pos_cursor_na_frase_U=pos_cursor_na_frase_U+7;
            atributo2=recupera_argumento_U(comando);

            char *valor_do_atributo2;

            pos_cursor_na_frase_U=11+strlen(nome_tab)+5+strlen(atributo)+strlen(valor_do_atributo)+8;

             while(comando[pos_cursor_na_frase_U]!='='){
                   pos_cursor_na_frase_U=pos_cursor_na_frase_U+1;
                       }
                     pos_cursor_na_frase_U=pos_cursor_na_frase_U+1;
                   valor_do_atributo2=recupera_argumento_U(comando);


             int resp2=verifica_pos_do_atributo_U(atributo2);


            FILE *in=fopen(nome_arq_tabela_dados_U,"r");
            FILE *out=fopen("temporario.txt","w");

             LP_U *lista_p=le_linha_U(in);

             while(lista_p!=NULL){

               if(verifica_se_linha_tem_valor_U(lista_p,resp2-1,valor_do_atributo2)!=1){
                salva_linha_U(out,lista_p);
               }else{
                 altera_valor(lista_p,resp-1,valor_do_atributo);
                 salva_linha_U(out,lista_p);
               }
                lista_p=le_linha_U(in);
             }

            fclose(in);
            fclose(out);

            out=fopen(nome_arq_tabela_dados_U,"w");
            in=fopen("temporario.txt","r");


             while(fscanf(in,"%c",&c)!=EOF){
                   fprintf(out,"%c",c);
               }




            fclose(in);
            fclose(out);

            remove("temporario.txt");



}

}
