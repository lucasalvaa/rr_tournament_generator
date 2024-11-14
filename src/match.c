#include "match.h"

#define HOME_TEAM m->teams[0]
#define AWAY_TEAM m->teams[1]

match_t* create_match (team_id_t home_team, team_id_t away_team) {
    match_t* m = MALLOC(match_t, 1);
    CHECK_PTR(m, malloc);

    HOME_TEAM = home_team;
    AWAY_TEAM = away_team;

    return m;
}

team_id_t match_get_home_team (match_t* m) {
    return HOME_TEAM;
}

team_id_t match_get_away_team (match_t* m) {
    return AWAY_TEAM;
}
