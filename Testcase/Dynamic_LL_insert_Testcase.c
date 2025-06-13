#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int insertLL(Node **head, int index, int value) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) return 0; 

    newNode->data = value;
    newNode->next = NULL;

    if (index == 0) {
        newNode->next = *head;
        *head = newNode;
        return 1;
    }

    Node *prev = *head;
    for (int i = 0; i < index - 1; i++) {
        if (!prev) {
            free(newNode);
            return 0;
        }
        prev = prev->next;
    }

    newNode->next = prev->next;
    prev->next = newNode;

    return 1;
}


int main() {
    Node *head = NULL;

    insertLL(&head, 0, 10);
    insertLL(&head, 1, 20);
    insertLL(&head, 1, 15);
    insertLL(&head, 3, 30);
    insertLL(&head, 0, 5);

    printList(head);
    
    Node *cur = head;
    while (cur) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }

    return 0;
}
