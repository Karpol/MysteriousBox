#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "Level2.h"

Level2* Level2_Construct()
{
    Level2* level2 = (Level2*) malloc(sizeof(Level2));
    level2->reedSwitchState = GPIO_PIN_SET;
    level2->lastReedSwitchCheckTime = 0;
    return level2;
}

bool Level2_isCircuitOpen(GPIO_PinState reedSwitchState)
{
    return reedSwitchState == GPIO_PIN_SET;
}

GPIO_PinState Level2_readReedSwitchState() {
    return HAL_GPIO_ReadPin(REED_SWITCH_GPIO_Port, REED_SWITCH_Pin);
}

void Level2_Run(Level2 *level2)
{
    uint32_t currentTime;
    while (Level2_isCircuitOpen(level2->reedSwitchState)) {
        level2->reedSwitchState = Level2_readReedSwitchState();

        currentTime = HAL_GetTick();

        if (currentTime - level2->lastReedSwitchCheckTime > 1000) {
            level2->reedSwitchState = Level2_readReedSwitchState();
            level2->lastReedSwitchCheckTime = currentTime;
        }
    }
}

void Level2_Destroy(Level2 *level2)
{
    if (level2) {
        free(level2);
    }
}
