#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "combat.h"

int main() {
    srand(time(NULL));

    Character player;
    Scenario scenarios[4];
    initializeGame(&player, scenarios);

    int currentScenario = 0;
    while (currentScenario < 4 && player.hp > 0) {
        currentScenario = playScenario(&player, &scenarios[currentScenario], currentScenario);
        if (currentScenario < 0) {
            printf("Game Over! You failed the job interviews.\n");
            return 0;
        }
    }

    if (player.hp > 0) {
        printf("Congratulations! You have completed the game.\n");
    }
    return 0;
}
