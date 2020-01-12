#include <stdbool.h>
#include <stdlib.h>
#include "main.h"
#include "Level1.h"

Level1* Level1_Construct(ADC_HandleTypeDef* ldr)
{
    Level1* level1 = (Level1*) malloc(sizeof(Level1));
    level1->ldr = ldr;
    level1->illuminationLevel = 1000;
    level1->runTime = 0;
    level1->lastLedLaserToggleTime = 0;
    level1->lastPhotoResistorCheckTime = 0;
    return level1;
}

bool Level1_isIlluminated(uint32_t illuminationLevel)
{
    return illuminationLevel > 100;
}

uint32_t Level1_readIlluminationLevel(ADC_HandleTypeDef* ldr) {
    uint32_t result = 0;
    HAL_ADC_Start(ldr);
    HAL_ADC_PollForConversion(ldr, 10);
    result = HAL_ADC_GetValue(ldr);
    HAL_ADC_Stop(ldr);
    return result;
}

void Level1_Run(Level1 *level1)
{
    uint32_t currentTime = HAL_GetTick();
    level1->runTime = currentTime;

    while (Level1_isIlluminated(level1->illuminationLevel)) {
        currentTime = HAL_GetTick();

        if (currentTime - level1->lastLedLaserToggleTime > 100) {
            HAL_GPIO_TogglePin(LED_LASER_GPIO_Port, LED_LASER_Pin);
            level1->lastLedLaserToggleTime = currentTime;
        }

        if (currentTime - level1->lastPhotoResistorCheckTime > 1000) {
            level1->illuminationLevel = Level1_readIlluminationLevel(level1->ldr);
            level1->lastPhotoResistorCheckTime = currentTime;
        }

        if (currentTime - level1->runTime > 1000) {
            HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
        }
    }

    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_LASER_GPIO_Port, LED_LASER_Pin, GPIO_PIN_RESET);
}

void Level1_Destroy(Level1 *level1)
{
    if (level1) {
        free(level1);
    }
}
