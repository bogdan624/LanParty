#include "tasks.h"

void* allocate_memory(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("Alocare esuata!\n");
        exit(1);
    }
    return ptr;
}

void check_null(void* ptr) {
    if (ptr == NULL) {
        printf("Error: The pointer is NULL!\n");
        exit(1);
    }
}

/*----------------------------TASK1 INCEPUT----------------------------------*/
void ReadPlayers(PD *Players, int nr_playeri, FILE* fisier) {
    char nume[30], prenume[30];
    int puncte;
    for(int i = 0; i < nr_playeri; ++i) {
        fscanf(fisier, "%s %s %d", nume, prenume, &puncte);
        Players[i].firstName = allocate_memory((strlen(nume) + 1) * sizeof(char));
        Players[i].secondName = allocate_memory((strlen(prenume) + 1) * sizeof(char));
        strcpy(Players[i].firstName, nume);
        strcpy(Players[i].secondName, prenume);
        Players[i].points = puncte;
    }
}

void ReadTeamDetails(TL **head, char* Nume_Echipa, int Nr_Playeri, FILE* fisier) {
    TL *newNode = allocate_memory(sizeof(TL));
    newNode->Team.Nr_Players = Nr_Playeri;
    newNode->Team.Team_Name = allocate_memory((strlen(Nume_Echipa) + 1) * sizeof(char));
    strcpy(newNode->Team.Team_Name, Nume_Echipa);
    newNode->Team.Players = allocate_memory(Nr_Playeri * sizeof(PD));
    ReadPlayers(newNode->Team.Players, newNode->Team.Nr_Players, fisier);
    newNode->next=*head;
    *head=newNode;
}

void ReadTeamList(TL **head, int *Nr_Echipe) {
    FILE* fisier = fopen("d.in", "rt");
    check_null(fisier);
    int Nr = 0;
    fscanf(fisier, "%d", &Nr);
    *Nr_Echipe = Nr;
    int Nr_Playeri;
    char Nume_Echipa[50];
    for(int i = 0; i < Nr; ++i) {
        fscanf(fisier, "%d", &Nr_Playeri);
        fgetc(fisier);
        fgets(Nume_Echipa, 50, fisier);
        Nume_Echipa[strlen(Nume_Echipa)-1] = NULL;
        ReadTeamDetails(head, Nume_Echipa, Nr_Playeri, fisier);
    }
    fclose(fisier);
}

void DisplayTeams(TL *head, int Nr_Echipe,FILE *fisier) {
    for(int i = 0; i < Nr_Echipe; ++i) {
        fprintf(fisier,"%s\n",head->Team.Team_Name);
        head = head->next;
    }
}
/*----------------------------TASK1 SFARSIT----------------------------------*/

/*----------------------------TASK2 INCEPUT----------------------------------*/
int NrMaxPosibil(int Nr_Echipe) {
    int NrPosibil = 1;
    while (NrPosibil < Nr_Echipe) {
        NrPosibil = NrPosibil * 2;
    }
    NrPosibil = NrPosibil / 2;
    return NrPosibil;
}
void TeamPoints(TL *head, int Nr_Echipe) {
    TL *aux = head;
    for (int i = 0; i < Nr_Echipe; ++i) {
        float pct = 0;
        aux->Team.PuncteEchipa=0;
        for (int j = 0; j < aux->Team.Nr_Players; ++j) {
            pct += aux->Team.Players[j].points;
        }
        aux->Team.PuncteEchipa = (float)pct / aux->Team.Nr_Players;
        aux = aux->next;
    }
}
void DeleteTeam(TL** head, float min) {
    if (*head == NULL) {
        return;
    }
    TL* nodeToDelete = *head;
    if (nodeToDelete->Team.PuncteEchipa == min) {
        *head = nodeToDelete->next;
        free(nodeToDelete);
        return;
    }
    TL* prevNode = *head;
    nodeToDelete = nodeToDelete->next;
    while (nodeToDelete != NULL) {
        if (nodeToDelete->Team.PuncteEchipa == min) {
            prevNode->next = nodeToDelete->next;
            free(nodeToDelete);
            return;
        }
        prevNode = nodeToDelete;
        nodeToDelete = nodeToDelete->next;
    }
}
void RemoveTeams(TL **head, int *Nr_Echipe) {
    int NrPosibil = NrMaxPosibil(*Nr_Echipe);
    int NrEchipe = *Nr_Echipe;
    TeamPoints(*head, NrEchipe);
    while (NrEchipe > NrPosibil) {
        TL *aux = *head;
        float min = aux->Team.PuncteEchipa;
        while (aux != NULL) {
            if (aux->Team.PuncteEchipa < min) {
                min = aux->Team.PuncteEchipa;
            }
            aux = aux->next;
        }
        DeleteTeam(head, min);
        NrEchipe--;
    }
    *Nr_Echipe = NrPosibil;
}
/*----------------------------TASK2 SFARSIT----------------------------------*/

