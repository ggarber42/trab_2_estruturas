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

void avisoListaVazia()
{
    printf("\nA lista esta vazia\n\n");
}

void avisoPosicaoInexistente()
{
    printf("\nEssa posicao nao existe\n\n");
}

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


void displayLista()
{
    struct contato *current = head;
    int posicaoLista = 1;
    if (head == NULL)
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

void getContato(int posicao)
{
    struct contato *current = head;
    if (posicao <= 0 || head == NULL)
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

void deleteContato(int posicao)
{
    struct contato *current = head;
    if (posicao <= 0 || head == NULL)
    {
        avisoListaVazia();
        return;
    }
    int i;
    for (int i = 1; current != NULL && i < posicao; i++)
    {
        current = current->next;
    }
    if (head == NULL || current == NULL)
    {
        avisoPosicaoInexistente();
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

int getNovaPosicao(struct contato *newcontato)
{

    struct contato *current = head;
    int pos = 0;
    if (current == NULL)
    {
        return pos;
    }
    else
    {
        while (current != NULL)
        {
            int n = 0;
            while (n < strlen(newcontato->nome))
            {
                if (newcontato->nome[n] < current->nome[n])
                {
                    return pos;
                }
                n++;
            }
            pos++;
            current = current->next;
        }
    }
    return pos;
}

void addContatoEmPosicao(struct contato *pessoa)
{
    int pos = getNovaPosicao(pessoa);
    struct contato *newcontato = (struct contato *)malloc(sizeof(struct contato));
    struct contato *temp = (struct contato *)malloc(sizeof(struct contato));
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
        struct contato *current = head;
        if (current->next == NULL && pos == 1)
        {
            current->next = newcontato;
            newcontato->previous = current;
            newcontato->next = NULL;
        }
        else if (current->next == NULL || pos == 0)
        {
            head = newcontato;
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
            // addcontato(pessoa);
            addContatoEmPosicao(pessoa);
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
    }
    return 0;
}