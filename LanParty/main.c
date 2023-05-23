#include "tasks.h"

int main(int argc,char **argv)
{
    FILE *fisierC,*fisierD,*fisierR;
    int *task;
    TL *head = NULL;
    TL *OptEchipe = NULL;
    int Nr_Echipe = 0;
    fisierC=fopen(argv[1],"r");
    fisierD=fopen(argv[2],"r");
    fisierR = fopen(argv[3],"w");
    task=allocate_memory(5*sizeof(int));
    check_null(fisierC);
    check_null(fisierD);
    check_null(fisierR);
    fscanf(fisierC,"%d %d %d %d %d",&task[0],&task[1],&task[2],&task[3],&task[4]);
    NAE * arbore = allocate_memory(sizeof(NAE));
    if(task[0]==1){
        ReadTeamList(&head,&Nr_Echipe,fisierD);
        DisplayTeams(head,Nr_Echipe,fisierR);
        fclose(fisierR);
    }
    if(task[1]==1){
        fisierR = fopen(argv[3],"wt");
        check_null(fisierR);
        RemoveTeams(&head,&Nr_Echipe);
        DisplayTeams(head,Nr_Echipe,fisierR);
    }
    if(task[2]==1){
        AfisareTask3(head,Nr_Echipe,fisierR,&OptEchipe);
    }
    if(task[3]==1){
        arbore = AfisareTask4(OptEchipe,arbore,fisierR);
    }
    if(task[4]==1){
        AVL * ceva = allocate_memory(sizeof(AVL));
        TL* lista_ajutor = NULL;
        transferDataNAEtoTL(arbore,&lista_ajutor);
        reverseTL(&lista_ajutor);
        AfisareTask5(lista_ajutor,ceva,fisierR);
    }
    return 0;
}
