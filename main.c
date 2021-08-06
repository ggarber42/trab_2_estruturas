#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Represent a contato of the doubly linked list

struct contato
{
    char nome[50];
    char email[50];
    char telefone[50];
    struct contato *previous;
    struct contato *next;
};

//Represent the head and tail of the doubly linked list
struct contato *head, *tail = NULL;

//addcontato() will add a contato to the list
void addcontato(struct contato *pessoa)
{
    //Create a new contato
    struct contato *newcontato = (struct contato *)malloc(sizeof(struct contato));
    strcpy(newcontato->nome, pessoa->nome);
    strcpy(newcontato->email, pessoa->email);
    strcpy(newcontato->telefone, pessoa->telefone);
    //If list is empty
    if (head == NULL)
    {
        //Both head and tail will point to newcontato
        head = tail = newcontato;
        //head's previous will point to NULL
        head->previous = NULL;
        //tail's next will point to NULL, as it is the last contato of the list
        tail->next = NULL;
    }
    else
    {
        //newcontato will be added after tail such that tail's next will point to newcontato
        tail->next = newcontato;
        //newcontato's previous will point to tail
        newcontato->previous = tail;
        //newcontato will become new tail
        tail = newcontato;
        //As it is last contato, tail's next will point to NULL
        tail->next = NULL;
    }
}

//sortList() will sort the given list in ascending order
void sortList()
{
    struct contato *current = NULL, *index = NULL;
    char temp[50];
    //Check whether list is empty
    if (head == NULL)
    {
        return;
    }
    else
    {
        //Current will point to head
        for (current = head; current->next != NULL; current = current->next)
        {
            //Index will point to contato next to current
            for (index = current->next; index != NULL; index = index->next)
            {
                //If current's nome is greater than index's nome, swap the nome of current and index
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

//display() will print out the contatos of the list
void display()
{
    //contato current will point to head
    struct contato *current = head;
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while (current != NULL)
    {
        //Prints each contato by incrementing pointer.
        printf("%s ", current->nome);
        current = current->next;
    }
    printf("\n");
}

void getContato(int posicao)
{
    struct contato *current = head;
    /* if list in NULL or invalid position is given */
    if (posicao <= 0 || head == NULL)
    {
        return;
    }
    /* traverse up to the node at position 'n' from
       the beginning */
    int i;
    for (int i = 1; current != NULL && i < posicao; i++)
    {
        current = current->next;
    }

    printf("%s\n", current->nome);
};

void deleteContato(int posicao)
{
    struct contato *current = head;
    /* if list in NULL or invalid position is given */
    if (posicao <= 0 || head == NULL)
    {
        return;
    }
    /* traverse up to the node at position 'n' from
       the beginning */
    int i;
    for (int i = 1; current != NULL && i < posicao; i++)
    {
        current = current->next;
    }

    /* if 'n' is greater than the number of nodes
       in the doubly linked list */
    if (current == NULL)
    {
        return;
    }
    /* delete the node pointed to by 'current' */
    // deleteNode(head_ref, current);

    /* base case */
    if (head == NULL || current == NULL)
        return;

    /* If node to be deleted is head node */
    if (head == current)
        head = current->next;

    /* Change next only if node to be deleted is NOT
       the last node */
    if (current->next != NULL)
        current->next->previous = current->previous;

    /* Change prev only if node to be deleted is NOT
       the first node */
    if (current->previous != NULL)
        current->previous->next = current->next;

    /* Finally, free the memory occupied by del*/
    free(current);
};

int main()
{
    struct contato *pessoa = (struct contato *)malloc(sizeof(struct contato));
    //Add contatos to the list
    strcpy(pessoa->nome, "misha");
    strcpy(pessoa->email, "misha@email.com");
    strcpy(pessoa->telefone, "000");
    addcontato(pessoa);

    strcpy(pessoa->nome, "amy");
    strcpy(pessoa->email, "amy@email.com");
    strcpy(pessoa->telefone, "000");
    addcontato(pessoa);

    strcpy(pessoa->nome, "tom");
    strcpy(pessoa->email, "tom@email.com");
    strcpy(pessoa->telefone, "000");
    addcontato(pessoa);

    strcpy(pessoa->nome, "jade");
    strcpy(pessoa->email, "jade@email.com");
    strcpy(pessoa->telefone, "000");
    addcontato(pessoa);

    strcpy(pessoa->nome, "maia");
    strcpy(pessoa->email, "maia@email.com");
    strcpy(pessoa->telefone, "000");
    addcontato(pessoa);

    strcpy(pessoa->nome, "mel");
    strcpy(pessoa->email, "mel@email.com");
    strcpy(pessoa->telefone, "000");
    addcontato(pessoa);

    //    //Displaying original list
    printf("Original list: \n");
    display();
    //    //Sorting list
    sortList();
    //    //Displaying sorted list
    printf("Sorted list: \n");
    display();
    getContato(3);
    deleteContato(1);
    display();
    return 0;
}