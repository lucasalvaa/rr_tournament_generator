#include "matchday.h"

enum Cases {
    FIRST, 
    LAST, 
    NORMAL 
};

// Static function prototypes

/**
 * Populates the array "matches" with n matches 
 * @param matches Array to populate with matches
 * @param n Number of matches to create and insert into the array
 * @param a Queue where to get the first teams
 * @param b Queue where to get the second teams
 * @return True if the generation is successful, otherwise false
 */
static bool matches_generator (match_t** matches, int n, queue_t* a, queue_t* b);

/**
 * Dequeues the items at the top of queues a and b to enqueue them in the right position 
 * for the next matchday according to the circle method algorithm of round robin tournaments.
 * @param c Case of rotation depending on the iteration
 * @param a First queue to operate on
 * @param b Second queue to operate on
 * @return True if rotation is successful, otherwise false
 */
static bool rr_tournament_rotation (enum Cases c, queue_t* a, queue_t* b);

// Implementation

matchday_t* create_matchday (const int id, const int n_matches, queue_t* a, queue_t* b) {
    
    // Creating the pointer to return
    matchday_t* m = MALLOC(matchday_t, 1);
    CHECK_PTR(m, malloc);

    // Struct fields' initialization
    m->id = id;
    m->matches = MALLOC(match_t, n_matches);
    CHECK_PTR(m->matches, malloc);
    
    // Array m->matches is populated by matches_generator function
    // The array will contains this matchday's matches 
    if(!matches_generator(m->matches, n_matches, a, b)) {
        printf("Matchday %d generation failed\n", id);
        exit(EXIT_FAILURE);
    }
    
    return m;
}

static bool matches_generator (match_t** matches, int n, queue_t* a, queue_t* b) {
    team_id_t hm, aw;   // Variables that will contain the two teams fetched at each iteration
    match_t* match;     // Temporary pointer to the i-th match
    
    for (int i=0; i<n; i++) {
        // Teams are fetched by the queues 
        hm = (IS_ODD(i))
            ? queue_top(a)
            : queue_top(b);
        aw = (IS_ODD(i))
            ? queue_top(b)
            : queue_top(a);

        // Once teams are fetched by the queues, the match is created and pushed into the array
        match = create_match (hm, aw);
        matches[i] = match;

        // The rotation of the queues is made up by granting the 
        // rotation system needed by the circular method algorithm
        enum Cases c = (i == 0)
            ? FIRST 
            : i == (n-1)
                ? LAST
                : NORMAL;
        if(!rr_tournament_rotation (c, a, b)) {
            return false;
        }

    }

    return true;
} 

static bool rr_tournament_rotation (enum Cases c, queue_t* a, queue_t* b) {
    // After a match is generated, teams are dequeued and enqueued back
    // in the queues so that the circle method algorithm is tutelated
    // and that the items in the queues are in the correct position for the next matchday
    team_id_t t1 = queue_dequeue(a);
    team_id_t t2 = queue_dequeue(b);
    bool flag;
    switch(c) {
        // Teams fetched to generate the first match of the matchday must to be enqueued both in queue a
        case FIRST:
            flag = queue_enqueue(a, t1) && queue_enqueue(a, t2);
            break;
        // Teams fetched to generate the last match of the matchday must to be enqueued both in queue b
        // In this case, the second team fetched must be enqueued before the other
        case LAST:
            flag = queue_enqueue(b, t2) && queue_enqueue(b, t1);
            break;
        // For every other match, teams must to be enqueued back to the same queue they've been fetched from
        case NORMAL:
            flag = queue_enqueue(a, t1) && queue_enqueue(b, t2);
            break;
        default:
            flag = false;
            break;
    }

    return flag;
}


