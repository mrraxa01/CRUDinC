/* BIBLIOTECA QUE MANIPULA OS DADOS SALVANDO EM UM ARQUIVO */
#include <stdio.h>
#include "model.h"
#include "views.h"

/* DEFINE O NOME DO ARQUIVO ONDE OS DADOS SERÃO SALVOS*/
#define ARQ "Dados.dat"
/*DEFINE UM PONTEIRO PARA O ARQUIVO. COM ESSA DECLARAÇÃO GLOBAL PODEMOS ACESSAR O ARQUIVO DENTRO DE QUALQUER FUNÇÃO*/
FILE *fp;

/*
    A FUNÇÃO INICIA VAI VERIFICAR SE O ARQUIVO JÁ EXISTE, SE EXISTIR VAI ABRIR NO MODO LEITURA E ESCRITA, SE NÃO
    EXISTIR VAI CRIAR O ARQUIVO
*/
void Inicia() {
  fp = fopen(ARQ, "r+b"); // tentar abrir
  if (fp == NULL) {
    fp = fopen(ARQ, "w+b"); // criar o arquivo
    if (fp == NULL) {
      printf(" Erro fatal: impossível criar arquivo de dados\n");
      exit(1);
    }
  }
}

/*
    AS FUNÇÕES A SEGUIR ADICIONAM UM NOTA AO REGISTRO
*/

void Inserir_Nota() {
  Nota novaNota;
  //A FUNCAO LER NOTA VAI LER OS DADOS INSERIDOS PELO USUÁRIO, COMO TUDO RELACIONADO A TELA ESTARÁ NA BIBLIOTECA VIEWS
  Ler_Nota(&novaNota);
  Adiciona_Nota(novaNota);
  Listar();
}

void Adiciona_Nota(Nota n) {
  fseek(fp, 0L, SEEK_END);
  if (fwrite(&n, sizeof(n), 1, fp) != 1)
    Mensagem("Adicionar nota: Falhou a escrita do registro");
}

/* FUNÇÃO PARA APAGAR UM REGISTRO */

void Apagar_Nota(){
    limparTela();
    Nota n;
    long int n_reg;
    char resp;

    printf("Qual o numero do registro: ");
    scanf("%ld", & n_reg); fflush(stdin);
    if(fseek(fp, (n_reg - 1)*sizeof(Nota), SEEK_SET)!= 0){
        Mensagem("Registro inexistente ou problemas no registro!!!");
        return;
    }
    if(fread(&n, sizeof(Nota), 1, fp)!= 1){
        Mensagem("Problema na leitura do registro!!!");
        return;
    }
    if(n.status=='*'){
        Mensagem("Registro já está apagado!!!\n\n");
    }
    printf("\n\n Dados atuais: \n\n");
    printf("Apagar nota no valor de R$ %.2f do dia %s de %s ?", n.valor, n.data, n.tecnico);
    printf("\n\n Apagar o registro (s/n)???: "); resp = getchar();
    fflush(stdin);
    if(toupper(resp)!= 'S')Listar();

    n.status= '*';
    // recuar um registro no arquivo
    fseek(fp, -(long) sizeof(Nota), SEEK_CUR);
    // reescrever o registro;
    fwrite(&n, sizeof(Nota), 1, fp);
    fflush(fp); /*Despejar os arquivos no disco rígido*/
    Listar();
}

/* A FUNÇÃO DE LISTAR VAI LER OS DADOS SALVOS NO ARQUIVO E EXIBIR NA TELA */

void Listar(){
    limparTela();
    int i =0;
    Nota notasSalvas[1024];
    long int n_Linhas = 0;
    Nota reg;
    rewind(fp);
    while(1){
        if(fread(&reg, sizeof(reg), 1, fp)!= 1)break; /*Sair do laço*/

        if(reg.status=='*') continue; /*Passa ao próximo*/
        n_Linhas++;
        notasSalvas[i] = reg;
        i++;
        if(n_Linhas%20==0)
            Mensagem("Pressione <Enter> para continuar .  .  .");
    }
    //A FUNÇÃO MOSTRAR_NOTA RECEBE UM ARRAY COM AS NOTAS LIDAS DO ARQUIVO E EXIBE NA TELA, O i é a qtdade de notas salvas
    Mostrar_Nota(notasSalvas, i);


}
/* FUNÇÃO AUXILIAR QUE EXIBE UMA MENSAGEM NA TELA */
void Mensagem(char *msg) {
  printf("%s", msg);
  getchar();
}
