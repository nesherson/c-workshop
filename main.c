#include <stdio.h>
#include <stdlib.h>

struct TestNode
{
    int data;
    struct TestNode *next;
    struct TestNode *prev;
};

struct TestNode *CreateNode(int data)
{
    struct TestNode *node = (struct TestNode *)malloc(sizeof(struct TestNode));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void InsertDataAtBeginning(struct TestNode **node, int data)
{
    if (node == NULL)
    {
        (*node) = CreateNode(data);
    }
    else
    {
        struct TestNode *newNode = CreateNode(data);
        newNode->next = (*node);
        (*node)->prev = newNode;
        (*node) = newNode;
    }
}

void InsertDataAtEnd(struct TestNode **node, int data)
{
    struct TestNode *newNode = CreateNode(data);

    if ((*node)->next == NULL)
    {
        (*node)->next = newNode;
        return;
    }
    else
    {
        InsertDataAtEnd(&(*node)->next, data);
    }
}

void PrintNodes(struct TestNode **node)
{
    struct TestNode *currentNode = (*node);
    int counter = 1;

    while (currentNode != NULL)
    {
        printf("Node %d. ", counter++);
        printf(" %d\n", currentNode->data);
        currentNode = currentNode->next;
    };
}

void DeleteNodes(struct TestNode **node)
{
    struct TestNode **currentNode = node;

    while (currentNode != NULL)
    {
        struct TestNode *nextNode = (*currentNode)->next;

        free(currentNode);
        currentNode = NULL;

        if (nextNode != NULL)
        {
            currentNode = &nextNode;
        }
    };

    printf("Nodes cleared!\n");
}

struct TestNode *GetNode(struct TestNode** node, int data)
{
    if ((*node)->data == data)
    {
        return (*node);
    }

    return GetNode(&(*node)->next, data);
}

int main()
{
    struct TestNode *testNode = CreateNode(5);

    InsertDataAtBeginning(&testNode, 3);
    InsertDataAtEnd(&testNode, 7);
    InsertDataAtEnd(&testNode, 2);
    InsertDataAtEnd(&testNode, 10);
    InsertDataAtEnd(&testNode, 15);
    InsertDataAtBeginning(&testNode, 100);

    struct TestNode* searchedNode = GetNode(&testNode, 10);

    PrintNodes(&testNode);
    DeleteNodes(&testNode);

    return 0;
}
