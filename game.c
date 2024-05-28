#include "game.h"
#include "combat.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initializeGame(Character *player, Scenario scenarios[]) {
    // Initialize player character
    printf("Enter your character's name: ");
    scanf("%s", player->name);
    player->hp = 100;
    player->atk = 20;
    player->def = 10;

    // Define skills (interview answers)
    strcpy(player->skills[0].name, "Perfectionist");
    strcpy(player->skills[0].description, "I am too much of a perfectionist");
    player->skills[0].type = 1;
    player->skills[0].atkModifier = -10;

    strcpy(player->skills[1].name, "Hard Worker");
    strcpy(player->skills[1].description, "I work too hard");
    player->skills[1].type = 1;
    player->skills[1].atkModifier = 5;

    // Initialize scenarios (job interviews)
    char* interviewerNames[] = {"Mr. Smith", "Ms. Johnson", "Dr. Brown", "Prof. Davis"};
    char* questionTexts[] = {
        "What is your greatest weakness?",
        "Where do you see yourself in 5 years?",
        "Why do you want to work here?",
        "How do you handle stress?",
        "Tell me about a time you failed."
    };
    char* options[][MAX_OPTIONS] = {
        {"I am too much of a perfectionist", "I work too hard", "I can be disorganized at times", "I have trouble delegating tasks"},
        {"In your position", "Running my own company", "Still learning and growing", "In a different field"},
        {"For the money", "Because I love this industry", "For the experience", "I need a job"},
        {"I don't get stressed", "I exercise regularly", "I meditate", "I ignore it"},
        {"I don't fail", "I learned from my mistakes", "I don't remember any failures", "I try to avoid failure"}
    };
    int impacts[][MAX_OPTIONS] = {
        {-10, -10, 10, 5},
        {-5, -5, 10, -5},
        {-10, 10, 5, -10},
        {-10, 10, 10, -10},
        {-10, 10, -5, -5}
    };

    for (int i = 0; i < 4; i++) {
        snprintf(scenarios[i].name, MAX_NAME_LENGTH, "Interview %d", i+1);
        snprintf(scenarios[i].description, 200, "You are at job interview %d", i+1);
        snprintf(scenarios[i].interviewer.name, MAX_NAME_LENGTH, "%s", interviewerNames[i]);
        scenarios[i].interviewer.hp = 30;
        scenarios[i].interviewer.atk = 10;
        scenarios[i].interviewer.def = 5;
        scenarios[i].questionCount = MAX_QUESTIONS;

        for (int j = 0; j < MAX_QUESTIONS; j++) {
            snprintf(scenarios[i].questions[j].text, 200, "%s", questionTexts[j]);
            for (int k = 0; k < MAX_OPTIONS; k++) {
                snprintf(scenarios[i].questions[j].options[k], 200, "%s", options[j][k]);
                scenarios[i].questions[j].impacts[k] = impacts[j][k];
            }
        }
    }
}

int playScenario(Character *player, Scenario *scenario, int scenarioIndex) {
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
            player->hp += scenario->questions[i].impacts[choice];
            printf("Your HP: %d\n", player->hp);
        } else {
            printf("Invalid choice.\n");
        }

        if (player->hp <= 0) {
            printf("You failed the interview.\n");
            return -1; // End the game if the player's HP is 0 or less
        }
    }

    printf("You passed the interview!\n");
    if (scenarioIndex + 1 < 4) {
        printf("Proceeding to next interview...\n");
    }
    return scenarioIndex + 1; // Proceed to the next scenario
}
