enum{
    LASER_SOUND,
    ACCELERATE_SOUND,
    EXPLOSION_SOUND,
    MENUSELECT_SOUND,
    MENUCHANGE_SOUND,
    COUNTDOWN_SOUND,
    VICTORY_SOUND
};

int musicDuration;

void playSound(int sound);

void checkForSoundPlayer();

void playMusic(int play);
