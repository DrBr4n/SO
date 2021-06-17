#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

printf("testing\n");

void initQueueC (QueueC *qc) {
    *qc = malloc(sizeof(struct queueCircular));
    (*qc)->id = NULL;
    (*qc)->status = NULL;
    (*qc)->args = NULL;
    (*qc)->next = NULL;
}

int QisEmptyC (QueueC *qc) {
    return ((*qc)->next == NULL);    
}

int frontC (QueueC *qc, char *** args) {
    if (QisEmptyC(qc)) 
        return 1;
    else 
        *args = (*qc)->next->args;
    return 0;
}

void enqueueC (QueueC *qc, char *** args) {

    QueueC new = malloc(sizeof(struct queueCircular));
    new->id = (*qc)->next->id + 1;
    new->status = 0;
    new->args = args;
    new->next = NULL;

    if (QisEmptyC(qc)) {
        *qc = new;
        new->next = new; //apontar para a propria celula visto que é circular
    } else {
        new->next = (*qc)->next; //apontar para o primeiro elemento
        (*qc)->next = new; //fazer com que o penultimo elemento aponte para o ultimo
        *qc = new; //apontar para o ultimo elemento
    }
}

int dequeueCC (QueueC *qc) {
    if (QisEmptyC(qc)) {
        return 1;
    } else {
        if (*qc == (*qc)->next) {
            (*qc)->next = NULL;
        } else {
            (*qc)->next = (*qc)->next->next;
        }
    }
}



int main() {
  
    QueueC q;
    initQueueC(&q);
    printf("QisEmpty: %d\n", QisEmptyC(&q));
    enqueueC(&q, 2);
    enqueueC(&q, 4);
    printf("QisEmpty: %d\n", QisEmptyC(&q));
    enqueueC(&q, 6);
    enqueueC(&q, 8);
    int x, y, k, h, j;
    frontC(&q, &x);
    printf("%d", x);
    dequeueCC(&q);
    dequeueCC(&q);
    dequeueCC(&q);
    dequeueCC(&q);
    printf("y: %d\n", y);
    printf("k: %d\n", k);
    printf("h: %d\n", h);
    printf("j: %d\n", j);

  return 0;
}
