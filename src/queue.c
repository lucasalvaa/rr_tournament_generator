#include "queue.h"

static int shift_index (int index, int size);

queue_t* create_queue (item size) {

    if (size <= 0) {
        return NULL;
    }

    queue_t* q = (queue_t*) MALLOC(queue_t, 1);
    CHECK_PTR(q, malloc);
    q->items = (item*) MALLOC(item, size);
    CHECK_PTR(q->items, malloc);
    q->size = size;
    q->front = -1;
    q->rear = -1;

    return q;
}

bool queue_isValid (queue_t* q) {
    return (q != NULL) && (q->size > 0) && (q->items != NULL);
}

bool queue_isEmpty (queue_t* q) {
    return queue_isValid(q) && (q->front == -1);    
}

bool queue_isFull (queue_t* q) {
    return queue_isValid(q) && 
        ((q->front == (q->rear + 1) % q->size) 
            || (q->front == 0 && q->rear == (q->size - 1)));
}

bool queue_enqueue (queue_t* q, item e) {
    if (queue_isFull(q)) {
        return false;
    }
    
    if(q->front == -1) {
        q->front = 0;
    }

    q->rear = shift_index(q->rear, q->size);
    q->items[q->rear] = e;

    return true;
}

item queue_dequeue (queue_t* q) {
    item e;

    if (queue_isEmpty(q)) {
        return NULLITEM;
    }

    e = queue_top(q);

    // Check to handle the case where the queue has only one item inside
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    else {
        q->front = shift_index(q->front, q->size);
    }

    return e;
}

item queue_top (queue_t* q) {
    if (queue_isEmpty(q)) {
        return NULLITEM;
    }

    return q->items[q->front];
}

static int shift_index (int index, int size) {
    return (index + 1) % size;
}

