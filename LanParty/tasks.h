#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
struct MeciuriEchipe
{
    TD Team1;
    TD Team2;
    struct MeciuriEchipe *next;
};
typedef struct MeciuriEchipe ME;
struct CoziEchipe
{
    ME *front,*rear;
};
typedef struct CoziEchipe CE;
struct StivaEchipe
{
    TD Team;
    struct StivaEchipe* next;
};
typedef struct StivaEchipe SE;
struct NodArboreEchipe
{
    TD Team;
    struct NodArboreEchipe *left,*right;
};
typedef struct NodArboreEchipe NAE;
struct NodArboreEchipeAVL
{
    int height;
    TD Team;
    struct NodArboreEchipeAVL *left,*right;
};
typedef struct NodArboreEchipeAVL AVL;
