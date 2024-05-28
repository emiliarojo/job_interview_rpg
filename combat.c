#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void combat(Character *player, Character *enemy) {
    while (player->hp > 0 && enemy->hp > 0) {
        printf("Your HP: %d, Interviewer's HP: %d\n", player->hp, enemy->hp);
        printf("Choose an answer:\n");
        for (int i = 0; i < MAX_SKILLS; i++) {
            if (strlen(player->skills[i].name) > 0) {
                printf("%d. %s\n", i + 1, player->skills[i].name);
            }
        }
        int choice;
        scanf("%d", &choice);
        choice--;

        if (player->skills[choice].type == 1) {
            enemy->hp -= (player->atk + player->skills[choice].atkModifier) - enemy->def;
        } else if (player->skills[choice].type == 0) {
            player->def += player->skills[choice].defModifier;
        }

        if (enemy->hp > 0) {
            player->hp -= enemy->atk - player->def;
        }
    }

    if (player->hp > 0) {
        printf("You passed the interview!\n");
    } else {
        printf("You failed the interview.\n");
    }
}
