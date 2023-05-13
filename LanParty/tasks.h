#include <stdio.h>
#include <stdlib.h>

struct PlayerDetails
{
    char* firstName;
    char* secondName;
    int points;
};
typedef struct PlayerDetails PD;
struct TeamDetails
{
    int Nr_Players;
    char* Team_Name;
    PD* Players;
    float PuncteEchipa;
};
typedef struct TeamDetails TD;
struct TeamList
{
    TD Team;
    struct TeamList *next;
};
typedef struct TeamList TL;

