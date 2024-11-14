#include "tournament.h" 

/**
 * Populates the array arr with a random sequence of numbers between 0 and size-1
 * @param arr Pointer to the array to populate
 * @param size Size of the array arr
 */
static void rnd_sequence (int arr[], int size);

/**
 * Populates queues a and b with two random sequences of numbers between 0 and n-1
 * No number present in one queue will also be present in the other
 * @param a First queue to populate
 * @param b Second queue to populate
 * @param n Amount of numbers to generate (real range is 0 to n-1)
 */
static void populate_queues (queue_t* a, queue_t* b, int n);

// Implementation

tournament_t* create_rr_tournament (const char* name, int n) {
    
    if (n < 2) { // A tournament must have at least two teams
        return NULL;
    }

    tournament_t* t = (tournament_t*) MALLOC(tournament_t, 1);
    CHECK_PTR(t, malloc);

    // The fields of the struct pointed by t are populated here
    strlen(name) < TOURNAMENT_NAME_MAX_LEN 
        ? strcpy(t->name, name) 
        : NULL;
    t->n_teams = n;
    t->odd_tournament = IS_ODD(n);

    /**
     * If the number of teams of tournament t is odd, the tournament
     * will have n matchdays, because each team needs n-1 matchdays
     * to play every other team, and one more matchday to rest.
     */
    int matchdays = t->odd_tournament
        ? t->n_teams 
        : (t->n_teams - 1);
    t->matchdays = (matchday_t**) MALLOC(matchday_t*, matchdays);
    CHECK_PTR(t->matchdays, malloc);
    
    /** If the number of teams of tournament t is odd, for each matchday,
     * the team that is supposed to face team 0 will rest.
     * That's why we need one more virtual team.
     */
    int virtual_teams = t->odd_tournament 
        ? n+1 
        : n;

    // Queue a must have one slot more than queue b to allow the queues to rotate correctly 
    // according to the circle method used in the scheduling algorithm for round robin tournaments
    queue_t* a = create_queue((virtual_teams/2)+1); 
    queue_t* b = create_queue(virtual_teams/2);
    // Queues are populated by generating a random sequence of numbers from range 0 to virtual_teams-1
    populate_queues(a, b, virtual_teams);   

    // Matchdays and relative matches are created here
    #define MATCHES_FOR_MATCHDAY (virtual_teams/2)
    for (int i=0; i<matchdays; i++) {
        t->matchdays[i] = create_matchday(i+1, MATCHES_FOR_MATCHDAY, a, b);
    }

    return t;
}

void tournament_print_schedule (tournament_t* t) {
    /**
     * If the number of teams of tournament t is odd, the tournament
     * will have n matchdays, because each team needs n-1 matchdays
     * to play every other team, and one more matchday to rest.
     */ 
    int n_matchdays = t->odd_tournament 
        ? t->n_teams 
        : (t->n_teams-1);

    printf("Tournament name: %s\nNumber of teams: %d\n\n", t->name, t->n_teams);

    for (int d = 1; d <= n_matchdays; d++) {
        tournament_print_matchday(t, d);
        printf("\n");
    }
}

void tournament_print_matchday (tournament_t* t, int d) {
    /**
     * The number of matches for each matchday depends on the number of teams in the tournament (n).
     * If n is even, each matchday will have n/2 games.
     * If n is odd, there should be (n-1)/2 matches, but here the number of matches equals (n+1)/2.
     * That's why we need one more match to find the resting team: if a team x is matched with the team
     * represented by OPPONENT_REST value, x will rest in that matchday:
     * Consequentially, the number of effective matches will equals (n-1)/2
     */
    int n_matches = (t->odd_tournament
        ? (t->n_teams+1)
        : (t->n_teams)) / 2;

    /**
     * Argument d admits values in range between 1 and the number of matchdays of the tournament.
     * At the same time, the array is indexed from 0 to the number of matchdays minus one.
     */
    matchday_t* matchday = t->matchdays[d-1];
    
    match_t* match;         // Pointer to the i-th match
    team_id_t home_team = 0, away_team = 0;
    team_id_t resting_team = 0;   // The team that rest in this matchday if t has an odd number of teams

    printf("Matchday %d:\n", d);

    for (int i=0; i<n_matches; i++) {
        match = matchday->matches[i];
        home_team = match_get_home_team(match);
        away_team = match_get_away_team(match);
        
        /** 
         * If the number of teams in tournament t is odd and the value of one among home team
         * and away team equals OPPONENT_RESTS's value, it means the other team
         * is supposed to rest in this matchday. Consequentially, we don't have to print 
         * the information about this match, but we have to flag that this team rests.
         */
        #define OPPONENT_RESTS 0
        if (t->odd_tournament && (home_team == OPPONENT_RESTS || away_team == OPPONENT_RESTS)) {
            resting_team = (home_team == OPPONENT_RESTS) 
                ? away_team 
                : home_team;
            continue;
        }
        
        // Informations about the i-th match are printed here
        printf("%d-%d\n", home_team, away_team);
    }

    if (t->odd_tournament) {
        printf("Team %d rests this matchday\n", resting_team);
    }
}

static void rnd_sequence (int arr[], int size) {
    // This array keeps track of which teams have already been drawn
    bool drawn[size];
    for(int k=0; k<size; k++) {
        drawn[k] = false;
    }
    // The random number generation seed depends on the instant 
    // of time in which the following operation is performed
    srand(time(NULL));

    int team, i=0;
    while(i < size) {
        team = RAND_GENERATOR(size-1);
        if(!drawn[team]) {
            drawn[team] = true;
            arr[i++] = team;
        }
    }
}

static void populate_queues (queue_t* a, queue_t* b, int n) {
    // First, a random sequence of numbers between 0 and n-1 is generated
    team_id_t arr[n];
    rnd_sequence(arr, n);
    /** 
     * Queue a is populated taking elements from the left side of the array
     * Queue b is populated taking elements from the right side of the array
     * This method allows to initialize queues according to the standard circle method algorithm
     * More info on https://en.wikipedia.org/wiki/Round-robin_tournament#Circle_method
     */
    for(int i=0; i<n/2; i++) {
        queue_enqueue(a, arr[i]);
        queue_enqueue(b, arr[n -1 -i]);
    }
}
