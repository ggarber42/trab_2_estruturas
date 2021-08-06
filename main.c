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

struct contato *head, *tail = NULL;

void addcontato(struct contato *pessoa)
{
    struct contato *newcontato = (struct contato *)malloc(sizeof(struct contato));
    strcpy(newcontato->nome, pessoa->nome);
    strcpy(newcontato->email, pessoa->email);
    strcpy(newcontato->telefone, pessoa->telefone);
    if (head == NULL)
    {
        head = tail = newcontato;
        head->previous = NULL;
        tail->next = NULL;
    }
    else
    {
        tail->next = newcontato;
        newcontato->previous = tail;
        tail = newcontato;
        tail->next = NULL;
    }
}

void sortLista()
{
    struct contato *current = NULL, *index = NULL;
    char temp[50];
    if (head == NULL)
    {
        return;
    }
    else
    {
        for (current = head; current->next != NULL; current = current->next)
        {
            for (index = current->next; index != NULL; index = index->next)
            {
                int n = 0;
                while (n < strlen(current->nome))
                {
                    if (current->nome[n] > index->nome[n])
                    {
                        strcpy(temp, current->nome);
                        strcpy(current->nome, index->nome);
                        strcpy(index->nome, temp);
                    }
                    if (current->nome[n] != index->nome[n])
                    {
                        break;
                    }
                    n++;
                };
            }
        }
    }
}

void displayLista()
{
    struct contato *current = head;
    int posicaoLista = 1;
    if (head == NULL)
    {
        printf("\nA lista esta vazia\n\n");
        return;
    }
    printf("\n***\n");
    while (current != NULL)
    {   
        printf("%d- ",posicaoLista);
        printf("Nome: %s, ", current->nome);
        printf("Email: %s, ", current->email);
        printf("Telefone: %s\n", current->telefone);
        current = current->next;
        posicaoLista++;
    }
    printf("***\n");
}

void getContato(int posicao)
{
    struct contato *current = head;
    if (posicao <= 0 || head == NULL)
    {
        return;
    }
    int i;
    for (int i = 1; current != NULL && i < posicao; i++)
    {
        current = current->next;
    }

    printf("\n***\n");
    printf("Nome: %s, ", current->nome);
    printf("Email: %s, ", current->email);
    printf("Telefone: %s\n", current->telefone);
    printf("***\n");
};

void deleteContato(int posicao)
{
    struct contato *current = head;
    if (posicao <= 0 || head == NULL)
    {
        return;
    }
    int i;
    for (int i = 1; current != NULL && i < posicao; i++)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        return;
    }
    if (head == NULL || current == NULL)
    {
        return;
    }
    if (head == current)
    {
        head = current->next;
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
    struct contato *pessoa = (struct contato *)malloc(sizeof(struct contato));
    char aux[50];
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
            addcontato(pessoa);
            break;
        case 2:
            printf("Digite a posicao: ");
            scanf("%d", &posicao);
            getContato(posicao);
            break;
        case 3:
            printf("Digite a posicao: ");
            scanf("%d", &posicao);
            deleteContato(posicao);
            break;
        case 4:
            displayLista();
            break;
        case 5:
            flag = false;
            break;
        default:
            break;
        }
        sortLista();
    }

    // strcpy(pessoa->nome, "misha");
    // strcpy(pessoa->email, "misha@email.com");
    // strcpy(pessoa->telefone, "000");
    // addcontato(pessoa);

    // strcpy(pessoa->nome, "amy");
    // strcpy(pessoa->email, "amy@email.com");
    // strcpy(pessoa->telefone, "000");
    // addcontato(pessoa);

    // strcpy(pessoa->nome, "tom");
    // strcpy(pessoa->email, "tom@email.com");
    // strcpy(pessoa->telefone, "000");
    // addcontato(pessoa);

    // strcpy(pessoa->nome, "jade");
    // strcpy(pessoa->email, "jade@email.com");
    // strcpy(pessoa->telefone, "000");
    // addcontato(pessoa);

    // strcpy(pessoa->nome, "maia");
    // strcpy(pessoa->email, "maia@email.com");
    // strcpy(pessoa->telefone, "000");
    // addcontato(pessoa);

    // strcpy(pessoa->nome, "mel");
    // strcpy(pessoa->email, "mel@email.com");
    // strcpy(pessoa->telefone, "000");
    // addcontato(pessoa);

    //    //Displaying original list
    // printf("Original list: \n");
    // display();
    //    //Sorting list
    // sortList();
    //    //Displaying sorted list
    // printf("Sorted list: \n");
    // display();
    // getContato(3);
    // deleteContato(1);
    // display();
    return 0;
}