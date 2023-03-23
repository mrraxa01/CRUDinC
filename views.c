#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "model.h"
#include "database.h"


void limparTela(){
    system("cls");
}

void telaInicial(){
printf("\n\n\n\n\n\n\n");
printf("\t\t\t-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x--x-x-x-x\n\n");
printf("\t\t\tx-x-x-x-x-x-x-x-x-x       BEM VINDO AO CADASTRO DE NOTAS    -x-x--x-x-x-x-x-x-x-x\n\n");
printf("\t\t\tx-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x--x-x-\n\n");
printf("\n\n\n\n\n\n\n");
printf("\t\t\tPRESSIONE QUALQUER TECLA PARA INICIAR ...");
getchar();
Inicia();
limparTela();
Listar();

}

void menuOpcoes(){
    setlocale(LC_ALL, "Portuguese.Brazil");
    printf("\n\n");
    printf("\t\t______________________________________________________________________________________\n");
    printf("\t\t1 -> NOVA NOTA  -  2 -> APAGAR NOTA - 0 -> SAIR DO PROGRAMA\n");

    int opcao;
    bool mostrarMenu = true;
    while(mostrarMenu){

    scanf("\t%d", &opcao);
    switch(opcao){
        case 1:
                Inserir_Nota();
                mostrarMenu = false;
                break;
        case 2:
                Apagar_Nota();
                mostrarMenu = false;
                break;
        case 0:
            return 0;
        default:
            printf("OPCAO INVALIDA\n");
                 break;

    }

    }}

void Ler_Nota(Nota *n) {


 getchar();
  char nomeTecnico[99];
  char dataViagem[15];
  char cidadeOrigem[40];
  char cidadeDestino[40];

   printf("Tecnico: ");

    fgets(nomeTecnico, 99, stdin);
    nomeTecnico[strcspn(nomeTecnico,"\n")]= '\0';
    strcpy(n->tecnico, nomeTecnico);

   printf("Data:   ");
   fgets(dataViagem, 15, stdin);
   dataViagem[strcspn(dataViagem,"\n")]= '\0';
   strcpy(n->data, dataViagem);


  printf("Cidade Origem: ");
  fgets(cidadeOrigem, 40, stdin);
  cidadeOrigem[strcspn(cidadeOrigem,"\n")]= '\0';
  strcpy(n->origem, cidadeOrigem);


  printf("Cidade Destino: ");
  fgets(cidadeDestino, 40, stdin);
  cidadeDestino[strcspn(cidadeDestino,"\n")]= '\0';
  strcpy(n->destino, cidadeDestino);



  printf("Valor da Nota: ");
  scanf("%f", &n->valor);
  n->status = 'R';


}


void Mostrar_Nota(Nota notasSalvas[],int tamArray){

    printf("\t\t+___________________________________________________________________________+\n");
    printf("\t\t+                             CADASTRO DE NOTAS                             +\n");
    printf("\t\t+___________________________________________________________________________+\n\n");

    if(tamArray==0){
        printf("\t\t\t\tAINDA NAO EXISTEM NOTAS CADASTRADAS!\n\n");
    }
    for(int i=0; i<tamArray; i++ ){

        printf ("\tNRO: %d - Tecnico: %s - Data da Viagem: %s - Origem: %s - Destino: %s - Valor: %.2f\n\n", i+1,
                notasSalvas[i].tecnico, notasSalvas[i].data, notasSalvas[i].origem, notasSalvas[i].destino, notasSalvas[i].valor);
    }
    menuOpcoes();

}
