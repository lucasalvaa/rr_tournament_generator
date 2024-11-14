#include "utils.h"

// In the next two lines you can manually set the item type and its null value 
typedef team_id_t item;
#define NULLITEM -1

typedef struct {
    item* items;    // A circular array is used to implement the queue
    int front;      
    int rear;
    int size;
} queue_t;

/**
 * Create and return a new empty queue of a given size
 * @param size The size the queue should be. It must be an integer value bigger than zero
 * @return A queue_t pointer, or NULL if size value is not valid
 */
queue_t* create_queue (item size);

/**
 * Check if q is a pointer to a valid queue
 * @param q The queue on which the check is to be performed
 * @return True if queue is a pointer to a valid queue, otherwise false
 */
bool queue_isValid (queue_t* q);

/**
 * Check if the queue q is empty
 * @param q The queue on which the check is to be performed
 * @return True if the queue q is empty, otherwise false
 */
bool queue_isEmpty (queue_t* q);

/**
 * Check if the queue q is full
 * @param q The queue on which the check is to be performed
 * @return True if the queue q is full, otherwise false
 */
bool queue_isFull (queue_t* q);

/**
 * Insert a new element at the end of the queue
 * @param q The queue to insert the element into
 * @param e The element to be inserted
 * @return True if the insertion is successful, otherwise false
 */
bool queue_enqueue (queue_t* q, item e);

/**
 * Remove and return the element at the top of the queue
 * @param q The queue to remove the element from
 * @return The top item of the queue if q is valid and not empty, otherwise NULLITEM
 */
item queue_dequeue (queue_t* q);

/**
 * Return the element at the top of the queue without removing it from the queue
 * @param q The queue to get the element from
 * @return The top item of the queue if q is valid and not empty, otherwise NULLITEM
 */
item queue_top (queue_t* q);