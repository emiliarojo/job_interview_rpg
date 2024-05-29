#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "game.h"

void saveGameState(Character *player, int currentScenario);
void loadGameState(Character *player, int *currentScenario);

#endif
