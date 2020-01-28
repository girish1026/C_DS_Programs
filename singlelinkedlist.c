#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

void push(struct node **, int);
void append(struct node **, int);
void insertBefore(struct node **, int, int);
void insertAfter(struct node **, int, int);
void insertAtLocation(struct node **, int, int);
void deleteNode(struct node **, int);
void deleteBefore(struct node **, int);
void deleteAfter(struct node **, int);
void deleteAtLocation(struct node **, int);
void printList(struct node *);
int countNodes(struct node *);
void freeList(struct node **);

//Re-write all malloc() contained functions with malloc() and free()

int main()
{
    struct node *list;
    list = NULL;

    freeList(&list);
    printList(list);

    push(&list, 1);
    push(&list, 10);
    push(&list, 20);
    push(&list, 30);

    append(&list, 40);
    append(&list, 50);
    append(&list, 1000);

    insertAfter(&list, 6, 444);
    //insertBefore(&list, 6, 99);
    //insertAtLocation(&list, 8, 111);

    //deleteNode(&list, 444);
    //deleteBefore(&list, 7);
    //deleteAfter(&list, 7);
    deleteAtLocation(&list, 7);

    printList(list);
    freeList(&list);
    freeList(&list);

    return 0;
}

//Adds a node at beginning of list
void push(struct node **head_ref, int new_data)
{
    struct node *new_node;

    if(*head_ref == NULL)   //if list is empy
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = new_data;
        new_node->link = NULL;
        *head_ref = new_node;
    }
    else    //if list is not empty
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = new_data;
        new_node->link = *head_ref;
        *head_ref = new_node;
    }
}

//Adds a node at end of list
void append(struct node **head_ref, int new_data)
{
    struct node *temp_node;

    if(*head_ref == NULL)   //if list is empy
    {
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = new_data;
        new_node->link = NULL;
        *head_ref = new_node;
    }
    else    //if list is not empty
    {
        struct node *new_node;

        new_node = *head_ref;

        while(new_node->link != NULL)
            new_node = new_node->link;

        temp_node = (struct node *)malloc(sizeof(struct node));

        temp_node->data = new_data;
        temp_node->link = NULL;
        new_node->link = temp_node;
    }
}

//Adds a node before a valid location
void insertBefore(struct node **node_ref, int location, int new_data)
{
    struct node *temp_node  = *node_ref, *ref_node, *new_node;
    int count = countNodes(temp_node), i;
    ref_node = *node_ref;

    if(*node_ref == NULL)
        printf("List can't be empty\n");
    else if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    else if(location == 0)
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = new_data;
        new_node->link = *node_ref;
        *node_ref = new_node;
        //printf("Cant add at head node. Use push() instead.\n");
    }
    else
    {
        for(i = 0; i < location-1; i++)
        {
            ref_node = ref_node->link;
        }

        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = new_data;
        new_node->link = ref_node->link;
        ref_node->link = new_node;
    }
}

//Adds a node after a valid location
void insertAfter(struct node **node_ref, int location, int new_data)
{
    struct node *temp_node  = *node_ref, *ref_node, *new_node;
    int count = countNodes(temp_node), i;
    ref_node = *node_ref;

    if(*node_ref == NULL)
        printf("List can't be empty\n");
    else if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    else if(location >= 0 && location <= count-2)
    {
        for(i = 0; i < location; i++)
            ref_node = ref_node->link;

        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = new_data;
        new_node->link = ref_node->link;
        ref_node->link = new_node;
    }
    else if(location == count-1)
    {
        //Need to wirte code
    }
}

//Adds a node at a valid location
void insertAtLocation(struct node **head_ref, int location, int new_data)
{
    struct node *temp_node  = *head_ref, *ref_node, *new_node;
    int count = countNodes(temp_node), i;
    ref_node = *head_ref;
    temp_node = *head_ref;

    if(*head_ref == NULL)
        printf("List can't be empty\n");
    else if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    else if(location == 0)
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = new_data;
        new_node->link = temp_node;
    }
    else
    {
        for(i=0; i<location-1; i++)
            ref_node = ref_node->link;

        for(i=0; i<location; i++)
            temp_node = temp_node->link;

        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = new_data;
        ref_node->link = new_node;
        new_node->link = temp_node;
    }
}

