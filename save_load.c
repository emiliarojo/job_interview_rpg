#include "save_load.h"
#include "game.h" // Include this header to recognize the Character type
#include <stdio.h>

void saveGameState(Character *player, int currentScenario) {
    FILE *file = fopen("savegame.txt", "w");
    if (file == NULL) {
        printf("Error saving game.\n");
        return;
    }
    fprintf(file, "%s %d %d %d %d\n", player->name, player->hp, player->atk, player->def, currentScenario);
    fclose(file);
}

void loadGameState(Character *player, int *currentScenario) {
    FILE *file = fopen("savegame.txt", "r");
    if (file == NULL) {
        printf("No saved game found.\n");
        return;
    }
    fscanf(file, "%s %d %d %d %d\n", player->name, &player->hp, &player->atk, &player->def, currentScenario);
    fclose(file);
}
