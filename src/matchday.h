#include "match.h"
#include "queue.h"

typedef struct {
    int id;             // Matchday identificator 
    match_t** matches;  // Array containing the matches of the matchday
} matchday_t;

/**
 * Create a matchday and populates it with their matches
 * @param id Matchday identificator, must be an integer bigger than zero
 * @param n_matches Number of matches to play in the matchday
 * @param a Queue where to get the first teams
 * @param b Queue where to get the second teams 
 * @return A matchday_t pointer that already contains its matches
 */
matchday_t* create_matchday (const int id, const int n_matches, queue_t* a, queue_t* b);
