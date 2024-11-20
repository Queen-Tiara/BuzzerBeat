#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Global Variables
int qNum = 0;

//input files with questions and answers
#define questionFile "questions.txt"
#define answerFile "answers.txt"
#define bQuestionFile "bonus_questions.txt"
#define bAnswerFile "bonus_answers.txt"

struct team{
    char name[100];
    char teamPlayers[4][100];
    char *captain;
    int score;
}teamOne, teamTwo;

struct question{
    struct answer ans;
    struct answer pr;
    char store[2000];
    int questNum;
    struct bonusQuestion b;
    struct question *next, *prev;

};

struct bonusQuestion{
    struct answer one_Ans;
    struct answer two_Ans;
    struct answer three_Ans;
    struct answer one_Pr;
    struct answer two_Pr;
    struct answer three_Pr;
    char one[2000], two[2000], three[2000];
};

struct answer{
    struct answer *next, *prev;
    char store[100];
};

//Functions
void clearList(struct question *head);
void newQuestion(struct question *head, FILE *file,  FILE *bfile, FILE *afile, FILE *bafile);
void setQuestion(FILE *file, struct question *temp);

int main() {
    //I need to introduce the rules and set up here
    /*Things needed in setup:
    explain rules
    determine two teams
    determine names
    determine captain
    all players online press ready*/
    bool ready = false;
    char captain[100];
    printf("\nGames will consist of tossup questions worth 10 or 15 points, and 3 bonus questions worth 30 points. \nTeams will compete by answering questions on a variety of academic subjects. \nFor more specificity on quiz bowl rules visit https://www.naqt.com/rules/");
    printf("\nPlease enter two team names\nLet's start with Team One:\n");
    scanf("%s", &(teamOne.name));
    printf("\nPlease enter Team Two's name:\n");
    scanf("%s", &(teamTwo.name));
    printf("\nPlease enter up to four names per team (if less than 4 just press enter on excess entries)\n Let's start with team %s: \n", teamOne.name);
    for(int i = 0; i < 4; i++){
        scanf("%s", teamOne.teamPlayers[i]);
    }
    printf("\nNext, team %s: \n", teamTwo.name);
    for(int i = 0; i < 4; i++){
        scanf("%s", teamTwo.teamPlayers[i]);
    }
    printf("\nWho is the captain for %s?: ", teamOne.name);
    scanf("%s", captain);
    for(int i = 0; i < 4; i++){
        if(teamOne.teamPlayers[i] == captain){
            teamOne.captain = teamOne.teamPlayers[i];
        }
    }
    captain[0] = '\0';
    printf("\nWho is the captain for %s?: ", teamTwo.name);
    scanf("%s", captain);
    for(int i = 0; i < 4; i++){
        if(teamTwo.teamPlayers[i] == captain){
            teamTwo.captain = teamTwo.teamPlayers[i];
        }
    }
    free(captain);
    while(!ready){
        //add code for both captains to answer
        break;
    }

    /*Start of extraction of questions and answers*/

    FILE *qfile = fopen(questionFile, "r");
    FILE *bfile = fopen(bQuestionFile, "r");
    FILE *afile = fopen(answerFile, "r");
    FILE *bafile = fopen(bAnswerFile, "r");
    struct question *head;
    if (qfile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    for(int i = 0; i < 20; i++){
        qNum++;
        newQuestion(head, qfile, bfile, afile, bafile);

    }

    /*Onto gameplay
    Need timer
    need to grade answers
    */
    bool gameOn = true;
    while(gameOn){

    }
    

    fclose(qfile);
    fclose(bafile);
    fclose(bfile);
    fclose(afile);

    return 0;
}

void newQuestion(struct question *head, FILE *qfile, FILE *bfile, FILE *afile, FILE *bafile){

    struct question *temp = head;
    struct question *t = NULL;
    struct question *newNode = malloc(sizeof(struct question));
    if (temp == NULL) {
         head = newNode;
         newNode->prev = NULL;
         setQuestion(qfile, head);
         setAnswers(afile, head);
         setBonus(bfile, bafile, head);
         return;
        }
    while(temp->next != NULL){
        t = temp;
        temp = temp->next;
        temp->prev = t;
    }
    temp->next = newNode;
    head->prev = newNode;
    setQuestion(qfile, temp->next);
    setAnswers(afile, temp->next);
    setBonus(bfile, bafile, temp->next);
    temp->next->questNum = qNum;
    temp->next->next = head;
    return;
}

void setQuestion( FILE *file, struct question *temp){
    int targetLine = 2*qNum; 
    int currentLine = 1;
    char c;
    while((c = fgetc(file)) != EOF){
        if (c == '\n') {
            currentLine++;     
        }
        if (currentLine == targetLine) {
            int x = 0;
            while((c = fgetc(file)) != '\n'){
                temp->store[x] = c;
                x++;
            }
            temp->store[x] = '\0';
        }
    }
}

void setAnswers(FILE *file, struct question *temp){
    int targetLine = qNum*2;
    int currentLine = 1;
    char c;
    
    struct answer *a = &(temp->ans); 
    a = malloc(sizeof(struct answer));
    struct answer *tempA = NULL;
    a->prev = NULL;
    struct answer *p = &(temp->pr); 
    p = malloc(sizeof(struct answer));
    struct answer *tempP = NULL;
    p->prev = NULL;
    while((c = fgetc(file)) != EOF){
        if (c == '\n') {
            currentLine++;     
        }
        if (currentLine == targetLine) {
            int x = 0;
            int y = 0;
            while((c = fgetc(file)) != ':' || (c = fgetc(file)) != '\n'){
                if(c == '|'){ 
                    tempA = a;
                    a = a->next;
                    a->prev = tempA;
                    a = malloc(sizeof(struct answer));
                    temp->ans.prev = a;
                    a->next = temp->ans.prev;
                    continue;
                } 
                
                a->store[x] = c;
                x++;
                
            }
            a->store[x] = '\0';
            if(c == ':'){
                c = fgetc(file);
            }
            while((c = fgetc(file)) != '\n'){
                if(c == ':'){ 
                    tempP = p;
                    p = p->next;
                    p->prev = tempP;
                    p = malloc(sizeof(struct answer));
                    temp->pr.prev = p;
                    p->next = temp->pr.prev;
                    continue;
                }
                p->store[y] = c;
                y++;
            }
            p->store[y] = '\0';
            
        }
    }
    return;
}

void setBonus(FILE *file, FILE *afile, struct question *temp){
    int targetLine = qNum*2;
    int currentLine = 1;
    char c;
    while((c = fgetc(file)) != EOF){
        if (c == '\n') {
            currentLine++;     
        }
        if (currentLine == targetLine) {
            int x = 0;
            while((c = fgetc(file)) != '\n'){
                temp->b.one[x] = c;
                x++;
            }
            temp->b.one[x] = '\0';
        }
        if (currentLine == (targetLine + 1)) {
            int x = 0;
            while((c = fgetc(file)) != '\n'){
                temp->b.two[x] = c;
                x++;
            }
            temp->b.two[x] = '\0';
        }
        if (currentLine == (targetLine + 2)) {
            int x = 0;
            while((c = fgetc(file)) != '\n'){
                temp->b.three[x] = c;
                x++;
            }
            temp->b.three[x] = '\0';
        }
    }
    struct answer *a1 = &(temp->b.one_Ans);
    struct answer *a2 = &(temp->b.two_Ans);
    struct answer *a3 = &(temp->b.three_Ans);
    a1 = malloc(sizeof(struct answer));
    a2 = malloc(sizeof(struct answer));
    a3 = malloc(sizeof(struct answer));
    struct answer *tempA = NULL;
    a1->prev = NULL;
    a2->prev = NULL;
    a3->prev = NULL;
    struct answer *p1 = &(temp->pr); 
    struct answer *p2 = &(temp->pr); 
    struct answer *p3 = &(temp->pr); 
    p1 = malloc(sizeof(struct answer));
    p2 = malloc(sizeof(struct answer));
    p3 = malloc(sizeof(struct answer));
    struct answer *tempP = NULL;
    p1->prev = NULL;
    p2->prev = NULL;
    p3->prev = NULL;
    while((c = fgetc(afile)) != EOF){
        if (c == '\n') {
            currentLine++;     
        }
        if (currentLine == targetLine) {
            int x = 0;
            while((c = fgetc(afile)) != ':' || (c = fgetc(afile)) != '\n'){
                if(c == '|'){ 
                    tempA = a1;
                    a1 = a1->next;
                    a1->prev = tempA;
                    a1 = malloc(sizeof(struct answer));
                    temp->b.one_Ans.prev = a1;
                    continue;
                }
                a1->store[x] = c;
                x++;
            }
            a1->store[x] = '\0';
            int y = 0;
            if(c == ':'){
                c = fgetc(afile);
            }
            while((c = fgetc(afile)) != '\n'){
                if(c == ':'){ 
                    tempP = p1;
                    p1 = p1->next;
                    p1->prev = tempP;
                    p1 = malloc(sizeof(struct answer));
                    temp->pr.prev = p1;
                    p1->next = temp->pr.prev;
                    continue;
                }
                p1->store[y] = c;
                y++;
            }
            p1->store[y] = '\0';
        }
        if (currentLine == (targetLine + 1)) {
            int x = 0;
            while((c = fgetc(afile)) != ':' || (c = fgetc(afile)) != '\n'){
                if(c == '|'){ 
                    tempA = a2;
                    a2 = a2->next;
                    a2->prev = tempA;
                    a2 = malloc(sizeof(struct answer));
                    temp->b.two_Ans.prev = a2;
                    continue;
                }
                a2->store[x] = c;
                x++;
            }
            a2->store[x] = '\0';
            if(c == ':'){
                c = fgetc(afile);
            }
            int y = 0;
            while((c = fgetc(afile)) != '\n'){
                if(c == ':'){ 
                    tempP = p2;
                    p2 = p2->next;
                    p2->prev = tempP;
                    p2 = malloc(sizeof(struct answer));
                    temp->pr.prev = p2;
                    p2->next = temp->pr.prev;
                    continue;
                }
                p2->store[y] = c;
                y++;
            }
            p2->store[y] = '\0';
        }
        if (currentLine == (targetLine + 2)) {
            int x = 0;
            while((c = fgetc(afile)) != ':' || (c = fgetc(afile)) != '\n'){
                if(c == '|'){ 
                    tempA = a3;
                    a3 = a3->next;
                    a3->prev = tempA;
                    a3 = malloc(sizeof(struct answer));
                    temp->b.three_Ans.prev = a3;
                    continue;
                }
                a3->store[x] = c;
                x++;
            }
            a3->store[x] = '\0';
            if(c == ':'){
                c = fgetc(afile);
            }
            int y = 0;
            while((c = fgetc(afile)) != '\n'){
                if(c == ':'){ 
                    tempP = p3;
                    p3 = p3->next;
                    p3->prev = tempP;
                    p3 = malloc(sizeof(struct answer));
                    temp->pr.prev = p3;
                    p3->next = temp->pr.prev;
                    continue;
                }
                p3->store[y] = c;
                y++;
            }
            p3->store[y] = '\0';
        }
    }
    return;
}


void clearList(struct question *head) {
    struct question* current = head;
    struct question* next;

    while (current != NULL) {
        
        free(&(current->ans));
        free(&(current->pr));
        free(&(current->b.one_Ans));
        free(&(current->b.two_Ans));
        free(&(current->b.three_Ans));
        free(&(current->b.one_Pr));
        free(&(current->b.two_Pr));
        free(&(current->b.three_Pr));

        next = current->next;
        free(current);
        current = next;
    }

    head = NULL; 

}