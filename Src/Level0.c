#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "Level0.h"

Level0* Level0_Construct(ADC_HandleTypeDef* ldr)
{
    Level0* level0 = (Level0*) malloc(sizeof(Level0));
    level0->ldr = ldr;
    level0->illuminationLevel = 0;
    level0->lastPhotoResistorCheckTime = 0;
    return level0;
}

bool Level0_isIlluminated(uint32_t illuminationLevel)
{
    return illuminationLevel > 100;
}

uint32_t Level0_readIlluminationLevel(ADC_HandleTypeDef* ldr) {
    uint32_t result = 0;
    HAL_ADC_Start(ldr);
    HAL_ADC_PollForConversion(ldr, 10);
    result = HAL_ADC_GetValue(ldr);
    HAL_ADC_Stop(ldr);
    return result;
}

void Level0_Run(Level0 *level0)
{
    uint32_t currentTime;
    while (!Level0_isIlluminated(level0->illuminationLevel)) {
        currentTime = HAL_GetTick();
        if (currentTime - level0->lastPhotoResistorCheckTime > 1000) {
            level0->illuminationLevel = Level0_readIlluminationLevel(level0->ldr);
            level0->lastPhotoResistorCheckTime = currentTime;
        }
    }
}

void Level0_Destroy(Level0 *level0)
{
    if (level0) {
        free(level0);
    }
}
