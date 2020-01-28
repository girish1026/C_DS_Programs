#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *prev;
    int data;
    struct node *next;
};

void push(struct node **, int);
void append(struct node **, int);
void insertBefore(struct node **, int, int);
void insertAfter(struct node **, int, int);
void insertAtLocation(struct node **, int, int);
void deleteNode(struct node **, int key);
void deleteBefore(struct node **, int);
void deleteAfter(struct node **, int);
void deleteAtLocation(struct node **, int);
void printListForward(struct node **);
void printListReverse(struct node **);
int countNodes(struct node *);
void freeList(struct node **);

int main()
{
    struct node *dllist;
    dllist = NULL;

    freeList(&dllist);
    printListForward(&dllist);
    printListReverse(&dllist);

    push(&dllist, 1);
    push(&dllist, 2);

    append(&dllist, 10);
    append(&dllist, 20);

    //insertBefore(&dllist, 3, 1000);
    //insertAfter(&dllist, 3, 99);
    //insertAtLocation(&dllist, 3, 99);

    printListForward(&dllist);

    //deleteNode(&dllist, 20);
    //deleteBefore(&dllist, 3);
    //deleteAfter(&dllist, 2);
    deleteAtLocation(&dllist, 2);

    printListForward(&dllist);
    printListReverse(&dllist);

    printf("No. of nodes are: %d\n", countNodes(dllist));
    freeList(&dllist);
    freeList(&dllist);

    return 0;
}

//adds a node at beginning of list
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
        new_node->prev = NULL;
        new_node->data = new_data;

        if(*head_ref == NULL)   //if list is empty
        {
            new_node->next = NULL;
            *head_ref = new_node;
        }
        else    //if list is not empty
        {
            new_node->next = (*head_ref);
            (*head_ref)->prev = new_node;
            *head_ref = new_node;
        }
    }
}

//adds a node at end of list
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
        struct node *temp_node = *head_ref;

        new_node->data = new_data;
        new_node->next = NULL;

        if(*head_ref == NULL)
        {
            new_node->prev = NULL;
            *head_ref = new_node;
        }
        else
        {
            while(temp_node->next != NULL)
                temp_node = temp_node->next;

            new_node->prev = temp_node;
            temp_node->next = new_node;
        }
    }
}