/*----------------------------TASK3 INCEPUT----------------------------------*/
CE * createQueue (){
    CE *q;
    q=allocate_memory(sizeof(CE));
    q-> front =q-> rear = NULL ;
    return q;
}
void enqueue(CE *q, TD t1, TD t2) {
    ME *newNode = (ME *) malloc(sizeof(ME));
    newNode->Team1 = t1;
    newNode->Team2 = t2;
    newNode->next = NULL;
    if (q->front == NULL) {
        q->front = q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}
void dequeue(CE *q, TD *t1, TD *t2) {
    if (q->front == NULL) {
        return;
    }
    *t1 = q->front->Team1;
    *t2 = q->front->Team2;
    ME *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}
void addTeamsToQueue(TL* teamsList, CE* matchesQueue) {
    TL* currentTeam = teamsList;
    while (currentTeam != NULL && currentTeam->next != NULL) {
        enqueue(matchesQueue, currentTeam->Team, currentTeam->next->Team);
        currentTeam = currentTeam->next->next;
    }
}
void afiseazaMeciuri(CE *coada,FILE* fisier) {
    if (coada == NULL || coada->front == NULL) {
        fprintf(fisier,"Nu exista meciuri de afisat.\n");
        return;
    }
    fprintf(fisier,"\n");
    ME *current = coada->front;
    while (current != NULL) {
        fprintf(fisier,"%-32s - %32s\n", current->Team1.Team_Name, current->Team2.Team_Name);
        current = current->next;
    }
}
void pushStiva(SE** top, TD team)
{
    SE* newTeam = (SE*) malloc(sizeof(SE));
    newTeam->Team = team;
    newTeam->next = *top;
    *top = newTeam;
}
TD popStiva(SE** top)
{
    TD echipaEliminata;
    SE* aux;
    if (*top == NULL) {
        printf("Stiva este goala.\n");
        return;
    }
    echipaEliminata = (*top)->Team;
    aux = *top;
    *top = (*top)->next;
    free(aux);
    return echipaEliminata;
}
void printStiva(SE* top,FILE *fisier)
{
    fprintf(fisier,"\n");
    while (top != NULL)
    {
        fprintf(fisier,"%-32s  -  %.2f\n", top->Team.Team_Name,top->Team.PuncteEchipa);
        top = top->next;
    }
}
void deleteQueue(CE* q) {
    ME* temp;
    while (q->front != NULL) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    free(q);
}
void clearStack(SE** top) {
    while (*top != NULL) {
        popStiva(top);
    }
}
void deleteStack(SE* top) {
    SE* temp;
    while (top != NULL) {
        temp = top;
        top = top->next;
        free(temp);
    }
}
void addTeamsFromStackToQueue(SE** top, CE* matchesQueue) {
    TD team1, team2;
    while(*top != NULL){
        team1 = popStiva(&*top);
        team2 = popStiva(&*top);
        enqueue(matchesQueue,team1,team2);
    }

}
void processMatches(CE* matchesQueue, SE** winnersStack, SE** losersStack) {
    TD team1, team2;
    while (matchesQueue->front != NULL) {
        dequeue(matchesQueue, &team1, &team2);
        if (team1.PuncteEchipa > team2.PuncteEchipa) {
            team1.PuncteEchipa++;
            pushStiva(&*winnersStack, team1);
            pushStiva(&*losersStack, team2);
        } else {
            team2.PuncteEchipa++;
            pushStiva(&*winnersStack, team2);
            pushStiva(&*losersStack, team1);
        }
    }
}

void AfisareTask3(TL* head, int Nr_Echipe, FILE* fisier){
    int NrEchipe = Nr_Echipe;
    int round = 1;
    CE* coada = createQueue();
    addTeamsToQueue(head,coada);
    fprintf(fisier,"\n--- ROUND NO:%d",round);
    afiseazaMeciuri(coada,fisier);
    SE* castigatori = NULL;
    SE* pierzatori = NULL;
    TD echipa1, echipa2;
    processMatches(coada,&castigatori,&pierzatori);
    fprintf(fisier,"\nWINNERS OF ROUND NO:%d",round);
    printStiva(castigatori,fisier);
    NrEchipe /=2;
    deleteStack(pierzatori);
    while(NrEchipe>1){
        round++;
        addTeamsFromStackToQueue(&castigatori,coada);
        fprintf(fisier,"\n--- ROUND NO:%d",round);
        afiseazaMeciuri(coada,fisier);
        processMatches(coada,&castigatori,&pierzatori);
        fprintf(fisier,"\nWINNERS OF ROUND NO:%d",round);
        printStiva(castigatori,fisier);
        NrEchipe /= 2;
    }
}
/*----------------------------TASK3 SFARSIT----------------------------------*/
