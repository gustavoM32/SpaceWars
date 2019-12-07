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


/*
    checkForSoundPlayer()

    Checa se o usuário tem o programa para tocar sons.
*/
void checkForSoundPlayer();

/*
    playSound()

    Toca o som especificado

    Parâmetros:
        sound - número identificador do som.
*/
void playSound(int sound);

/*
    playMusic()

    Se play = 1, toca o som se não tiver tocando.
    Se play = 0, para o som.

    Parâmetros:
        play - booleana se deve tocar ou parar.
*/
void playMusic(int play);
