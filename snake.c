#include "snake.h"

Vector2 ZERO = (Vector2){0, 0};

void draw_text(char *text, int x, int y)
{
    int i = 0;
    char c = text[i];
    
    while (c != '\0')
    {
        int tile_index = -1;
        switch (c)
        {
        case '0':
        {
            tile_index = TILE_CHAR_0;
            break;
        }
        case '1':
        {
            tile_index = TILE_CHAR_1;
            break;
        }
        case '2':
        {
            tile_index = TILE_CHAR_2;
            break;
        }
        case '3':
        {
            tile_index = TILE_CHAR_3;
            break;
        }
        case '4':
        {
            tile_index = TILE_CHAR_4;
            break;
        }
        case '5':
        {
            tile_index = TILE_CHAR_5;
            break;
        }
        case '6':
        {
            tile_index = TILE_CHAR_6;
            break;
        }
        case '7':
        {
            tile_index = TILE_CHAR_7;
            break;
        }
        case '8':
        {
            tile_index = TILE_CHAR_8;
            break;
        }
        case '9':
        {
            tile_index = TILE_CHAR_9;
            break;
        }
        case '.':
        {
            tile_index = TILE_CHAR_POINT;
            break;
        }
        default:
            break;
        }
        if (tile_index != -1)
        {
            rtpAtlasSprite tile = rtpDescAsset[tile_index];
            Rectangle pos = {x, y, tile.sourceWidth, tile.sourceHeight};
            DrawTexturePro(texture_pack, (Rectangle){tile.positionX, tile.positionY, tile.sourceWidth, tile.sourceHeight}, pos, ZERO, 0, WHITE);
            x += tile.sourceWidth + 5;
        }
        i++;
        c =text[i];
    }
}
void draw_tile(int index, Rectangle rec)
{
    rtpAtlasSprite tile = rtpDescAsset[index];
    DrawTexturePro(texture_pack, (Rectangle){tile.positionX, tile.positionY, tile.sourceWidth, tile.sourceHeight}, rec, ZERO, 0, WHITE);
}
rtpAtlasSprite get_tile(int index)
{
    return rtpDescAsset[index];
}

Rectangle button_coo(Rectangle v, Rectangle src, Rectangle dst, Vector2 offset)
{
    float x1 = Remap(v.x, src.x, src.width, dst.x, dst.width) + offset.x;
    float y1 = Remap(v.y, src.y, src.height, dst.y, dst.height) + offset.y;
    float width = Remap(v.width, src.x, src.width, dst.x, dst.width);
    float height = Remap(v.height, src.y, src.height, dst.y, dst.height);
    return (Rectangle){x1, y1, width, height};
}
bool is_button_click(Rectangle v, Rectangle src, Rectangle dst, Vector2 offset)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {

        return CheckCollisionPointRec(GetMousePosition(), button_coo(v, src, dst, offset));
    }
    return false;
}

void debug_button(Rectangle v, Rectangle src, Rectangle dst, Vector2 offset)
{
    Rectangle c = button_coo(v, src, dst, offset);
    DrawRectangleLines(c.x, c.y, c.width, c.height, RED);
}
void putScore(char *text, Rectangle v, Rectangle src, Rectangle dst, Vector2 offset)
{
    Rectangle c = button_coo(v, src, dst, offset);
    //DrawText(text, c.x, c.y, 20, WHITE);
    draw_text(text,c.x, c.y);
}
void play_sound(Sound s)
{
    if (state.is_music_on)
    {
        PlaySound(s);
    }
}