//deletes a node with specified key
void deleteNode(struct node **head_ref, int key)
{
    struct node *prev_node, *next_node, *temp_node;
    prev_node = *head_ref;
    temp_node = *head_ref;
    next_node = temp_node->link;

    if(prev_node != NULL && prev_node->data == key)
    {
        *head_ref= next_node;
        free(prev_node);
    }
    else if(prev_node == NULL && prev_node->data == key)
        free(prev_node);
    else if(prev_node == NULL && prev_node->data != key)
        printf("Element not found\n");
    else
    {
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

void deleteBefore(struct node **head_ref, int location)
{
    struct node *prev_node, *next_node, *temp_node, *new_node;
    int count, i;

    prev_node = *head_ref;
    temp_node  = *head_ref;
    next_node = temp_node->link;

    new_node = *head_ref;
    count = countNodes(new_node);

    if(*head_ref == NULL)
        printf("List can't be empty\n");
    else if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    else if(location == 0)
        printf("No node is found before head node\n");
    else if(location == 1)
    {
        *head_ref = next_node;
        free(prev_node);
    }
    else if(location > 1 && location <= count-1)
    {
        for(i=0; i<location-2; i++)
        {
            next_node = next_node->link;
            prev_node = prev_node->link;
        }
            prev_node->link = next_node->link;
            free(next_node);
    }
}

void deleteAfter(struct node **head_ref, int location)
{
    struct node *prev_node, *next_node, *temp_node, *new_node;
    int count, i;

    prev_node = *head_ref;
    temp_node  = *head_ref;
    next_node = temp_node->link;

    new_node = *head_ref;
    count = countNodes(new_node);

    if(*head_ref == NULL)
        printf("List can't be empty\n");
    else if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    else if(location >= 0 && location <= count - 3)
    {
        for(i=0; i<location; i++)
        {
            next_node = next_node->link;
            prev_node = prev_node->link;
        }
        prev_node->link = next_node->link;
        free(next_node);
    }
    else if(location == count - 2)
    {
        for(i=0; i<location; i++)
        {
            next_node = next_node->link;
            prev_node = prev_node->link;
        }
        if(next_node->link == NULL)
        {
            prev_node->link = NULL;
            free(next_node);
        }
    }
    else if(location == count - 1)
        printf("Can't delete a node after last node\n");
}

void deleteAtLocation(struct node **head_ref, int location)
{
    struct node *prev_node, *next_node, *temp_node, *new_node;
    int count, i;

    prev_node = *head_ref;
    temp_node  = *head_ref;
    next_node = temp_node->link;

    new_node = *head_ref;
    count = countNodes(new_node);

    if(*head_ref == NULL)
        printf("List can't be empty\n");
    else if(location >= count)
        printf("No. of elements are less in list\n");
    else if(location < 0)
        printf("Invalid location\n");
    else if(location == 0)
    {
        *head_ref = next_node;
        free(prev_node);
    }
    else if(location > 0 && location <= count - 2)
    {
        for(i=0; i<location-1; i++)
        {
            next_node = next_node->link;
            prev_node = prev_node->link;
        }
        prev_node->link = next_node->link;
        free(next_node);
    }
    else if(location == count - 1)
    {
        for(i=0; i<location-1; i++)
        {
            next_node = next_node->link;
            prev_node = prev_node->link;
        }
        prev_node->link = NULL;
        free(next_node);
    }
}

void printList(struct node *n)
{

    if(n != NULL)
        while (n != NULL)
        {
            printf(" %d\n", n->data);
            n = n->link;
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

/*void freeList(struct node *n)
{
   struct node *temp;

   while (n != NULL)
    {
       temp = n;
       n = n->link;
       free(temp);
    }

    if(!n)
        printf("List is empty now.");
}*/

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
            free(current);
            current = next;
        }
        printf("List is free now\n");
        *head_ref = NULL;
    }
}
