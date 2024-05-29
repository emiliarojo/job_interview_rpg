#include "game.h"
#include "combat.h"
#include "load_config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int adjacencyMatrix[MAX_SCENARIOS][MAX_SCENARIOS] = {
    {0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}
};

char *scenarioNames[MAX_SCENARIOS] = {
    "HR Screening",
    "Coding Assessment",
    "Behavioral Interview",
    "System Design Interview",
    "Second Behavioral Interview",
    "Final Interview with CEO"
};

void createCharacter(Character *player, Skill availableSkills[], int numSkills) {
    printf("Enter your character's name: ");
    scanf("%s", player->name);
    player->hp = 100;
    player->atk = 20;
    player->def = 10;

    printf("Choose 4 skills from the following list:\n");
    for (int i = 0; i < numSkills; i++) {
        printf("%d. %s - %s (Type: %s, ATK Modifier: %d, DEF Modifier: %d)\n", i + 1, availableSkills[i].name, availableSkills[i].description,
               availableSkills[i].type == 1 ? "Offensive" : "Defensive", availableSkills[i].atkModifier, availableSkills[i].defModifier);
    }

    int chosenSkills[MAX_SKILLS] = {0}; // To keep track of chosen skills

    for (int i = 0; i < MAX_SKILLS; i++) {
        int choice;
        int validChoice = 0;

        while (!validChoice) {
            printf("Choose skill %d: ", i + 1);
            scanf("%d", &choice);
            choice--; // To match array index

            if (choice >= 0 && choice < numSkills && !chosenSkills[choice]) {
                player->skills[i] = availableSkills[choice];
                chosenSkills[choice] = 1; // Mark skill as chosen
                validChoice = 1;
            } else {
                printf("Invalid choice or skill already chosen, try again.\n");
            }
        }
    }
}


void initializeGame(Character *player, Scenario scenarios[], Skill availableSkills[], int numSkills) {
    createCharacter(player, availableSkills, numSkills);
}

int playScenario(Character *player, Scenario *scenario, int scenarioIndex, int completedScenarios[]) {
    printf("You are now in %s\n", scenario->name);
    printf("%s\n", scenario->description);
    printf("Interviewer: %s\n", scenario->interviewer.name);

    for (int i = 0; i < scenario->questionCount; i++) {
        printf("%s\n", scenario->questions[i].text);
        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("%d. %s\n", j + 1, scenario->questions[i].options[j]);
        }

        int choice;
        scanf("%d", &choice);
        choice--; // to match the array index

        if (choice >= 0 && choice < MAX_OPTIONS) {
            player->hp += scenario->questions[i].hpImpacts[choice];
            player->atk += scenario->questions[i].atkImpacts[choice];
            player->def += scenario->questions[i].defImpacts[choice];

            // Prevent negative ATK
            if (player->atk < 0) {
                player->atk = 0;
            }

            printf("Your HP: %d, ATK: %d, DEF: %d\n", player->hp, player->atk, player->def);
        } else {
            printf("Invalid choice.\n");
            i--; // Retry the current question
        }

        if (player->hp <= 0) {
            printf("You failed the interview.\n");
            return -1; // End the game if the player's HP is 0 or less
        }
    }

    printf("You passed the interview!\n");

    // Mark the current scenario as completed
    completedScenarios[scenarioIndex] = 1;

    // Show available scenarios
    printf("Available scenarios to navigate to:\n");
    int availableScenarioCount = 0;
    for (int i = 0; i < MAX_SCENARIOS; i++) {
        if (!completedScenarios[i]) {
            printf("%d. %s\n", i, scenarioNames[i]);
            availableScenarioCount++;
        }
    }

    if (availableScenarioCount == 0) {
        return -1;
    }

    int nextScenario;
    while (1) {
        printf("Choose the next scenario to navigate to: ");
        scanf("%d", &nextScenario);
        if (nextScenario >= 0 && nextScenario < MAX_SCENARIOS && !completedScenarios[nextScenario]) {
            break; // valid choice
        } else {
            printf("Invalid scenario. Please choose again.\n");
        }
    }

    return nextScenario; // Proceed to the selected scenario
}
