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
    char store[2000];
    int questNum;
    struct bonusQuestion b;
    struct bonusQuestion *head;
    struct question *next, *prev;

};

struct bonusQuestion{
    struct answer bAns;
    char one[2000], two[2000], three[2000];
};

struct answer{
    struct answer *next, *prev;
    char store[100];
};

//Functions
void clearList(struct answer *head);
void newQuestion(struct question *head, FILE *file, int lineNum,  FILE *bfile, FILE *afile, FILE *bafile);
void findQuestNum(FILE *file);

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
    int lineNum = 1;
    int readLine = 0;
    if (qfile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    char c;
    while((c = fgetc(qfile)) != EOF){
        if (c == '(') {
            qNum = fgetc(qfile) - '0';
            
        }
        if (c == '\n') {
            lineNum++;
            newQuestion(head, qfile, lineNum, bfile, afile, bafile);
             
                   
        }

    }

    
    

    fclose(qfile);
    fclose(bafile);
    fclose(bfile);
    fclose(afile);

    return 0;
}

void newQuestion(struct question *head, FILE *qfile, int lineNum, FILE *bfile, FILE *afile, FILE *bafile){

    struct question *temp = head;
    struct question *newNode = malloc(sizeof(struct question));
    if (temp == NULL) {
         head = newNode;
         newNode->prev = NULL;
         return;
        }
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    readQuestion(lineNum, qfile, temp->next);
    temp->next->questNum = qNum;

    return;
}

void readQuestion(int lineNum, FILE *file, struct question *temp){
    int targetLine = lineNum; 
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

void findQuestNum(FILE *file){
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '(') {
            qNum = fgetc(file) - '0';
            return;
        }
    }
}

void clearList(struct answer *head) {
    struct answer* current = head;
    struct answer* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL; 

}