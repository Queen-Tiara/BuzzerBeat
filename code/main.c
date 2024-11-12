#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
    int num;
};

struct bonusQuestion{
    
};

struct answer{

};

//Functions
clearList(Node** head);

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
    scanf("%s", &teamOne->name);
    printf("\nPlease enter Team Two's name:\n");
    scanf("%s", &teamTwo->name);
    printf("\nPlease enter up to four names per team (if less than 4 just press enter on excess entries)\n Let's start with team %s: \n", teamOne->name);
    for(int i = 0; i < 4; i++){
        scanf("%s", teamOne->teamPlayers[i]);
    }
    printf("\nNext, team %s: \n", teamTwo->name);
    for(int i = 0; i < 4; i++){
        scanf("%s", teamTwo->teamPlayers[i]);
    }
    printf("\nWho is the captain for %s?: ", teamOne->name);
    scanf("%s", captain);
    for(int i = 0; i < 4; i++){
        if(teamOne->teamPlayers[i] == captain){
            teamOne->captain = teamOne->teamPlayers[i];
        }
    }
    captain[0] = '\0';
    printf("\nWho is the captain for %s?: ", teamTwo->name);
    scanf("%s", captain);
    for(int i = 0; i < 4; i++){
        if(teamTwo->teamPlayers[i] == captain){
            teamTwo->captain = teamTwo->teamPlayers[i];
        }
    }
    free(captain);
    while(!ready){
        //add code for both captains to answer
        break;
    }

    /*Start of extraction of questions and answers*/

    FILE *file = fopen(questionFile, "r"); 
    struct question q;
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    
    if (fgets(q->store, 100, file) == '(' ) {
        
    }

    fclose(file); // Close the file

    return 0;
}

void clearList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;   

}