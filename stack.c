#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list {
    int data;
    struct list *next;
} List;


List* push_to_stack(List *head, int num);
int pop_from_stack(List **head);
int top_of_stack(List *head);
void reverse_print(List *head);
void bubble_sort(List **head);

int main(void) {
    List *head = NULL;
    int i = 0;

    // for (int i = 0; i < 10; i ++) {
    //     head = push_to_stack(head, i+1);
    // }

    head = push_to_stack(head, 3);
    head = push_to_stack(head, 5);
    head = push_to_stack(head, 2);
    head = push_to_stack(head, 1);
    head = push_to_stack(head, 7);

    printf("%d ", i);
    while (i < 5) {
        printf("%d ", i);
        bubble_sort(&head);
        i++;
    }printf("\n");

    while (head != NULL) {
        printf("%d->", head->data);
        head = head->next;
    }
    printf("NULL\n");
    return 0;
}

List* push_to_stack(List *head, int num) {
    List *newNode = malloc(sizeof(List));

    newNode->data = num;
    newNode->next = head;
    if (head == NULL) {
        newNode->next = NULL;
    }
    head = newNode;

    // free(newNode);
    return head;
}

int pop_from_stack(List **head) {
    int top_data = (*head)->data;
    List *top = *head;

    *head = (*head)->next;
    free(top);

    return top_data;  
}

int top_of_stack(List *head) {
    return head->data;
}

void reverse_print(List *head) {
    if (head == NULL) 
        return;
    reverse_print(head->next);
    printf("%d->", head->data);
}

void bubble_sort(List **head) {
    // printf("h..");
    List* cur, *prev, *next;
    bool swapped = true;
    int i = 0;
        
    cur = (*head);
    prev = NULL;
    next = cur->next;
    
    while (next != NULL) {
        if (cur->data > next->data) {
            if (prev == NULL) {
                (*head)->next = next->next;
                next->next = (*head);
                (*head) = next;
            }
            else {
                cur->next = next->next;
                prev->next = next;
                next->next = cur;
            }
            swapped = true;
            continue;
        }
            printf("emh..");
    }
}