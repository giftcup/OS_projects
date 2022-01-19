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
void swap(List **current, List **next);
List* join_list(List *head1, List *head2);

int main(void) {
    List *head = NULL;
    List *head2 = NULL;

    int i = 0;

    for (int i = 0; i < 10; i ++) {
        head = push_to_stack(head, i+1);
    }
    for (int i = 10; i < 20; i ++) {
        head2 = push_to_stack(head2, i+1);
    }
    // head = push_to_stack(head, 7);
    // head = push_to_stack(head, 3);
    // head = push_to_stack(head, 5);
    // head = push_to_stack(head, 2);
    // head = push_to_stack(head, 1);
    head = join_list(head, head2);
    bubble_sort(&head);

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
    List* cur, *prev, *next;
    bool swapped;
    int i = 0;

    do {  
        swapped = false;
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
            }
            prev = cur;
            cur = next;
            next = next->next;
        }
    } while (swapped);
}

void swap(List **current, List **next) {
    List *temp, *tempNext;
    tempNext = (*current)->next;
    temp = *current;
    printf("1. %p %p\n", temp->next, (*current)->next);
    printf("   %p\n", tempNext->next);
    *current = *next;
    printf("2. %p %p\n", (*next)->next, (*current)->next);
    *next = temp;
    (*next)->next = tempNext;
    printf("3. %p %p\n", (*next)->next,tempNext);
}

List* join_list(List *head1, List *head2) {
    if (head1->next == NULL) {
        head1->next = head2;
        return head1;
    }
    join_list(head1->next, head2);
    return head1;
}