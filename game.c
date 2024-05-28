#include "game.h"
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
    for (int i = 0; i < 4; i++) {
        snprintf(scenarios[i].name, MAX_NAME_LENGTH, "Interview %d", i+1);
        snprintf(scenarios[i].description, 200, "You are at job interview %d", i+1);
        scenarios[i].enemyCount = 1;
        snprintf(scenarios[i].enemies[0].name, MAX_NAME_LENGTH, "Interviewer %d", i+1);
        scenarios[i].enemies[0].hp = 30;
        scenarios[i].enemies[0].atk = 10;
        scenarios[i].enemies[0].def = 5;
    }
}

int playScenario(Character *player, Scenario *scenario) {
    printf("You are now in %s\n", scenario->name);
    printf("%s\n", scenario->description);

    for (int i = 0; i < scenario->enemyCount; i++) {
        printf("%s appears!\n", scenario->enemies[i].name);
        combat(player, &scenario->enemies[i]);
    }

    return 0; // Placeholder for scenario navigation
}
