%{
#include "game.h"
#include<string.h>
#include "scanner.h"

typedef enum{
    UP_KEY,
    DOWN_KEY,
    LEFT_KEY,
    RIGHT_KEY,
    PAUSE_KEY
} KEYS;

int player = 0;
int key = 0;
int x = 0;
%}

%x LIVES PLAYER PAUSE GAMEDURATION PROJETIL KEYS

%%
numberOfLives= { BEGIN(LIVES);}
gameDuration= {BEGIN(GAMEDURATION);}
pauseKey= { key = PAUSE_KEY; BEGIN(PLAYER);}
player1 {player = 0; BEGIN(KEYS); }
player2 {player = 1; BEGIN(KEYS);}
<LIVES>[0-9]+ { config.numberOfLives = atoi(yytext); BEGIN(INITIAL);}
<KEYS>upKey= { key = UP_KEY; BEGIN(PLAYER);}
<KEYS>leftKey= { key = LEFT_KEY; BEGIN(PLAYER);}
<KEYS>rightKey= { key = RIGHT_KEY; BEGIN(PLAYER);}
<KEYS>downKey= { key = DOWN_KEY; BEGIN(PLAYER);}
<GAMEDURATION>[0-9]+?[.]?[0-9]+ { config.gameDuration = atof(yytext); BEGIN(INITIAL);}
<PLAYER>[0-9]+  { 
                    x = atoi(yytext);
                    switch(key){
                        case UP_KEY:
                        if(player) config.player2.up = x;
                        else config.player1.up = x;
                        break;
                        case DOWN_KEY:
                        if(player) config.player2.down = x;
                        else config.player1.down = x;
                        break;
                        case LEFT_KEY:
                        if(player) config.player2.left = x;
                        else config.player1.left = x;
                        break;
                        case RIGHT_KEY:
                        if(player) config.player2.right = x;
                        else config.player1.right = x;
                        break;
                        case PAUSE_KEY:
                        config.pauseKey = x;
                        break;
                        default:
                        break;
                    }
                    BEGIN(INITIAL);
                }
<*>. ;
<*>\n ;
%%

void loadSettings(){
    yyin = fopen("assets/settings/settings.txt", "r");
    yylex();
    fclose(yyin);
    yyin = NULL;
}

void saveSettings(){
    FILE * arquivo;
    arquivo = fopen("assets/settings/settings.txt", "w");
    fprintf(arquivo, "numberOfLives=%d\n", config.numberOfLives);
    fprintf(arquivo, "gameDuration=%f\n", config.gameDuration);    
    fprintf(arquivo, "pauseKey=%d\n", config.pauseKey);
    fprintf(arquivo, "player1 upKey=%d\n", config.player1.up);
    fprintf(arquivo, "player1 downKey=%d\n", config.player1.down);
    fprintf(arquivo, "player1 leftKey=%d\n", config.player1.left);
    fprintf(arquivo, "player1 rightKey=%d\n", config.player1.right);
    fprintf(arquivo, "player2 upKey=%d\n", config.player2.up);
    fprintf(arquivo, "player2 downKey=%d\n", config.player2.down);
    fprintf(arquivo, "player2 leftKey=%d\n", config.player2.left);
    fprintf(arquivo, "player2 rightKey=%d\n", config.player2.right);
    fclose(arquivo);
}