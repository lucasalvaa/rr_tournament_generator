#include "matchday.h"

#define TOURNAMENT_NAME_MAX_LEN 128

typedef struct {
    char name[TOURNAMENT_NAME_MAX_LEN]; // Name of the tournament
    int n_teams;                        // Number of teams of the tournament
    bool odd_tournament;                // Flag set to true if n_teams is an odd number
    matchday_t** matchdays;             // Array that contains every matchday of the tournament
} tournament_t;

/**
 * Creates a calendar of a sports tournament that follows the
 * round robin tournament format, where each team plays against all the others.
 * 
 * Given a number of teams equal to n:
 *  - if n is even, there will be n-1 matchdays, each one with n/2 matches
 *  - else if n is odd, there will be n matchdays, 
 *      each one with (n-1)/2 matches and a team that rests
 * This program implements the circle method and generates the sequence of numbers
 * using the rand() function from the stdlib, so that a different calendar is generated each time
 * 
 * More info about round robin tournaments and the circle method on:
 * https://en.wikipedia.org/wiki/Round-robin_tournament
 *
 * @param name Name to assign to the tournament
 * @param n Number of teams in the tournament (must be an integer greater than or equal to 2)
 * @return A tournament_t pointer to a tournament whose matchdays have already been generated
 */
tournament_t* create_rr_tournament (const char* name, int n);

/**
 * Prints the tournament name, the number of its teams and the matches of eatch matchday
 * @param t Pointer to the tournament struct to print
 */
void tournament_print_schedule (tournament_t* t);

/**
 * Prints informations about each match of the matchday d in tournament t
 * @param t Pointer to the tournament struct of the matchday to print
 * @param d Number of the matchday to print (must be a number between 1 and the amount of matchday of t)
 */
void tournament_print_matchday (tournament_t* t, int d);