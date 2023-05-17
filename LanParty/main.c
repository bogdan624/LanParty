#include "tasks.h"

int main()
{
    FILE *fisier_taskuri, *check;
    int *task;
    TL *head = NULL;
    TL *OptEchipe = NULL;
    int Nr_Echipe = 0;
    fisier_taskuri=fopen("c.in","rt");
    check = fopen("test.txt","wt");
    task=allocate_memory(5*sizeof(int));
    check_null(fisier_taskuri);
    check_null(check);
    fscanf(fisier_taskuri,"%d %d %d %d %d",&task[0],&task[1],&task[2],&task[3],&task[4]);
    NAE * arbore = allocate_memory(sizeof(NAE));
    /*if(task[0]==1){
        ReadTeamList(&head,&Nr_Echipe);
        DisplayTeams(head,Nr_Echipe,check);
    }*/
    if(task[1]==1){
        ReadTeamList(&head,&Nr_Echipe);
        RemoveTeams(&head,&Nr_Echipe);
        DisplayTeams(head,Nr_Echipe,check);
    }
    if(task[2]==1){
        AfisareTask3(head,Nr_Echipe,check,&OptEchipe);
    }
    if(task[3]==1){
        arbore = AfisareTask4(OptEchipe,arbore,check);
    }
    if(task[4]==1){
        AVL * ceva = allocate_memory(sizeof(AVL));
        TL* lista_ajutor = NULL;
        transferDataNAEtoTL(arbore,&lista_ajutor);
        reverseTL(&lista_ajutor);
        AfisareTask5(lista_ajutor,ceva,check);
    }
    return 0;
}
