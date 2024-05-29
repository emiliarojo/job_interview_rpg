#include "game.h"
#include "save_load.h"
#include "combat.h"
#include "load_config.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Character player;
    Scenario scenarios[MAX_SCENARIOS];
    Skill availableSkills[MAX_AVAILABLE_SKILLS];
    int numSkills = MAX_AVAILABLE_SKILLS;

    // Load game configuration from JSON file
    loadGameConfiguration(&player, scenarios, availableSkills, &numSkills);

    // Initialize the game with the player and scenarios
    initializeGame(&player, scenarios, availableSkills, numSkills);

    int completedScenarios[MAX_SCENARIOS] = {0}; // Initialize to 0
    int currentScenario = 0;

    while (currentScenario != -1) {
        currentScenario = playScenario(&player, &scenarios[currentScenario], currentScenario, completedScenarios);

        if (currentScenario == -1 && player.hp > 0) {
            printf("Congratulations! You're hired!\n");
        } else if (currentScenario == -1 && player.hp <= 0) {
            printf("Game over. You failed the interview process.\n");
        }
    }

    return 0;
}