void grid_to_local(Vector2 *src, Vector2 *dest)
{
    dest->x = (src->x * CELL_SIZE) + CELL_SIZE;
    dest->y = (src->y * CELL_SIZE) + CELL_SIZE + DASHBOARD_HEIGHT;
}
int get_snake_body_texture(Vector2 cur, Vector2 prev, Vector2 next)
{

    if (cur.x == prev.x && cur.x == next.x)
    {
        return TILE_SNAKE_BODY_VERT;
    }
    else if (cur.y == prev.y && cur.y == next.y)
    {
        return TILE_SNAKE_BODY_HORZ;
    }

    Vector2 ndir = Vector2Subtract(cur, next);
    Vector2 pdir = Vector2Subtract(cur, prev);

    if ((IS_UP(ndir) && IS_LEFT(pdir)) || (IS_UP(pdir) && IS_LEFT(ndir)))
    {
        return TILE_SNAKE_BODY_BOTTOM_RIGHT;
    }

    if ((IS_UP(ndir) && IS_RIGHT(pdir)) || (IS_UP(pdir) && IS_RIGHT(ndir)))
    {
        return TILE_SNAKE_BODY_BOTTOM_LEFT;
    }

    if ((IS_DOWN(ndir) && IS_RIGHT(pdir)) || (IS_DOWN(pdir) && IS_RIGHT(ndir)))
    {
        return TILE_SNAKE_BODY_TOP_LEFT;
    }

    return TILE_SNAKE_BODY_TOP_RIGHT;
}
int get_snake_head_texture(Vector2 v)
{

    if (IS_UP(v))
    {
        return TILE_SNAKE_HEAD_UP;
    }
    if (IS_DOWN(v))
    {
        return TILE_SNAKE_HEAD_DOWN;
    }
    if (IS_LEFT(v))
    {
        return TILE_SNAKE_HEAD_LEFT;
    }
    if (IS_RIGHT(v))
    {
        return TILE_SNAKE_HEAD_RIGHT;
    }
}

int get_snake_tail_texture(Vector2 v)
{

    if (IS_UP(v))
    {
        return TILE_SNAKE_TAIL_UP;
    }
    if (IS_DOWN(v))
    {
        return TILE_SNAKE_TAIL_DOWN;
    }
    if (IS_LEFT(v))
    {
        return TILE_SNAKE_TAIL_LEFT;
    }
    if (IS_RIGHT(v))
    {
        return TILE_SNAKE_TAIL_RIGHT;
    }
}
void print_stats()
{
    char buf[256];
    sprintf(buf, "%d", state.score);
    int y = 20;

    draw_tile(TILE_APPLE, (Rectangle){20, 10, 30, 30});
    //DrawTextEx(font, buf, (Vector2){55, 15}, 24, 1, WHITE);
    draw_text(buf,55,y);

    draw_tile(TILE_KEY, (Rectangle){150, 10, 30, 30});
    sprintf(buf, "%d", state.movement);
    //DrawTextEx(font, buf, (Vector2){185, 15}, 24, 1, WHITE);
    draw_text(buf,185, y);

    draw_tile(TILE_CLOCK, (Rectangle){280, 10, 30, 30});
    sprintf(buf, "%.2f", state.time);
    //DrawTextEx(font, buf, (Vector2){320, 15}, 24, 1, WHITE);
     draw_text(buf,320, y);
    Rectangle icon_size = (Rectangle){GetScreenWidth() - 50, 15, 25, 25};
    if (state.is_music_on)
    {
        draw_tile(TILE_SOUND_ON, icon_size);
    }

    else
    {
        draw_tile(TILE_SOUND_OFF, icon_size);
    }
}

void draw_fruit()
{

    Vector2 pos;
    grid_to_local(&(state.fruit), &pos);
    rtpAtlasSprite tile = rtpDescAsset[TILE_APPLE];
    draw_tile(TILE_APPLE, (Rectangle){pos.x, pos.y, tile.sourceWidth / 2, tile.sourceHeight / 2});
}

