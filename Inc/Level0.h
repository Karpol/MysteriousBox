typedef struct
{
	ADC_HandleTypeDef* ldr;
	uint32_t illuminationLevel;
    uint32_t lastPhotoResistorCheckTime;
} Level0;

Level0* Level0_Construct(ADC_HandleTypeDef* ldr);
void Level0_Destroy(Level0 *level0);
void Level0_Run(Level0* level0);
