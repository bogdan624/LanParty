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
        Nume_Echipa[strlen(Nume_Echipa)-1] = '\0';
        if(Nume_Echipa[strlen(Nume_Echipa)-1] == ' ')
            Nume_Echipa[strlen(Nume_Echipa)-1] = '\0';
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
    while (NrPosibil <= Nr_Echipe) {
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
        exit(1);
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
            for(int i = 0; i <team1.Nr_Players;++i){
                team1.Players[i].points++;
            }
            team1.PuncteEchipa++;
            pushStiva(&*winnersStack, team1);
            pushStiva(&*losersStack, team2);
        } else {
            for(int i = 0; i <team2.Nr_Players;++i){
                team2.Players[i].points++;
            }
            team2.PuncteEchipa++;
            pushStiva(&*winnersStack, team2);
            pushStiva(&*losersStack, team1);
        }
    }
}
void addTeamsToTL(TL** head, SE* stiva) {
    while (stiva != NULL) {
        TL* new_node = (TL*)malloc(sizeof(TL));
        new_node->Team = stiva->Team;
        new_node->next = NULL;
        if (*head == NULL) {
            *head = new_node;
        }
        else {
            TL* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
        stiva = stiva->next;
    }
}

void AfisareTask3(TL* head, int Nr_Echipe, FILE* fisier, TL** echipe_ramase){
    int NrEchipe = Nr_Echipe;
    int round = 1;
    CE* coada = createQueue();
    addTeamsToQueue(head,coada);
    fprintf(fisier,"\n--- ROUND NO:%d",round);
    afiseazaMeciuri(coada,fisier);
    SE* castigatori = NULL;
    SE* pierzatori = NULL;
    processMatches(coada,&castigatori,&pierzatori);
    fprintf(fisier,"\nWINNERS OF ROUND NO:%d",round);
    printStiva(castigatori,fisier);
    NrEchipe /=2;
    deleteStack(pierzatori);
    while(NrEchipe>1){
        if(NrEchipe == 8){
            addTeamsToTL(echipe_ramase,castigatori);
        }
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

/*----------------------------TASK4 INCEPUT----------------------------------*/
NAE * newNode ( TD data ) {
    NAE * node = allocate_memory(sizeof(NAE));
    node->Team = data ;
    node->left=node->right=NULL ;
    return node ;
}
NAE * insertNAE ( NAE * node , TD key) {
    if ( node == NULL ) return newNode ( key );
    if ( key.PuncteEchipa < node->Team.PuncteEchipa)
    node-> left = insertNAE(node->left,key);
    else if (key.PuncteEchipa > node->Team.PuncteEchipa)
    node->right = insertNAE(node->right,key);
    else if(key.PuncteEchipa == node->Team.PuncteEchipa){
        if(strcmp(key.Team_Name,node->Team.Team_Name)>0){
            node->right = insertNAE(node->right,key);
        }
        else {
            node-> left = insertNAE(node->left,key);
        }
    }
    return node ;
}
void inorderRightToLeft(NAE* root,FILE *fisier) {
    if (root == NULL) {
        return;
    }
    inorderRightToLeft(root->right,fisier);
    fprintf(fisier,"%-32s  -  %.2f\n", root->Team.Team_Name,root->Team.PuncteEchipa);
    inorderRightToLeft(root->left,fisier);
}
NAE* AfisareTask4(TL*head,NAE* arbore,FILE* fisier){
    arbore = NULL;
    while(head->next != NULL){
        arbore=insertNAE(arbore,head->Team);
        head = head->next;
    }
    arbore=insertNAE(arbore,head->Team);
    fprintf(fisier,"\nTOP 8 TEAMS:\n");
    inorderRightToLeft(arbore,fisier);
    return arbore;
}
/*----------------------------TASK4 SFARSIT----------------------------------*/

/*----------------------------TASK5 INCEPUT----------------------------------*/
int max(int a, int b) {
    return ((a > b) ? a : b);
}

int nodeHeight(AVL* root) {
    if (root == NULL)
        return -1;
    else
        return root->height;
}

AVL* rightRotation(AVL* z) {
    AVL* y = z->left;
    AVL* T3 = y->right;
    y->right = z;
    z->left = T3;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

AVL* leftRotation(AVL* z) {
    AVL* y = z->right;
    AVL* T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

AVL* LRRotation(AVL* Z) {
    Z->left = leftRotation(Z->left);
    return rightRotation(Z);
}

AVL* RLRotation(AVL* Z) {
    Z->right = rightRotation(Z->right);
    return leftRotation(Z);
}
AVL* balanceAVL(AVL* node, TD key) {
    int balanceFactor = nodeHeight(node->left) - nodeHeight(node->right);
    if (balanceFactor > 1 && key.PuncteEchipa < node->left->Team.PuncteEchipa)
        return rightRotation(node);
    if (balanceFactor < -1 && key.PuncteEchipa > node->right->Team.PuncteEchipa)
        return leftRotation(node);
    if (balanceFactor > 1 && key.PuncteEchipa > node->left->Team.PuncteEchipa) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    if (balanceFactor < -1 && key.PuncteEchipa < node->right->Team.PuncteEchipa) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}
AVL* insertAVL(AVL* node, TD key) {
    if (node == NULL) {
        AVL* newNode = allocate_memory(sizeof(AVL));
        newNode->Team = key;
        newNode->height = 0;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key.PuncteEchipa < node->Team.PuncteEchipa)
        node->left = insertAVL(node->left, key);
    else if (key.PuncteEchipa > node->Team.PuncteEchipa)
        node->right = insertAVL(node->right, key);
    else {
        int verf = strcmp(key.Team_Name, node->Team.Team_Name);
        if (verf > 0)
            node->right = insertAVL(node->right, key);
        else
            node->left = insertAVL(node->left, key);
    }
    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
    node = balanceAVL(node, key);

    return node;
}
void insertTeam(TL** tl_head, TD team) {
    TL* new_team = allocate_memory(sizeof(TL));
    new_team->Team = team;
    new_team->next = NULL;

    if (*tl_head == NULL) {
        *tl_head = new_team;
        return;
    }

    TL* curr = *tl_head;
    TL* prev = NULL;
    while (curr != NULL && curr->Team.PuncteEchipa < team.PuncteEchipa) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) {
        new_team->next = *tl_head;
        *tl_head = new_team;
    } else {
        prev->next = new_team;
        new_team->next = curr;
    }
}
void transferDataNAEtoTL(NAE* nae, TL** tl_head) {
    if (nae == NULL) {
        return;
    }
    transferDataNAEtoTL(nae->right, tl_head);
    insertTeam(tl_head, nae->Team);
    transferDataNAEtoTL(nae->left, tl_head);
}
AVL* transferTLtoAVL(TL* list) {
    AVL* tree = NULL;
    TL* current = list;
    while (current != NULL) {
        tree = insertAVL(tree, current->Team);
        current = current->next;
    }
    return tree;
}

void PrintLevel2(AVL* root, FILE* output) {
    if (root == NULL) return;
    if (root->right != NULL) {
        if (root->right->right != NULL) {
            fprintf(output, "%-32s\n", root->right->right->Team.Team_Name);
        }
        if (root->right->left != NULL) {
            fprintf(output, "%-32s\n", root->right->left->Team.Team_Name);
        }
    }

    if (root->left != NULL) {
        if (root->left->right != NULL) {
            fprintf(output, "%-32s\n", root->left->right->Team.Team_Name);
        }
        if (root->left->left != NULL) {
            fprintf(output, "%-32s\n", root->left->left->Team.Team_Name);
        }
    }
}

void reverseTL(TL** head) {
    TL* prev = NULL;
    TL* current = *head;
    TL* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void AfisareTask5(TL* lista, AVL* echipe, FILE* fisier) {
    echipe = transferTLtoAVL(lista);
    fprintf(fisier, "\nTHE LEVEL 2 TEAMS ARE:\n");
    PrintLevel2(echipe, fisier);
}
/*----------------------------TASK5 SFARSIT----------------------------------*/
