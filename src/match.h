#include "utils.h"

typedef struct {
    team_id_t teams[2]; // teams[0] contains the home team, teams[1] contains the away team
} match_t;

/**
 * Create and return a match_t pointer to a match where home_team challenges away_team
 * @param home_team The id of the team playing at home in this match
 * @param away_team The id of the team playing away in this match
 * @return A match_t pointer
 */
match_t* create_match (team_id_t home_team, team_id_t away_team);

/**
 * Return the id of the team that plays at home in match m
 * @param m Match from which to get the home team id
 * @return The home team id
 */
team_id_t match_get_home_team (match_t* m);

/**
 * Return the id of the team that plays away in match m
 * @param m Match from which to get the away team id
 * @return The away team id
 */
team_id_t match_get_away_team (match_t* m);