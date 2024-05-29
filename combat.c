#include "combat.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void timeStrike(Character *player, Character *enemy, char *lastMove) {
    if (strcmp(lastMove, "Problem Solving") == 0) {
        enemy->hp -= player->atk * 2;
        printf("Time Strike! You used %s and caused massive damage!\n", lastMove);
    } else {
        enemy->hp -= player->atk;
        printf("You used %s.\n", lastMove);
    }

    if (enemy->hp < 0) {
        enemy->hp = 0;
    }

    printf("Enemy HP: %d\n", enemy->hp);
}
