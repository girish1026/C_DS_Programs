#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

void push(struct node **, int);
void append(struct node **, int);
void insertBeforeLocation(struct node **, int, int);
void insertAtLocation(struct node **, int, int);
void insertAfterLocation(struct node **, int, int);
void deleteBeforeLocation(struct node **head, int location);
void deleteAtLocation(struct node **head, int location);
void deleteAfterLocation(struct node **head, int location);
void insertBeforeNode(struct node **, int, int);
void insertAtNode(struct node **, int, int);
void insertAfterNode(struct node **, int, int);
void deleteBeforeNode(struct node **, int);
void deleteNode(struct node **, int);
void deleteAfterNode(struct node **, int);
void printList(struct node *);
int countNodes(struct node *);
void freeList(struct node **);

int main()
{
    struct node *list = NULL;

    append(&list, 1);
    append(&list, 2);
    append(&list, 3);
    append(&list, 4);
    append(&list, 5);

    printf("No of nodes %d\n", countNodes(list));

    printList(list);
    freeList(&list);

    return 0;
}

//Adds a node at beginning of list
void push(struct node **head_ref, int new_data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if(new_node == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        new_node->data = new_data;

        if(*head_ref == NULL)   //if list is empty
        {
            new_node->link = NULL;
            *head_ref = new_node;
        }
        else    //if list is not empty
        {
            new_node->link = *head_ref;
            *head_ref = new_node;
        }
    }
}

//Adds a node at end of list
void append(struct node **head_ref, int new_data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if(new_node == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        new_node->data = new_data;
        new_node->link = NULL;

        if(*head_ref == NULL)
            *head_ref = new_node;
        else
        {
            struct node *temp_node = *head_ref;

            while(temp_node->link != NULL)
                temp_node = temp_node->link;

            temp_node->link = new_node;
        }
    }
}

