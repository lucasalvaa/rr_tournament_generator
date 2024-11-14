#include "tournament.h"

int main (int argc, char** argv) {
    char name[TOURNAMENT_NAME_MAX_LEN];
    int n_teams;

    // ./rr_tournament.exe "[name]" [number of teams]
    // argv[0] = executable name
    // argv[1] = name to assign to your tournament
    // argv[2] = number of teams of your tournament
    if (argc == 3) {
        strcpy(name, argv[1]);
        n_teams = atoi(argv[2]);
    }
    else {
        strcpy(name, "Your tournament");
        n_teams = 10;
    }

    tournament_t* t = create_rr_tournament(name, n_teams);
    tournament_print_schedule(t);
    return 0;
}
