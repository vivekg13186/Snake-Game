#include <raylib.h>
#include <stdlib.h>
#include "clist.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <raymath.h>
#include "asset.h"
#include "image_data.h"
#include "eat_sound_data.h"
#include "fail_sound_data.h"
 

#define TILE_APPLE 0
#define TILE_BANNER 1
#define TILE_CHECKER 2
#define TILE_CLOCK 3
#define TILE_GAME_OVER 4
#define TILE_HELP 5
#define TILE_KEY 6
#define TILE_SOUND_OFF 7
#define TILE_SOUND_ON 8
#define TILE_SNAKE_BODY_BOTTOM_LEFT 9
#define TILE_SNAKE_BODY_BOTTOM_RIGHT 10
#define TILE_SNAKE_BODY_HORZ 11

#define TILE_SNAKE_BODY_TOP_LEFT 12
#define TILE_SNAKE_BODY_TOP_RIGHT 13
#define TILE_SNAKE_BODY_VERT 14
#define TILE_SNAKE_HEAD_DOWN 15
#define TILE_SNAKE_HEAD_LEFT 16
#define TILE_SNAKE_HEAD_RIGHT 17
#define TILE_SNAKE_HEAD_UP 18
#define TILE_SNAKE_TAIL_DOWN 19
#define TILE_SNAKE_TAIL_LEFT 20
#define TILE_SNAKE_TAIL_RIGHT 21
#define TILE_SNAKE_TAIL_UP 22






#define TILE_CHAR_0 23
#define TILE_CHAR_1 24
#define TILE_CHAR_2 25
#define TILE_CHAR_3 26
#define TILE_CHAR_4 27
#define TILE_CHAR_5 28
#define TILE_CHAR_6 29
#define TILE_CHAR_7 30
#define TILE_CHAR_8 31
#define TILE_CHAR_9 32
#define TILE_CHAR_POINT 33


#define DASHBOARD_HEIGHT  50
#define CELL_SIZE 25
#define CELL_NUMBER 20
#define MAX_SPEED 0.1
#define INIT_SPEED 0.3
#define SCORE_TO_SPEED 5
#define length(s) s->count(s)
#define IS_UP(v) v.y == -1
#define IS_DOWN(v) v.y == 1
#define IS_LEFT(v) v.x == -1
#define IS_RIGHT(v) v.x == 1

#define START_SCREEN 0
#define PLAY_GAME 1
#define FAIL_SCREEN 2
#define PAUSE_GAME 3
#define HELP_SCREEN 4

#define GAME_MODE_MARATHON 1
#define GAME_MODE_SPRINT 2

//resources
Texture2D texture_pack;

Font font;
Sound pop;
Sound  fail;
 
 
typedef struct Snake
{
    CList *body;
    Vector2 direction;
    int length;
    bool addNewBlock;
} Snake;
 


typedef struct GameState
{
    int movement;
    float time;
    int score;
    Snake snake;
    Vector2 fruit;
    bool is_music_on;
    int mode;
    float speed;
    int run_mode;
}GameState;

GameState  state;
time_t start;

Rectangle button_marathon ={
    76,190,322,82
};
Rectangle button_sprint ={
    76,300,322,82
};

Rectangle button_help ={
    69,405,322,82
};

Rectangle button_home ={
    205,415,60,60
};

Rectangle button_home_game_over ={
    210,495,60,60
};

Rectangle cherry_score_box ={
    155,215,100,100
};

Rectangle time_score_box ={
    155,325,100,100
};

Rectangle key_score_box ={
    155,432,100,100
};

Vector2* create_vec2(int x, int y);
void logVector(Vector2 *, char *);




