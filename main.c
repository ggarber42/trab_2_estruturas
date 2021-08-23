#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct contato
{
     char nome[50];
     char email[50];
     char telefone[50];
     struct contato *previous;
     struct contato *next;
};

// struct contato *head, *tail = NULL;


 struct header{
	struct contato* head;//primeiro
	struct contato* tail;//ultimo
};

void initLista (struct header *lista){
    lista->head = NULL;
    lista->tail = NULL;
}


void avisoListaVazia()
{
     printf("\nA lista esta vazia\n\n");
}

void avisoPosicaoInexistente()
{
     printf("\nEssa posicao nao existe\n\n");
}

void displayLista( struct header *lista)
{
     struct contato *current = lista->head;
     int posicaoLista = 1;
     if (lista->head == NULL)
     {
          avisoListaVazia();
          return;
     }
     printf("\n***\n");
     while (current != NULL)
     {
          printf("%d- ", posicaoLista);
          printf("Nome: %s, ", current->nome);
          printf("Email: %s, ", current->email);
          printf("Telefone: %s\n", current->telefone);
          current = current->next;
          posicaoLista++;
     }
     printf("***\n");
}

void getContato(int posicao, struct header *lista)
{
     struct contato *current = lista->head;
     if (posicao <= 0 || lista->head == NULL)
     {
          avisoListaVazia();
          return;
     }
     int i;
     for (int i = 1; current != NULL && i < posicao; i++)
     {
          current = current->next;
     }

     if (current == NULL)
     {
          avisoPosicaoInexistente();
     }
     else
     {
          printf("\n***\n");
          printf("Nome: %s, ", current->nome);
          printf("Email: %s, ", current->email);
          printf("Telefone: %s\n", current->telefone);
          printf("***\n");
     }
};

void deleteContato(int posicao, struct header *lista)
{
     struct contato *current = lista->head;
     if (posicao <= 0 || lista->head == NULL)
     {
          avisoListaVazia();
          return;
     }
     int i;
     for (int i = 1; current != NULL && i < posicao; i++)
     {
          current = current->next;
     }
     if (lista->head == NULL || current == NULL)
     {
          avisoPosicaoInexistente();
          return;
     }
     if (lista->head == current)
     {
          lista->head = current->next;
     }
     if (current->next != NULL)
     {
          current->next->previous = current->previous;
     }
     if (current->previous != NULL)
     {
          current->previous->next = current->next;
     }
     free(current);
};

int getNovaPosicao(struct contato *newcontato, struct header *lista)
{
     int pos = 0;
     if (lista->head == NULL)
     {
          return pos;
     }
     else
     {
          struct contato *current = lista->head;
          while (current != NULL)
          {

               int ret = strcmp(newcontato->nome, current->nome);

               if (ret < 0)
               {
                    break;
               }
               else if (ret > 0)
               {
                    pos++;
               }
               current = current->next;
          }
     }
     return pos;
}

void addContatoEmPosicao(struct contato *pessoa, int pos, struct header *lista)
{

     struct contato *newcontato = (struct contato *)malloc(sizeof(struct contato));
     struct contato *temp = (struct contato *)malloc(sizeof(struct contato));
     strcpy(newcontato->nome, pessoa->nome);
     strcpy(newcontato->email, pessoa->email);
     strcpy(newcontato->telefone, pessoa->telefone);
     if (lista->head == NULL)
     {
          lista->head = lista->tail = newcontato;
     }
     else
     {
          struct contato *current = lista->head;
          if (current->next == NULL && pos == 1)
          {
               current->next = newcontato;
               newcontato->previous = current;
               newcontato->next = NULL;
          }
          else if (current->next == NULL || pos == 0)
          {
               lista->head = newcontato;
               current->previous = newcontato;
               newcontato->next = current;
               newcontato->previous = NULL;
          }
          else
          {
               int i;
               for (int i = 1; current != NULL && i < pos; i++)
               {
                    current = current->next;
               }
               newcontato->next = current->next;
               newcontato->previous = current;
               current->next = newcontato;
          }
     }
}

void showMenu()
{
     printf("Escolha uma das opcoes abaixo\n");
     printf("1 - Inserir contato\n");
     printf("2 - Consultar contato de uma determinada posicao\n");
     printf("3 - Remover contato de uma determinada posicao\n");
     printf("4 - Listar contatos\n");
     printf("5 - Sair\n");
     printf("Digite aqui sua opcao: ");
}

int main()
{
     struct header lista;
     initLista(&lista);
     struct contato *pessoa = (struct contato *)malloc(sizeof(struct contato));
     int opcao, posicao;
     bool flag = true;
     while (flag)
     {
          showMenu();
          scanf("%i", &opcao);
          switch (opcao)
          {
          case 1:
               printf("Digite o Nome: ");
               scanf("%s", pessoa->nome);
               printf("Digite o email: ");
               scanf("%s", pessoa->email);
               printf("Digite o telefone: ");
               scanf("%s", pessoa->telefone);
               int pos = getNovaPosicao(pessoa, &lista);
               addContatoEmPosicao(pessoa, pos, &lista);
               break;
          case 2:
               printf("Digite a posicao: ");
               scanf("%d", &posicao);
               getContato(posicao, &lista);
               break;
          case 3:
               printf("Digite a posicao: ");
               scanf("%d", &posicao);
               deleteContato(posicao, &lista);
               break;
          case 4:
               displayLista(&lista);
               break;
          case 5:
               flag = false;
               break;
          default:
               break;
          }
     }
     return 0;
}