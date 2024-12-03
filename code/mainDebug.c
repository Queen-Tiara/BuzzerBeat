#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Global Variables
int qNum = 0;

// File paths for questions and answers
#define questionFile "questions.txt"
#define answerFile "answers.txt"
#define bQuestionFile "bonus_questions.txt"
#define bAnswerFile "bonus_answers.txt"

// Structure Definitions
struct team {
    char name[100];
    char teamPlayers[4][100];
    char *captain;
    int score;
} teamOne, teamTwo;

struct answer {
    struct answer *next, *prev;
    char store[100];
};

struct bonusQuestion {
    struct answer one_Ans;
    struct answer two_Ans;
    struct answer three_Ans;
    struct answer one_Pr;
    struct answer two_Pr;
    struct answer three_Pr;
    char one[2000], two[2000], three[2000];
};

struct question {
    struct answer ans;
    struct answer pr;
    char store[2000];
    int questNum;
    struct bonusQuestion b;
    struct question *next, *prev;
};

// Function Declarations
void clearList(struct question *head);
void newQuestion(struct question **head, FILE *qfile, FILE *bfile, FILE *afile, FILE *bafile);
void setQuestion(FILE *file, struct question *temp);
bool checkAnswer(char pA[], struct question *head, struct team *team, bool p);
void bonusTime(struct question *head, struct team *team);
void setAnswers(FILE *file, struct question *temp);
void setBonus(FILE *file, FILE *afile, struct question *temp);
void displayQuestion(char *question);

// Main Function
int main() {
    // Initial Setup
    bool ready = false;
    char captain[100];
    printf("\nGames will consist of tossup questions worth 10 or 15 points, and 3 bonus questions worth 30 points. \nTeams will compete by answering questions on a variety of academic subjects.\n");

    printf("\nPlease enter two team names\nLet's start with Team One:\n");
    scanf("%s", &(teamOne.name));
    printf("\nPlease enter Team Two's name:\n");
    scanf("%s", &(teamTwo.name));
    printf("\nPlease enter up to four names per team (if less than 4 just press enter on excess entries)\n Let's start with team %s: \n", teamOne.name);
    for (int i = 0; i < 4; i++) {
        scanf("%s", teamOne.teamPlayers[i]);
    }
    printf("\nNext, team %s: \n", teamTwo.name);
    for (int i = 0; i < 4; i++) {
        scanf("%s", teamTwo.teamPlayers[i]);
    }
    printf("\nWho is the captain for %s?: ", teamOne.name);
    scanf("%s", captain);
    for (int i = 0; i < 4; i++) {
        if (strcmp(teamOne.teamPlayers[i], captain) == 0) {
            teamOne.captain = teamOne.teamPlayers[i];
        }
    }
    captain[0] = '\0';
    printf("\nWho is the captain for %s?: ", teamTwo.name);
    scanf("%s", captain);
    for (int i = 0; i < 4; i++) {
        if (strcmp(teamTwo.teamPlayers[i], captain) == 0) {
            teamTwo.captain = teamTwo.teamPlayers[i];
        }
    }

    // Load Questions and Answers from Files
    FILE *qfile = fopen(questionFile, "r");
    FILE *bfile = fopen(bQuestionFile, "r");
    FILE *afile = fopen(answerFile, "r");
    FILE *bafile = fopen(bAnswerFile, "r");

    struct question *head = NULL;
    if (qfile == NULL || bfile == NULL || afile == NULL || bafile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        qNum++;
        newQuestion(&head, qfile, bfile, afile, bafile);
    }

    // Game Loop
    qNum = 0;
    struct question *temp = NULL;
    struct team *t = NULL;
    bool power = true;
    int c;
    char pAnswer[100];
    while (qNum < 20) {
        qNum++;
        temp = head;
        // Traverse to the current question
        for (int i = 0; i < qNum; i++) {
            temp = temp->next;
        }
        if (qNum % 2 == 1) {
            printf("For team %s: \n", teamOne.name);
            t = &teamOne;
        }
        else {
            printf("For team %s: \n", teamTwo.name);
            t = &teamTwo;
        }
        c = 0;
        power = true;

        // Display the question one character at a time
        displayQuestion(temp->store);

        // Get and check the player's answer
        while (1) {
            if (kbhit() && getch() == ' ') {
                fgets(pAnswer, 100, stdin);
                if (checkAnswer(pAnswer, temp, t, power)) {
                    printf("\nCorrect\n");
                    break;
                }
                else {
                    printf("\nIncorrect\n");
                    t->score -= 5;
                }
            }
        }
        if (kbhit() && getch() == ' ') {
            fgets(pAnswer, 100, stdin);
            if (checkAnswer(pAnswer, temp, t, power)) {
                printf("\nCorrect\n");
                bonusTime(temp, t);
            }
            else {
                printf("\nIncorrect\n");
            }
        }
    }

    printf("\nGAME END\n");
    printf("--------\n");
    if (teamOne.score > teamTwo.score) {
        printf("Congratulations %s, you have won!", teamOne.name);
    }
    else if (teamTwo.score > teamOne.score) {
        printf("Congratulations %s, you have won!", teamTwo.name);
    }
    else {
        printf("Congratulations both teams, you are tied!");
    }

    clearList(head);
    fclose(qfile);
    fclose(bafile);
    fclose(bfile);
    fclose(afile);

    return 0;
}

// Function to display the question one character at a time
void displayQuestion(char *question) {
    int c = 0;
    while (question[c] != '\0') {
        putchar(question[c]);
        c++;
        fflush(stdout);
        usleep(100000);  // Sleep for 100ms to simulate typing effect
    }
    printf("\n");
}

// Function to parse and create new question node
void newQuestion(struct question **head, FILE *qfile, FILE *bfile, FILE *afile, FILE *bafile) {
    struct question *temp = *head;
    struct question *newNode = malloc(sizeof(struct question));

    if (temp == NULL) {
        *head = newNode;
        newNode->prev = NULL;
        setQuestion(qfile, newNode);
        setAnswers(afile, newNode);
        setBonus(bfile, bafile, newNode);
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
    setQuestion(qfile, newNode);
    setAnswers(afile, newNode);
    setBonus(bfile, bafile, newNode);
    return;
}

// Function to set the question from the file
void setQuestion(FILE *file, struct question *temp) {
    int targetLine = 2 * qNum; 
    int currentLine = 1;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            currentLine++;     
        }
        if (currentLine == targetLine) {
            int x = 0;
            while ((c = fgetc(file)) != '\n' && c != EOF) {
                temp->store[x] = c;
                x++;
            }
            temp->store[x] = '\0';
        }
    }
}

// Function to set the answer from the answer file
void setAnswers(FILE *file, struct question *temp) {
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            temp->ans.store[i] = '\0'; // Null-terminate the answer string
            break;
        }
        temp->ans.store[i] = c;
        i++;
    }
}

// Function to set bonus questions and answers
void setBonus(FILE *file, FILE *afile, struct question *temp) {
    char c;
    int
