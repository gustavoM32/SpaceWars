#include <stdlib.h>
#include "sounds.h"
#include "game.h"
int hasSoundPlayer = 0;
int musicPlayingTime = 0;

void checkForSoundPlayer(){
    hasSoundPlayer = !system("aplay --version &");
    config.isSoundActive = 1;
}

void playSound(int sound){
    if(hasSoundPlayer && config.isSoundActive)
    {
        switch (sound)
        {
        case LASER_SOUND:
            system("aplay assets/sounds/shot.wav & exit");        
            break;
        case EXPLOSION_SOUND:
            system("aplay assets/sounds/shipexplosion.wav & exit");        
            break;
        case MENUSELECT_SOUND:
            system("aplay assets/sounds/menuselect.wav & exit");        
            break;
        case MENUCHANGE_SOUND:
            system("aplay assets/sounds/menuchange.wav & exit");        
            break;    
        default:
            break;
        }
    }
}

void playMusic(int play){
    musicPlayingTime = 0;

    if(play) system("aplay assets/sounds/music.wav & exit");    
    else system("pkill aplay");
}