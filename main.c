#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

int main() {
    srand(time(NULL));

    Character player;
    Scenario scenarios[4];
    initializeGame(&player, scenarios);

    int currentScenario = 0;
    while (currentScenario != -1) {
        currentScenario = playScenario(&player, &scenarios[currentScenario]);
    }

    printf("Congratulations! You're hired!\n");
    return 0;
}