void spawn_fruit()
{

    state.fruit.x = GetRandomValue(1, CELL_NUMBER - 1);
    state.fruit.y = GetRandomValue(1, CELL_NUMBER - 1);
}
void draw_snake()
{

    int tail = length(state.snake.body) - 1;

    for (int i = 0; i < length(state.snake.body); i++)
    {

        Vector2 *v = state.snake.body->at(state.snake.body, i);

        int tile_index;
        if (i == 0)
        {

            tile_index = get_snake_head_texture(state.snake.direction);
        }
        else if (i == tail)
        {
            Vector2 *prev = state.snake.body->at(state.snake.body, i - 1);

            tile_index = get_snake_tail_texture(Vector2Subtract(*v, *prev));
        }
        else
        {
            Vector2 *prev = state.snake.body->at(state.snake.body, i - 1);
            Vector2 *next = state.snake.body->at(state.snake.body, i + 1);
            tile_index = get_snake_body_texture(*v, *prev, *next);
        }
        Vector2 pos;
        grid_to_local(v, &pos);
        draw_tile(tile_index, (Rectangle){pos.x, pos.y, CELL_SIZE + 1, CELL_SIZE});
    }
}

void draw_background()
{
    ClearBackground(BLACK);
    float scale = 0.390625;
    int top = CELL_SIZE + DASHBOARD_HEIGHT;

    DrawRectangle(0, 0, GetScreenWidth(), DASHBOARD_HEIGHT, (Color){203, 157, 135, 255});

    DrawRectangle(0, DASHBOARD_HEIGHT, GetScreenWidth(), GetScreenHeight(), (Color){38, 24, 27, 255});
    rtpAtlasSprite tile_region = rtpDescAsset[TILE_CHECKER];
    DrawTextureTiled(texture_pack,
                     (Rectangle){tile_region.positionX, tile_region.positionY, tile_region.sourceWidth, tile_region.sourceHeight},
                     (Rectangle){CELL_SIZE, top, CELL_NUMBER * CELL_SIZE, CELL_NUMBER * CELL_SIZE},
                     (Vector2){0, 0}, 0, scale, WHITE);
}
void move_snake()
{

    Vector2 *top = state.snake.body->at(state.snake.body, 0);
    Vector2 *nu = create_vec2(top->x + state.snake.direction.x, top->y + state.snake.direction.y);
    state.snake.body->insert(state.snake.body, nu, 0);
    if (state.snake.addNewBlock == false)
    {
        int index = length(state.snake.body) - 1;
        state.snake.body->remove(state.snake.body, index);
    }
    else
    {
        state.snake.addNewBlock = false;
    }
}

Vector2 *create_vec2(int x, int y)
{
    Vector2 *v = malloc(sizeof(Vector2));
    v->x = x;
    v->y = y;
    return v;
}
void check_fail()
{
    Vector2 *top = state.snake.body->at(state.snake.body, 0);

    if (top->x < 0 || top->x > CELL_NUMBER - 1 || top->y < 0 || top->y > CELL_NUMBER - 1)
    {
        state.mode = FAIL_SCREEN;
        if (state.is_music_on)
        {
            PlaySound(fail);
        }
    }
    for (int i = 1; i < length(state.snake.body); i++)
    {
        Vector2 *b = state.snake.body->at(state.snake.body, i);
        if (top->x == b->x && top->y == b->y)
        {
            state.mode = FAIL_SCREEN;
            if (state.is_music_on)
            {
                PlaySound(fail);
            }
            break;
        }
    }
}
void check_collosion()
{
    Vector2 *snake_pos = state.snake.body->at(state.snake.body, 0);
    Vector2 f_pos = state.fruit;
    if (snake_pos->x == f_pos.x && snake_pos->y == state.fruit.y)
    {

        if (state.is_music_on)
        {
            PlaySound(pop);
        }
        state.score++;
        if (state.run_mode == GAME_MODE_SPRINT)
        {
            if (state.score % SCORE_TO_SPEED == 0)
            {
                TraceLog(LOG_INFO, "spped up");
                state.speed -= 0.05;
                state.speed = state.speed < MAX_SPEED ? MAX_SPEED : state.speed;
            }
        }

        spawn_fruit();
        state.snake.addNewBlock = true;
    }
}

