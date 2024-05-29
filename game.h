#ifndef GAME_H
#define GAME_H

#define MAX_NAME_LENGTH 50
#define MAX_SKILLS 4
#define MAX_AVAILABLE_SKILLS 10
#define MAX_OPTIONS 4
#define MAX_QUESTIONS 5
#define MAX_SCENARIOS 6

typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[200];
    int type; // 0 for defensive, 1 for offensive
    int atkModifier;
    int defModifier;
} Skill;

typedef struct {
    char text[200];
    char options[MAX_OPTIONS][200];
    int hpImpacts[MAX_OPTIONS];
    int atkImpacts[MAX_OPTIONS];
    int defImpacts[MAX_OPTIONS];
} Question;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int hp;
    int atk;
    int def;
} Interviewer;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[200];
    Interviewer interviewer;
    Question questions[MAX_QUESTIONS];
    int questionCount;
} Scenario;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int hp;
    int atk;
    int def;
    Skill skills[MAX_SKILLS];
} Character;

void initializeGame(Character *player, Scenario scenarios[], Skill availableSkills[], int numSkills);
int playScenario(Character *player, Scenario *scenario, int scenarioIndex, int completedScenarios[]);

extern int adjacencyMatrix[MAX_SCENARIOS][MAX_SCENARIOS];
extern char *scenarioNames[MAX_SCENARIOS];

#endif
