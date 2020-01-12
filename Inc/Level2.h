typedef struct
{
    GPIO_PinState reedSwitchState;
    uint32_t lastReedSwitchCheckTime;
} Level2;

Level2* Level2_Construct();
void Level2_Destroy(Level2 *level2);
void Level2_Run(Level2* level2);
