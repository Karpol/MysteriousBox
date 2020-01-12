typedef struct
{
	ADC_HandleTypeDef* ldr;
	uint32_t illuminationLevel;
    uint32_t runTime;
    uint32_t lastLedLaserToggleTime;
    uint32_t lastPhotoResistorCheckTime;
} Level1;

Level1* Level1_Construct(ADC_HandleTypeDef* ldr);
void Level1_Destroy(Level1 *level1);
void Level1_Run(Level1* level1);