void reset_state()
{
    state.snake.body->clear(state.snake.body);
    state.snake.body->add(state.snake.body, create_vec2(5, 10));
    state.snake.body->add(state.snake.body, create_vec2(4, 10));
    state.snake.body->add(state.snake.body, create_vec2(3, 10));
    state.snake.direction.x = 1;
    state.snake.direction.y = 0;
    state.snake.addNewBlock = false;
    state.score = 0;
    state.movement = 0;
    state.time = 0;
    state.speed = INIT_SPEED;
    state.is_music_on = true;

    spawn_fruit();
}
void update()
{
    move_snake();
    check_collosion();
    check_fail();
}

Texture2D load_pp_texture(char *filename)
{
    Texture2D res = LoadTexture(filename);
    SetTextureFilter(res, TEXTURE_FILTER_TRILINEAR);

    return res;
}
void load_resources()
{
    Image image_data = {0};
    image_data.format = IMAGE_DATA_FORMAT;
    image_data.height = IMAGE_DATA_HEIGHT;
    image_data.width = IMAGE_DATA_WIDTH;
    image_data.data = IMAGE_DATA_DATA;
    image_data.mipmaps = 1;
    texture_pack = LoadTextureFromImage(image_data);
    SetTextureFilter(texture_pack, TEXTURE_FILTER_TRILINEAR);

    Wave eat_wave = (Wave){
        EAT_FRAME_COUNT,
        EAT_SAMPLE_RATE, EAT_SAMPLE_SIZE, EAT_CHANNELS,
        eat_sound_dataData};
    pop = LoadSoundFromWave(eat_wave);
    Wave fail_wave = (Wave){
        FAIL_FRAME_COUNT,
        FAIL_SAMPLE_RATE, FAIL_SAMPLE_SIZE, FAIL_CHANNELS,
        fail_sound_dataData};
    fail = LoadSoundFromWave(fail_wave);

    font = LoadFont("assets/Roboto-Medium.ttf");
}
void logVector(Vector2 *v, char *msg)
{
    TraceLog(LOG_INFO, " %s x %f , y %f", msg, v->x, v->y);
}
void draw_start_screen()
{
    float width = GetScreenWidth() / 2;
    float height = GetScreenHeight() / 2;
    int x = width / 2;
    int y = height / 2;
    rtpAtlasSprite start_texture = get_tile(TILE_BANNER);
    Rectangle src = (Rectangle){0, 0, start_texture.sourceWidth, start_texture.sourceHeight};
    Rectangle dst = (Rectangle){0, 0, width, height};
    Vector2 pos = (Vector2){x, y};

    if (is_button_click(button_marathon, src, dst, pos)|| IsKeyPressed(KEY_M))
    {
        TraceLog(LOG_INFO, "Marthon clicked");
        state.run_mode = GAME_MODE_MARATHON;
        state.mode = PAUSE_GAME;
    }
    else if (is_button_click(button_sprint, src, dst, pos)|| IsKeyPressed(KEY_S))
    {
        TraceLog(LOG_INFO, "Sprint clicked");
        state.run_mode = GAME_MODE_SPRINT;
        state.mode = PAUSE_GAME;
    }
    else if (is_button_click(button_help, src, dst, pos))
    {
        TraceLog(LOG_INFO, "Help clicked");
        state.mode = HELP_SCREEN;
    }

    BeginDrawing();
    draw_background();
    print_stats();

    draw_tile(TILE_BANNER, (Rectangle){x, y, width, height});

    EndDrawing();
}
float delta = 0;
void draw_game()
{

    state.time += GetFrameTime();
    if (delta > state.speed)
    {
        update();
        delta = 0;
    }
    delta += GetFrameTime();

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D))
    {
        state.movement++;
    }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {

        if (state.snake.direction.y != 1)
        {
            state.snake.direction.x = 0;
            state.snake.direction.y = -1;
        }
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {

        if (state.snake.direction.x != -1)
        {
            state.snake.direction.x = 1;
            state.snake.direction.y = 0;
        }
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {

        if (state.snake.direction.y != -1)
        {
            state.snake.direction.x = 0;
            state.snake.direction.y = 1;
        }
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {

        if (state.snake.direction.x != 1)
        {
            state.snake.direction.x = -1;
            state.snake.direction.y = 0;
        }
    }

    BeginDrawing();
    draw_background();
    print_stats();
    draw_snake();
    draw_fruit();

    EndDrawing();
}

void pause_game()
{

    if (IsKeyPressed(KEY_W) ||
        IsKeyPressed(KEY_S) ||
        IsKeyPressed(KEY_A) ||
        IsKeyPressed(KEY_D) ||
        IsKeyPressed(KEY_UP) ||
        IsKeyPressed(KEY_DOWN) ||
        IsKeyPressed(KEY_LEFT) ||
        IsKeyPressed(KEY_RIGHT))
    {
        state.mode = PLAY_GAME;
    }
    BeginDrawing();
    draw_background();
    print_stats();
    draw_snake();
    draw_fruit();

    EndDrawing();
}
void fail_screen()
{

    float width = GetScreenWidth() / 2;
    float height = GetScreenHeight() / 2;
    int x = width / 2;
    int y = height / 2;
    rtpAtlasSprite new_game_texture = get_tile(TILE_GAME_OVER);
    Rectangle src = (Rectangle){0, 0, new_game_texture.sourceWidth, new_game_texture.sourceHeight};
    Rectangle dst = (Rectangle){0, 0, width, height};
    Vector2 pos = (Vector2){x, y};
    if (is_button_click(button_home_game_over, src, dst, pos))
    {
        reset_state();
        state.mode = START_SCREEN;
    }
    BeginDrawing();
    draw_background();
    print_stats();

    char buf[256];

    draw_tile(TILE_GAME_OVER, (Rectangle){x, y, width, height});
    sprintf(buf, "%d", state.score);
    putScore(buf, cherry_score_box, src, dst, pos);
    sprintf(buf, "%.2f", state.time);
    putScore(buf, time_score_box, src, dst, pos);
    sprintf(buf, "%d", state.movement);
    putScore(buf, key_score_box, src, dst, pos);
    EndDrawing();
}

void help_screen()
{
    float width = GetScreenWidth() / 2;
    float height = GetScreenHeight() / 2;
    int x = width / 2;
    int y = height / 2;
    rtpAtlasSprite help_texture = get_tile(TILE_HELP);
    Rectangle src = (Rectangle){0, 0, help_texture.sourceWidth, help_texture.sourceHeight};
    Rectangle dst = (Rectangle){0, 0, width, height};
    Vector2 pos = (Vector2){x, y};

    if (is_button_click(button_home, src, dst, pos))
    {
        TraceLog(LOG_INFO, "Home clicked");

        state.mode = START_SCREEN;
    }

    BeginDrawing();
    draw_background();
    print_stats();

    draw_tile(TILE_HELP, (Rectangle){x, y, width, height});

    EndDrawing();
}

int main()
{

    int width = (CELL_NUMBER * CELL_SIZE);
    int height = (CELL_NUMBER * CELL_SIZE);
    width += 2 * CELL_SIZE;
    height += (2 * CELL_SIZE) + DASHBOARD_HEIGHT;
    InitWindow(width, height, "Snake");
    SetTargetFPS(60);
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitAudioDevice();
    state.snake.body = CList_init(sizeof(Vector2));
    reset_state();
    state.mode = START_SCREEN;
    float delta = 0;

    load_resources();
    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    while (!WindowShouldClose())
    {

        if (IsWindowHidden() || IsWindowMinimized())
            continue;

        if (IsKeyPressed(KEY_V))
        {
            state.is_music_on = !state.is_music_on;
        }
        if (state.mode == START_SCREEN)
        {
            draw_start_screen();
        }

        if (state.mode == PAUSE_GAME)
        {
            pause_game();
        }
        if (state.mode == PLAY_GAME)
        {
            draw_game();
        }
        if (state.mode == FAIL_SCREEN)
        {
            fail_screen();
        }
        if (state.mode == HELP_SCREEN)
        {
            help_screen();
        }
    }
    CloseWindow();
    return 0;
}