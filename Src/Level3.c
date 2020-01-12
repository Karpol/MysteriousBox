#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "Level3.h"

Level3* Level3_Construct()
{
    Level3* level3 = (Level3*) malloc(sizeof(Level3));
    level3->wireSwitchState = GPIO_PIN_SET;
    level3->lastWireSwitchCheckTime = 0;
    return level3;
}

bool Level3_isCircuitOpen(GPIO_PinState wireSwitchState)
{
    return wireSwitchState == GPIO_PIN_SET;
}

GPIO_PinState Level3_readWireSwitchState() {
    return HAL_GPIO_ReadPin(WIRE_SWITCH_GPIO_Port, WIRE_SWITCH_Pin);
}

void Level3_Run(Level3 *level3)
{
    uint32_t currentTime;
    while (Level3_isCircuitOpen(level3->wireSwitchState)) {
        level3->wireSwitchState = Level3_readWireSwitchState();

        currentTime = HAL_GetTick();

        if (currentTime - level3->lastWireSwitchCheckTime > 1000) {
            level3->wireSwitchState = Level3_readWireSwitchState();
            level3->lastWireSwitchCheckTime = currentTime;
        }
    }
}

void Level3_Destroy(Level3 *level3)
{
    if (level3) {
        free(level3);
    }
}
