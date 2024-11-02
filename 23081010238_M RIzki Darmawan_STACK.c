#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

struct stack {
    node *top;
    int count;
};
typedef struct stack Stack;

void createStack(Stack *s) {
    s->top = NULL;
    s->count = 0;
}

int isEmpty(Stack *s) {
    return s->count == 0;
}

int stackCount(Stack *s) {
    return s->count;
}

int push(Stack *s, int data) {
    node *pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal\n");
        return 0;
    }
    pNew->data = data;
    pNew->next = s->top;
    s->top = pNew;
    s->count++;
    return 1;
}

int pop(Stack *s, int *dataOut) {
    if (isEmpty(s)) {
        printf("Stack kosong!\n");
        return 0;
    }
    node *pDel = s->top;
    *dataOut = pDel->data;
    s->top = s->top->next;
    free(pDel);
    s->count--;
    return 1;
}

int top(Stack *s, int *dataOut) {
    if (isEmpty(s)) {
        printf("Stack kosong!\n");
        return 0;
    }
    *dataOut = s->top->data;
    return 1;
}

void destroyStack(Stack *s) {
    while (!isEmpty(s)) {
        int temp;
        pop(s, &temp);
    }
}

void displayStack(Stack *s) {
    node *pWalker = s->top;
    printf("Isi stack: ");
    while (pWalker != NULL) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }
    printf("NULL\n");
}

int main() {
    Stack s;
    createStack(&s);
    int dataOut;

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    displayStack(&s);
    printf("Jumlah elemen dalam stack: %d\n", stackCount(&s));

    if (top(&s, &dataOut))
        printf("Data teratas: %d\n", dataOut);

    if (pop(&s, &dataOut))
        printf("Data yang di-pop: %d\n", dataOut);

    displayStack(&s);
    printf("Jumlah elemen dalam stack setelah pop: %d\n", stackCount(&s));

    destroyStack(&s);
    printf("Stack dikosongkan.\n");

    return 0;
}
