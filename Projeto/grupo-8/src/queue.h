//typedef struct queueCircular {
//    int valor;
//    struct queueCircular * next;
//} * QueueC;

typedef struct queueCircular {
    int id;
    int status; //0 = pending, 1 = processing
    char ** args;
    struct queueCircular * next;
} * QueueC;

void initQueueC (QueueC *qc);

int QisEmptyC (QueueC *qc);

void frontC (QueueC *qc, char *** args);

void enqueueC (QueueC *qc, char *** args);

int dequeueC (QueueC *qc); //por a dar dequeue por id (o n elemento da queue pode demorar menos que o da frente)