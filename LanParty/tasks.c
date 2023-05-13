#include "tasks.h"

void* allocate_memory(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("Error: Memory allocation failed!\n");
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
        if(Nume_Echipa[strlen(Nume_Echipa)-1]==' ')
            Nume_Echipa[strlen(Nume_Echipa)-1]='\0';
        ReadTeamDetails(head, Nume_Echipa, Nr_Playeri, fisier);
    }
    fclose(fisier);
}

void DisplayTeams(TL *head, int Nr_Echipe,FILE *fisier) {
    for(int i = 0; i < Nr_Echipe; ++i) {
        fprintf(fisier,"%s",head->Team.Team_Name);
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