void insertBefore(struct node **head_ref, int location, int new_data)
{
    struct node *new_node;

    if(*head_ref == NULL)   //If list is empty, node is added at 0 position
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        if(new_node == NULL)
        {
            printf("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            new_node->prev = NULL;
            new_node->data = new_data;
            new_node->next = NULL;
            *head_ref = new_node;
        }
    }
    else
    {
        struct node *temp_node = *head_ref;
        int count = countNodes(temp_node);

        if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else if(location == 0)
        {
            new_node = (struct node *)malloc(sizeof(struct node));
            if(new_node == NULL)
            {
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            else
            {
                new_node->prev = NULL;
                new_node->data = new_data;
                new_node->next = *head_ref;
                (*head_ref)->prev = new_node;
                *head_ref = new_node;
            }
        }
        else if(location > 0 && location < count)
        {
            struct node *ref_node = *head_ref, *store_next;

            for(int i=0; i<location-1; i++)
                ref_node = ref_node->next;

            new_node = (struct node *)malloc(sizeof(struct node));
            if(new_node == NULL)
            {
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            else
            {
                new_node->data = new_data;
                store_next = ref_node->next;
                ref_node->next = new_node;
                new_node->prev = ref_node;
                new_node->next = store_next;
                store_next->prev = new_node;
            }
        }
    }
}

void insertAfter(struct node **head_ref, int location, int new_data)
{
    struct node *new_node;

    if(*head_ref == NULL)   //If list is empty, node is added at 0 position
    {
        new_node = (struct node *)malloc(sizeof(struct node));
        if(new_node == NULL)
        {
            printf("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            new_node->prev = NULL;
            new_node->data = new_data;
            new_node->next = NULL;
            *head_ref = new_node;
        }
    }
    else
    {
        struct node *temp_node = *head_ref, *store_next;
        int count = countNodes(temp_node);

        if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else if(location >= 0 && location <= count-2)
        {
            struct node *ref_node = *head_ref;

            for(int i=0; i<location; i++)
                ref_node = ref_node->next;

            new_node = (struct node *)malloc(sizeof(struct node));
            if(new_node == NULL)
            {
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            else
            {
                new_node->data = new_data;
                store_next = ref_node->next;
                ref_node->next = new_node;
                new_node->prev = ref_node;
                new_node->next = store_next;
                store_next->prev = new_node;
            }
        }
        else if(location == count-1)
        {
            struct node *ref_node = *head_ref;

            new_node = (struct node *)malloc(sizeof(struct node));
            if(new_node == NULL)
            {
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            else
            {
                new_node->data = new_data;
                new_node->next = NULL;

                //You can use while loop or for loop
                //for(int i=0; i<location; ref_node = ref_node->next, i++);

                while(ref_node->next != NULL)
                    ref_node = ref_node->next;

                new_node->prev = ref_node;
                ref_node->next = new_node;
            }
        }
    }
}

void insertAtLocation(struct node **head_ref, int location, int new_data)
{
    struct node *new_node;

    if(*head_ref == NULL)   //If list is empty, node is added at 0 position
    {
        new_node = (struct node *)malloc(sizeof(struct node));

        if(new_node == NULL)
        {
            printf("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            new_node->prev = NULL;
            new_node->data = new_data;
            new_node->next = NULL;
            *head_ref = new_node;
        }
    }
    else
    {
        struct node *temp_node = *head_ref, *store_next;
        int count = countNodes(temp_node);

        if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else if(location == 0)
        {
            new_node = (struct node *)malloc(sizeof(struct node));
            if(new_node == NULL)
            {
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            else
            {
                new_node->prev = NULL;
                new_node->data = new_data;
                new_node->next = (*head_ref);
                (*head_ref)->prev = new_node;
                *head_ref = new_node;
            }
        }
        else if(location > 0 && location <= count-1)
        {
            struct node *ref_node = *head_ref, *store_next;

            for(int i=0; i<location-1; i++)
                ref_node = ref_node->next;

            new_node = (struct node *)malloc(sizeof(struct node));
            if(new_node == NULL)
            {
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            else
            {
                new_node->data = new_data;
                store_next = ref_node->next;
                ref_node->next = new_node;
                new_node->prev = ref_node;
                new_node->next = store_next;
                store_next->prev = new_node;
            }
        }
    }
}

void deleteNode(struct node **head_ref, int key)
{
    struct node *prev_node, *next_node, *temp_node;
    prev_node = *head_ref;
    temp_node = *head_ref;
    next_node = temp_node->next;

     if((prev_node->prev == NULL && prev_node->next == NULL)  && prev_node->data == key)
        free(prev_node);
    else if((prev_node->prev == NULL && prev_node->next == NULL) && prev_node->data != key)
        printf("Element not found\n");
    else if((prev_node->prev == NULL && prev_node->next != NULL) && prev_node->data == key) //First node
    {
        *head_ref = next_node;
        (*head_ref)->prev = NULL;
        free(prev_node);
    }
    else
    {
        struct node *store_prev, *store_next;

        while(next_node->next != NULL && next_node->data != key)
            next_node = next_node->next;

        if(next_node->next == NULL)
        {
            if(next_node->data == key)  //Last node
            {
                store_prev = next_node->prev;
                store_prev->next = NULL;
                free(next_node);
            }
            else
                printf("Element not found\n");
        }
        else    //Middle nodes
        {
            store_next = next_node->next;
            store_prev = next_node->prev;
            store_next->prev = store_prev;
            store_prev->next = store_next;
            free(next_node);
        }
    }
}

void deleteBefore(struct node **head_ref, int location)
{
    if(*head_ref == NULL)
        printf("List can't be empty\n");
    else
    {
        struct node *new_node = *head_ref;
        int count = countNodes(new_node);

         if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else if(location == 0)
            printf("No node is found before head node\n");
        else if(location == 1)
        {
            struct node *prev_node = *head_ref, *temp_node, *next_node;

            temp_node = *head_ref;
            next_node = temp_node->next;
            *head_ref = next_node;
            (*head_ref)->prev = NULL;
            free(prev_node);
        }
        else if(location > 1 && location <= count-1)
        {
            struct node *temp_node, *next_node, *store_prev, *store_next;

            temp_node = *head_ref;
            next_node = temp_node->next;

            for(int i=0; i<location-2; i++)
                next_node = next_node->next;

            store_next = next_node->next;
            store_prev = next_node->prev;
            store_next->prev = store_prev;
            store_prev->next = store_next;
            free(next_node);
        }
    }
}

void deleteAfter(struct node **head_ref, int location)
{
    if(*head_ref == NULL)
        printf("List can't be empty\n");
    else
    {
        struct node *new_node = *head_ref;
        int count = countNodes(new_node);

         if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else if(location >= 0 && location <= count - 3)
        {
            struct node *temp_node, *next_node, *store_prev, *store_next;

            temp_node = *head_ref;
            next_node = temp_node->next;

            for(int i=0; i<location; i++)
                next_node = next_node->next;

            store_next = next_node->next;
            store_prev = next_node->prev;
            store_next->prev = store_prev;
            store_prev->next = store_next;
            free(next_node);
        }
        else if(location == count-2)
        {
            struct node *temp_node, *next_node, *store_prev;

            temp_node = *head_ref;
            next_node = temp_node->next;

            for(int i=0; i<location; i++)
                next_node = next_node->next;

            if(next_node->next == NULL)
            {
                store_prev = next_node->prev;
                store_prev->next = NULL;
                free(next_node);
            }
        }
    }
}

void deleteAtLocation(struct node **head_ref, int location)
{
    if(*head_ref == NULL)
        printf("List can't be empty\n");
    else
    {
        struct node *new_node = *head_ref;
        int count = countNodes(new_node);

         if(location >= count)
            printf("No. of elements are less in list\n");
        else if(location < 0)
            printf("Invalid location\n");
        else if(location == 0)
        {
            struct node *prev_node, *next_node, *temp_node;

            prev_node = *head_ref;
            temp_node = *head_ref;
            next_node = temp_node->next;

            *head_ref = next_node;
            (*head_ref)->prev = NULL;
            free(prev_node);
        }
        else if(location > 0 && location <= count - 2)
        {
            struct node *temp_node, *next_node, *store_prev, *store_next;

            temp_node = *head_ref;
            next_node = temp_node->next;

            for(int i=0; i<location-1; i++)
                next_node = next_node->next;

            store_next = next_node->next;
            store_prev = next_node->prev;
            store_next->prev = store_prev;
            store_prev->next = store_next;
            free(next_node);
        }
        else if(location == count - 1)
        {
            struct node *temp_node, *next_node, *store_prev;

            temp_node = *head_ref;
            next_node = temp_node->next;

            for(int i=0; i<location-1; i++)
                next_node = next_node->next;

            if(next_node->next == NULL)
            {
                store_prev = next_node->prev;
                store_prev->next = NULL;
                free(next_node);
            }
        }
    }
}

void printListForward(struct node **head_ref)
{
    struct node *new_node = *head_ref, *back_ref;

    if(*head_ref != NULL)
    {
        printf("Traversal in forward direction\n");
        while (new_node != NULL)
        {
            printf("%d ", new_node->data);
            back_ref = new_node;
            new_node = new_node->next;
        }
        printf("\n");
    }
    else
        printf("You called with empty list\n");
}

void printListReverse(struct node **head_ref)
{
    struct node *new_node = *head_ref, *back_ref;

    if(*head_ref != NULL)
    {
        while(new_node != NULL)
        {
            back_ref = new_node;
            new_node = new_node->next;
        }

        printf("Traversal in reverse direction\n");
        while (back_ref != NULL)
        {
            printf("%d ", back_ref->data);
            back_ref = back_ref->prev;
        }
        printf("\n");
    }
    else
        printf("You called with empty list\n");
}

int countNodes(struct node *head_ref)
{
    int count = 0;

    if( head_ref != NULL)
    {
        while(head_ref != NULL)
        {
            count++;
            head_ref = head_ref->next;
        }
    }
    else
        printf("You called with empty list\n");

    return count;
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
            next = current->next;
            free(current);
            current = next;
        }
        printf("List is free now\n");
        *head_ref = NULL;
    }
}
