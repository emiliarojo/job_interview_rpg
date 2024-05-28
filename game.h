#ifndef GAME_H
#define GAME_H

#define MAX_NAME_LENGTH 50
#define MAX_SKILLS 4
#define MAX_QUESTIONS 5
#define MAX_OPTIONS 4

typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[100];
    int type; // 0 for temporary, 1 for direct attack
    int duration; // in turns, for temporary
    int atkModifier;
    int defModifier;
} Skill;

typedef struct {
    char text[200];
    char options[MAX_OPTIONS][200];
    int impacts[MAX_OPTIONS]; // positive or negative impact on player's HP
} Question;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int hp;
    int atk;
    int def;
    Skill skills[MAX_SKILLS];
} Character;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[200];
    Question questions[MAX_QUESTIONS];
    int questionCount;
    Character interviewer;
} Scenario;

void initializeGame(Character *player, Scenario scenarios[]);
int playScenario(Character *player, Scenario *scenario, int scenarioIndex);

#endif
