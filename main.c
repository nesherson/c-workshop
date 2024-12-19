#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *CreateNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

int GetLength(struct Node **head)
{
    int length = 0;
    struct Node *currentNode = (*head);

    while (currentNode != NULL)
    {
        length++;
        currentNode = currentNode->next;
    };

    return length;
}

void InsertDataAtBeginning(struct Node **head, int data)
{
    if (head == NULL)
    {
        (*head) = CreateNode(data);
    }
    else
    {
        struct Node *newNode = CreateNode(data);
        newNode->next = (*head);
        (*head)->prev = newNode;
        (*head) = newNode;
    }
}

void InsertDataAtEnd(struct Node **node, int data)
{
    struct Node *newNode = CreateNode(data);

    if ((*node)->next == NULL)
    {
        (*node)->next = newNode;
        newNode->prev = (*node);

        return;
    }
    else
    {
        InsertDataAtEnd(&(*node)->next, data);
    }
}

void InsertDataAtPosition(struct Node** head, int data, int position)
{
    if (GetLength(head) <= position)
    {
        return;
    }

    struct Node *currentNode = (*head);
    struct Node *newNode = CreateNode(data);
    int counter = 0;

    while (currentNode != NULL)
    {
        if (counter == position)
        {
            newNode->prev = currentNode->prev;
            newNode->next = currentNode;
            currentNode->prev->next = newNode;
            currentNode->prev = newNode;
            break;
        }

        currentNode = currentNode->next;
        counter++;
    };
}

void DeleteDataAtBeginning(struct Node** head)
{
    struct Node *currentNode = (*head);
    struct Node *nextNode = (*head)->next;

    free(currentNode);
    currentNode = NULL;
    nextNode->prev = NULL;
    (*head) = nextNode;
}

// 0 1 2 3 4 5 6

void PrintNodes(struct Node **head)
{
    struct Node *currentNode = (*head);
    int counter = 1;

    while (currentNode != NULL)
    {
        printf("Node %d. ", counter++);
        printf(" %d\n", currentNode->data);
        currentNode = currentNode->next;
    }; 
}

void FreeNodesFromMemory(struct Node **node)
{
    struct Node **currentNode = node;

    while (currentNode != NULL)
    {
        struct Node *nextNode = (*currentNode)->next;

        free(currentNode);
        currentNode = NULL;

        if (nextNode != NULL)
        {
            currentNode = &nextNode;
        }
    };

    printf("Nodes cleared!\n");
}

struct Node *GetNode(struct Node **node, int data)
{
    if ((*node) == NULL)
    {
        return NULL;
    }

    if ((*node)->data == data)
    {
        return (*node);
    }

    return GetNode(&(*node)->next, data);
}


//TODO:
// Add deletion at end
// Add deletion at certain position


int main()
{
    struct Node *testNode = CreateNode(5);
    InsertDataAtEnd(&testNode, 7);
    InsertDataAtEnd(&testNode, 2);
    // InsertDataAtEnd(&testNode, 10);
    // InsertDataAtEnd(&testNode, 15);
    // InsertDataAtBeginning(&testNode, 100);
    // InsertDataAtPosition(&testNode, 150, 2);

    struct Node *searchedNode = GetNode(&testNode, 10);
    int nodeLength = GetLength(&testNode);

    DeleteDataAtBeginning(&testNode);

    PrintNodes(&testNode);
    printf("Node length -> %d\n", nodeLength);
    FreeNodesFromMemory(&testNode);

    return 0;
}
