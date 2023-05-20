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
void* allocate_memory(size_t size);
void check_null(void* ptr);

void ReadPlayers(PD* Players, int nr_playeri, FILE* fisier);
void ReadTeamDetails(TL** head, char* Nume_Echipa, int Nr_Playeri, FILE* fisier);
void ReadTeamList(TL** head, int* Nr_Echipe,FILE* fisier);
void DisplayTeams(TL* head, int Nr_Echipe, FILE* fisier);

int NrMaxPosibil(int Nr_Echipe);
void TeamPoints(TL* head, int Nr_Echipe);
void DeleteTeam(TL** head, float min);
void RemoveTeams(TL** head, int* Nr_Echipe);

CE* createQueue();
void enqueue(CE* q, TD t1, TD t2);
void dequeue(CE* q, TD* t1, TD* t2);
void addTeamsToQueue(TL* teamsList, CE* matchesQueue);
void afiseazaMeciuri(CE* coada, FILE* fisier);
void pushStiva(SE** top, TD team);
TD popStiva(SE** top);
void printStiva(SE* top, FILE* fisier);
void deleteQueue(CE* q);
void clearStack(SE** top);
void deleteStack(SE* top);
void addTeamsFromStackToQueue(SE** top, CE* matchesQueue);
void processMatches(CE* matchesQueue, SE** winnersStack, SE** losersStack);
void addTeamsToTL(TL** head, SE* stiva);
void AfisareTask3(TL* head, int Nr_Echipe, FILE* fisier, TL** echipe_ramase);

NAE* newNode(TD data);
NAE* insertNAE(NAE* node, TD key);
void inorderRightToLeft(NAE* root, FILE* fisier);
NAE* AfisareTask4(TL* head, NAE* arbore, FILE* fisier);

int max(int a, int b);
int nodeHeight(AVL* root);
AVL* rightRotation(AVL* z);
AVL* leftRotation(AVL* z);
AVL* LRRotation(AVL* Z);
AVL* RLRotation(AVL* Z);
AVL* balanceAVL(AVL* node, TD key);
AVL* insertAVL(AVL* node, TD key);
void insertTeam(TL** tl_head, TD team);
void transferDataNAEtoTL(NAE* nae, TL** tl_head);
AVL* transferTLtoAVL(TL* list);
void inorderRightToLeftAVL(AVL* root, FILE* fisier);
void reverseTL(TL** head);
void AfisareTask5(TL* lista, AVL* echipe, FILE* fisier);
