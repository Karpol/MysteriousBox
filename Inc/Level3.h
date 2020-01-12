typedef struct
{
    GPIO_PinState wireSwitchState;
    uint32_t lastWireSwitchCheckTime;
} Level3;

Level3* Level3_Construct();
void Level3_Destroy(Level3 *level3);
void Level3_Run(Level3* level3);