//Adds a node before a valid location
void insertBeforeLocation(struct node **head, int location, int new_data)
{
    int count = countNodes(*head);

    if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    //else if((location >= 0 && location < count) || *head == NULL)
    else
    {
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        if(new_node == NULL)
        {
            printf("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        new_node->data = new_data;

        if(*head == NULL)
        {
            new_node->link = NULL;
            *head = new_node;
        }
        else if(location == 0)
        {
            new_node->link = *head;
            *head = new_node;
        }
        else if(location > 0 && location < count)
        {
            struct node *ref_node = *head;

            for(int i = 0; i < location-1; i++)
                    ref_node = ref_node->link;

            new_node->link = ref_node->link;
            ref_node->link = new_node;
        }
    }
}

void insertAtLocation(struct node **head, int location, int new_data)
{
    int count = countNodes(*head);

    if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    else
    {
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        if(new_node == NULL)
        {
            printf("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            new_node->data = new_data;

            if(*head == NULL)
            {
                new_node->link = NULL;
                *head = new_node;
            }
            else if(location == 0)
            {
                new_node->link = (*head);
                *head = new_node;
            }
            else
            {
                struct node *temp_node, *ref_node;
                int i;

                temp_node = ref_node = *head;
                for(i=0; i<location-1; i++)
                    ref_node = ref_node->link;

                for(i=0; i<location; i++)
                    temp_node = temp_node->link;

                ref_node->link = new_node;
                new_node->link = temp_node;
            }
        }
    }
}

void insertAfterLocation(struct node **head, int location, int new_data)
{
    int count = countNodes(*head);

    if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    else
    {
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        if(new_node == NULL)
        {
            printf("Memory aallocation failed");
            exit(EXIT_FAILURE);
        }

        new_node->data = new_data;

        if(*head == NULL)
        {
            new_node->link = NULL;
            *head = new_node;
        }
        else
        {
            struct node *ref_node = *head;

            if(location >= 0 && location <= count-2)
            {
                for(int i = 0; i < location; i++)
                    ref_node = ref_node->link;

                new_node->link = ref_node->link;
                ref_node->link = new_node;
            }
            else if(location == count-1)
            {
                new_node->link = NULL;

                while(ref_node->link != NULL)
                    ref_node = ref_node->link;

                ref_node->link = new_node;
            }
        }
    }
}

void deleteBeforeLocation(struct node **head, int location)
{
    if(*head == NULL)
        printf("List can't be empty\n");
    else
    {
        int count = countNodes(*head);

        if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else if(location == 0)
            printf("No node is found before head node\n");
        else
        {
            struct node *next_node, *prev_node;
            next_node = (*head)->link;
            prev_node = *head;

            if(location == 1)
            {
                *head = next_node;
                free(prev_node);
            }
            else if(location > 1 && location <= count-1)
            {
                for(int i=0; i<location-2; i++)
                {
                    next_node = next_node->link;
                    prev_node = prev_node->link;
                }

                prev_node->link = next_node->link;
                free(next_node);
            }
        }
    }
}

void deleteAtLocation(struct node **head, int location)
{
    if(*head == NULL)
        printf("List can't be empty\n");
    else
    {
        int count = countNodes(*head);

        if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else
        {
            struct node *prev_node, *next_node;

            prev_node = *head;
            next_node = (*head)->link;

            if(location == 0)
            {
                *head = next_node;
                free(prev_node);
            }
            if((location > 0 && location <= count - 2) || (location == count - 1))
                for(int i=0; i<location-1; i++)
                {
                    next_node = next_node->link;
                    prev_node = prev_node->link;
                }
            if(location > 0 && location <= count - 2)
            {
                prev_node->link = next_node->link;
                free(next_node);
            }
            else if(location == count - 1)
            {
                prev_node->link = NULL;
                free(next_node);
            }
        }
    }
}

void deleteAfterLocation(struct node **head, int location)
{
    if(*head == NULL)
        printf("List can't be empty\n");
    else
    {
        int count = countNodes(*head);

        if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else
        {
            struct node *prev_node, *next_node;

            prev_node = *head;
            next_node = (*head)->link;

            if((location >= 0 && location <= count - 3) || (location == count - 2))
                for(int i=0; i<location; i++)
                {
                    next_node = next_node->link;
                    prev_node = prev_node->link;
                }

            if(location >= 0 && location <= count - 3)
            {
                prev_node->link = next_node->link;
                free(next_node);
            }
            else if(location == count - 2)
            {
                prev_node->link = NULL;
                free(next_node);
            }
            else if(location == count - 1)
                printf("Can't delete a node after last node\n");
        }
    }
}

void insertBeforeNode(struct node **head_ref, int new_data, int key)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if(new_node == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    else    //If head is empty, adds node as first node
    {
        new_node->data = new_data;

        if(*head_ref == NULL)
        {
            new_node->link = NULL;
            *head_ref = new_node;
        }
        else
        {
            if(((*head_ref)->link == NULL || (*head_ref)->link != NULL) && (*head_ref)->data == key)
            {
                new_node->link = *head_ref;
                *head_ref = new_node;
            }
            else if((*head_ref)->link == NULL && (*head_ref)->data != key)
            {
                printf("Reference node not found\n");
                free(new_node);
            }

            else if(*head_ref != NULL && (*head_ref)->data != key)
            {
                struct node *ref_node, *next_node;
                ref_node = *head_ref;
                next_node = (*head_ref)->link;

                while(next_node->link != NULL && next_node->data != key)
                {
                    next_node = next_node->link;
                    ref_node = ref_node->link;
                }

                if(next_node->link == NULL)
                {
                    if(next_node->data == key)
                    {
                        new_node->link = next_node;
                        ref_node->link =new_node;
                    }
                    else
                    {
                        printf("Reference node not found\n");
                        free(new_node);
                    }
                }
                else
                {
                    new_node->link = next_node;
                    ref_node->link = new_node;
                }
            }
        }
    }
}

void insertAtNode(struct node **head, int new_data, int key)
{
    struct node * new_node = (struct node *)malloc(sizeof(struct node));
    if(new_node == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        new_node->data = new_data;

        if(*head == NULL)
        {
            new_node->link = NULL;
            *head = new_node;
        }
        else
        {
            struct node *prev_node, *next_node, *temp_node;

            prev_node = temp_node = *head;
            next_node = temp_node->link;

            if((prev_node == NULL || prev_node != NULL) && prev_node->data == key)
            {
                new_node->link = *head;
                *head = new_node;
            }
            else if(prev_node->link == NULL && prev_node->data != key)
            {
                printf("Reference node not found\n");
                free(new_node);
            }

            else if(prev_node->link != NULL && prev_node->data != key)
            {
                while(1)
                {
                    if(next_node->data == key)
                    {
                        prev_node->link = new_node;
                        new_node->link = next_node;
                        break;
                    }
                    else if(next_node->data != key && next_node->link == NULL)
                    {
                        printf("Reference node not found\n");
                        free(new_node);
                        break;
                    }
                    prev_node = prev_node->link;
                    next_node = next_node->link;
                }
            }
        }
    }
}

void insertAfterNode(struct node **head_ref, int new_data, int key)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if(new_node == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        new_node->data = new_data;

        if(*head_ref == NULL)
        {
            new_node->link = NULL;
            *head_ref = new_node;
        }
        else
        {
            struct node *ref_node, *next_node;
            ref_node = *head_ref;
            next_node = (*head_ref)->link;

            while(ref_node->data != key && ref_node->link != NULL)
            {
                next_node = next_node->link;
                ref_node = ref_node->link;
            }
            if(ref_node->link == NULL)
            {
                if(ref_node->data == key)
                {
                    new_node->link = NULL;
                    ref_node->link =new_node;
                }
                else
                {
                    printf("Reference node not found\n");
                    free(new_node);
                }
            }
            else
            {
                ref_node->link = new_node;
                new_node->link = next_node;
            }
        }
    }
}

void deleteBeforeNode(struct node **head, int key)  //OK
{
    if(*head == NULL)
        printf("List can't be empty\n");
    else
    {
        struct node *prev_node = *head;

        if(prev_node->link == NULL && prev_node->data == key)
            printf("There is no node before head\n");
        else if(prev_node->link == NULL && prev_node->data != key)
            printf("List contains one node and key not found\n");
        else if(prev_node->link != NULL && prev_node->data == key)
            printf("There is no node before head\n");
        else if(prev_node->link != NULL && prev_node->data != key)
        {
            struct node *next_node = (*head)->link;

            while(next_node->link != NULL &&  next_node->data != key)
            {
                next_node = next_node->link;
                prev_node = prev_node->link;
            }
            if(next_node->link == NULL || next_node->data == key)
            {
                if(prev_node == *head && next_node->data == key)
                {
                    *head = prev_node->link;
                    free(prev_node);
                }
                else if(prev_node != *head && next_node->data == key)
                {
                    struct node *temp_node = *head;
                    int count = 0;

                    while(1)
                    {
                        if(temp_node->data == key)
                            break;
                        count++;
                        temp_node = temp_node->link;
                    }
                    temp_node = *head;
                    if(count > 1)
                        for( int i = 0; i < count - 2; i++)
                            temp_node = temp_node->link;
                    temp_node->link = next_node;
                    free(prev_node);
                }
                else
                    printf("Reference node not found\n");
            }
        }
    }
}

void deleteNode(struct node **head, int key)
{
    if(*head == NULL)
        printf("List can't be empty\n");
    else
    {
        struct node *prev_node = *head;

        if(prev_node == NULL && prev_node->data == key)
        {
            free(prev_node);
            *head = NULL;
        }
        else if(prev_node->link == NULL && prev_node->data != key)
            printf("Element not found\n");
        else
        {
            struct node *next_node = (*head)->link;

            if(prev_node != NULL && prev_node->data == key)
            {
                *head= next_node;
                free(prev_node);
            }
            else if(prev_node != NULL && prev_node->data != key)
            {
                struct node *next_node = (*head)->link;

                while(next_node->link != NULL && next_node->data != key)
                {
                    next_node = next_node->link;
                    prev_node = prev_node->link;
                }
                if(next_node->link == NULL)
                {
                    if(next_node->data == key)
                    {
                        prev_node->link = NULL;
                        free(next_node);
                    }
                    else
                        printf("Element not found\n");
                }
                else
                {
                    prev_node->link = next_node->link;
                    free(next_node);
                }
            }
        }
    }
}

void deleteAfterNode(struct node **head, int key)   //OK
{
    if(*head == NULL)
        printf("List can't be empty\n");
    else
    {
        struct node *prev_node = *head;

        if(prev_node->link == NULL && prev_node->data == key)
            printf("List contains only one node\n");
        else if(prev_node->link == NULL && prev_node->data != key)
            printf("List contains one node and key not found\n");
        else if(prev_node != NULL)
        {
            struct node *temp_node = *head;
            int count = 0;

            while(1)
            {
                if(prev_node->data == key || prev_node->link == NULL)
                    break;
                count++;
                prev_node = prev_node->link;
                temp_node = temp_node->link;
            }

            if(prev_node->link != NULL && prev_node->data == key)
            {
                prev_node = *head;
                for(int i = 0; i < count + 1; i++)
                    prev_node = prev_node->link;
                temp_node->link = prev_node->link;
                free(prev_node);
            }
            else if(prev_node->link == NULL && prev_node->data == key)
                printf("Can't delete node after last node\n");
            else if(prev_node->link == NULL && prev_node->data != key)
                printf("Reference node not found\n");
        }
    }
}

void printList(struct node *n)
{
    if(n != NULL)
    {
        while (n != NULL)
        {
            printf(" %d ", n->data);
            n = n->link;
        }
        printf("\n");
    }
    else
        printf("You called with empty list\n");
}

int countNodes(struct node *node_ref)
{
    int nodeCount = 0;

    while(node_ref != NULL)
    {
        node_ref = node_ref->link;
        nodeCount++;
    }

    return nodeCount;
}

void freeList(struct node **head_ref)
{
    if(*head_ref == NULL)
        printf("List is empty\n");
    else
    {
        struct node *current, *next;
        current = *head_ref;

        while(current != NULL)
        {
            next = current->link;
            //printf("Now %d deleted\n", current->data);
            free(current);
            current = next;
        }
        printf("List is free now\n");
        *head_ref = NULL;
    }
}
