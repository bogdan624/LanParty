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
        ReadTeamDetails(head, Nume_Echipa, Nr_Playeri, fisier);
    }
    fclose(fisier);
}

void DisplayTeams(TL *head, int Nr_Echipe,FILE *fisier) {
    for(int i = 0; i < Nr_Echipe; ++i) {
        fprintf(fisier,"%s", head->Team.Team_Name);
        head = head->next;
    }
}
