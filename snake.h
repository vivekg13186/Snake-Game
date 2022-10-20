#include <raylib.h>
#include <stdlib.h>
#include "clist.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <raymath.h>


#define INDEX_HEAD_UP 0
#define INDEX_HEAD_DOWN 1
#define INDEX_HEAD_RIGHT 2
#define INDEX_HEAD_LEFT 3
#define INDEX_TAIL_UP 4
#define INDEX_TAIL_DOWN 5
#define INDEX_TAIL_RIGHT 6
#define INDEX_TAIL_LEFT 7
#define INDEX_BODY_HORZ 8
#define INDEX_BODY_VERT 9
#define INDEX_BODY_TOP_LEFT 10
#define INDEX_BODY_TOP_RIGHT 11
#define INDEX_BODY_BOTTOM_LEFT 12
#define INDEX_BODY_BOTTOM_RIGHT 13

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

Texture2D fruit_texture;
Texture2D background_texture;
Texture2D move_texture;
Texture2D time_texture;
Texture2D music_on_texture;
Texture2D music_off_texture;
Texture2D start_texture;
Texture2D help_texture;
Texture2D new_game_texture;
Texture2D play_button_texture;
Texture2D snake_texture[14];

Font font;
Sound pop;
Sound  fail;
 



 

typedef struct
{
    Texture2D up;
    Texture2D down;
    Texture2D left;
    Texture2D right;
} SnakeHeadTexture;
SnakeHeadTexture sht;
typedef struct
{
    Texture2D up;
    Texture2D down;
    Texture2D left;
    Texture2D right;
} SnakeBodyTexture;
SnakeBodyTexture sbt;

typedef struct
{
    Texture2D up;
    Texture2D down;
    Texture2D left;
    Texture2D right;
} SnakeTailTexture;
SnakeTailTexture stt;

 
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




