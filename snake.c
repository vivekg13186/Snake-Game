#include "snake.h"

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
void putScore(char* text,Rectangle v, Rectangle src, Rectangle dst, Vector2 offset)
{
    Rectangle c = button_coo(v, src, dst, offset);
    DrawText(text,c.x, c.y, 20, WHITE);
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
Texture2D get_snake_body_texture(Vector2 cur, Vector2 prev, Vector2 next)
{

    if (cur.x == prev.x && cur.x == next.x)
    {
        return snake_texture[INDEX_BODY_VERT];
    }
    else if (cur.y == prev.y && cur.y == next.y)
    {
        return snake_texture[INDEX_BODY_HORZ];
    }

    Vector2 ndir = Vector2Subtract(cur, next);
    Vector2 pdir = Vector2Subtract(cur, prev);

    if ((IS_UP(ndir) && IS_LEFT(pdir)) || (IS_UP(pdir) && IS_LEFT(ndir)))
    {
        return snake_texture[INDEX_BODY_BOTTOM_RIGHT];
    }

    if ((IS_UP(ndir) && IS_RIGHT(pdir)) || (IS_UP(pdir) && IS_RIGHT(ndir)))
    {
        return snake_texture[INDEX_BODY_BOTTOM_LEFT];
    }

    if ((IS_DOWN(ndir) && IS_RIGHT(pdir)) || (IS_DOWN(pdir) && IS_RIGHT(ndir)))
    {
        return snake_texture[INDEX_BODY_TOP_LEFT];
    }

    return snake_texture[INDEX_BODY_TOP_RIGHT];
}
Texture2D get_snake_head_texture(Vector2 v)
{

    if (IS_UP(v))
    {
        return snake_texture[INDEX_HEAD_UP];
    }
    if (IS_DOWN(v))
    {
        return snake_texture[INDEX_HEAD_DOWN];
    }
    if (IS_LEFT(v))
    {
        return snake_texture[INDEX_HEAD_LEFT];
    }
    if (IS_RIGHT(v))
    {
        return snake_texture[INDEX_HEAD_RIGHT];
    }
}

Texture2D get_snake_tail_texture(Vector2 v)
{

    if (IS_UP(v))
    {
        return snake_texture[INDEX_TAIL_UP];
    }
    if (IS_DOWN(v))
    {
        return snake_texture[INDEX_TAIL_DOWN];
    }
    if (IS_LEFT(v))
    {
        return snake_texture[INDEX_TAIL_LEFT];
    }
    if (IS_RIGHT(v))
    {
        return snake_texture[INDEX_TAIL_RIGHT];
    }
}
void print_stats()
{
    char buf[256];
    sprintf(buf, "%d", state.score);

    DrawTexturePro(fruit_texture, (Rectangle){0, 0, fruit_texture.width, fruit_texture.height}, (Rectangle){20, 10, 30, 30}, (Vector2){0, 0}, 0, WHITE);
    DrawTextEx(font, buf, (Vector2){55, 15}, 24, 1, WHITE);

    sprintf(buf, "%d", state.movement);
    DrawTexturePro(move_texture, (Rectangle){0, 0, move_texture.width, move_texture.height}, (Rectangle){150, 10, 30, 30}, (Vector2){0, 0}, 0, WHITE);
    DrawTextEx(font, buf, (Vector2){185, 15}, 24, 1, WHITE);

    sprintf(buf, "%.2f", state.time);
    DrawTexturePro(time_texture, (Rectangle){0, 0, time_texture.width, time_texture.height}, (Rectangle){280, 10, 30, 30}, (Vector2){0, 0}, 0, WHITE);
    DrawTextEx(font, buf, (Vector2){320, 15}, 24, 1, WHITE);
    Rectangle icon_size = (Rectangle){GetScreenWidth() - 50, 15, 25, 25};
    if (state.is_music_on)
    {
        DrawTexturePro(music_on_texture, (Rectangle){0, 0, music_on_texture.width, music_on_texture.height}, icon_size, (Vector2){0, 0}, 0, WHITE);
    }

    else
    {
        DrawTexturePro(music_off_texture, (Rectangle){0, 0, music_off_texture.width, music_off_texture.height}, icon_size, (Vector2){0, 0}, 0, WHITE);
    }
}
void draw_game_over()
{

    int x = (GetScreenWidth() / 2) - (MeasureText("Game Over.Press 'R' to restart.", 12) / 2);
    DrawTextEx(font, "Game Over.Press 'R' to restart.", (Vector2){x, GetScreenHeight() / 2}, 20, 1, WHITE);
}
void draw_fruit()
{

    Vector2 pos;
    grid_to_local(&(state.fruit), &pos);
    DrawTextureEx(fruit_texture, pos, 0, 0.5, WHITE);
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

        Texture2D txt;
        if (i == 0)
        {

            txt = get_snake_head_texture(state.snake.direction);
        }
        else if (i == tail)
        {
            Vector2 *prev = state.snake.body->at(state.snake.body, i - 1);

            txt = get_snake_tail_texture(Vector2Subtract(*v, *prev));
        }
        else
        {
            Vector2 *prev = state.snake.body->at(state.snake.body, i - 1);
            Vector2 *next = state.snake.body->at(state.snake.body, i + 1);
            txt = get_snake_body_texture(*v, *prev, *next);
        }
        Vector2 pos;
        grid_to_local(v, &pos);
        DrawTexturePro(txt, (Rectangle){0, 0, txt.width, txt.height}, (Rectangle){pos.x, pos.y, CELL_SIZE + 1, CELL_SIZE}, (Vector2){0, 0}, 0, WHITE);
    }
}

void draw_background()
{
    ClearBackground(BLACK);
    float scale = 0.390625;
    int top = CELL_SIZE + DASHBOARD_HEIGHT;

    DrawRectangle(0, 0, GetScreenWidth(), DASHBOARD_HEIGHT, (Color){203, 157, 135, 255});

    DrawRectangle(0, DASHBOARD_HEIGHT, GetScreenWidth(), GetScreenHeight(), (Color){38, 24, 27, 255});
    DrawTextureTiled(background_texture,
                     (Rectangle){0, 0, background_texture.width, background_texture.height},
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

    snake_texture[INDEX_HEAD_UP] = load_pp_texture("assets/snake_textures/snake_head_up.png");

    snake_texture[INDEX_HEAD_DOWN] = load_pp_texture("assets/snake_textures/snake_head_down.png");
    snake_texture[INDEX_HEAD_RIGHT] = load_pp_texture("assets/snake_textures/snake_head_right.png");
    snake_texture[INDEX_HEAD_LEFT] = load_pp_texture("assets/snake_textures/snake_head_left.png");
    snake_texture[INDEX_TAIL_UP] = load_pp_texture("assets/snake_textures/snake_tail_up.png");
    snake_texture[INDEX_TAIL_DOWN] = load_pp_texture("assets/snake_textures/snake_tail_down.png");
    snake_texture[INDEX_TAIL_RIGHT] = load_pp_texture("assets/snake_textures/snake_tail_right.png");
    snake_texture[INDEX_TAIL_LEFT] = load_pp_texture("assets/snake_textures/snake_tail_left.png");
    snake_texture[INDEX_BODY_HORZ] = load_pp_texture("assets/snake_textures/snake_body_horz.png");
    snake_texture[INDEX_BODY_VERT] = load_pp_texture("assets/snake_textures/snake_body_vert.png");
    snake_texture[INDEX_BODY_TOP_LEFT] = load_pp_texture("assets/snake_textures/snake_body_top_left.png");
    snake_texture[INDEX_BODY_TOP_RIGHT] = load_pp_texture("assets/snake_textures/snake_body_top_right.png");
    snake_texture[INDEX_BODY_BOTTOM_LEFT] = load_pp_texture("assets/snake_textures/snake_body_bottom_left.png");
    snake_texture[INDEX_BODY_BOTTOM_RIGHT] = load_pp_texture("assets/snake_textures/snake_body_bottom_right.png");

    fruit_texture = load_pp_texture("assets/apple.png");

    move_texture = load_pp_texture("assets/key.png");
    time_texture = load_pp_texture("assets/clock.png");
    background_texture = load_pp_texture("assets/checker.png");
    music_on_texture = load_pp_texture("assets/sound_on.png");
    music_off_texture = load_pp_texture("assets/sound_off.png");

    start_texture = load_pp_texture("assets/banner.png");
    help_texture = load_pp_texture("assets/help.png");
    new_game_texture = load_pp_texture("assets/game_over.png");

    font = LoadFont("assets/Roboto-Medium.ttf");
    pop = LoadSound("assets/eat.ogg");
    fail = LoadSound("assets/fail.ogg");
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
    Rectangle src = (Rectangle){0, 0, start_texture.width, start_texture.height};
    Rectangle dst = (Rectangle){0, 0, width, height};
    Vector2 pos = (Vector2){x, y};

    if (is_button_click(button_marathon, src, dst, pos))
    {
        TraceLog(LOG_INFO, "Marthon clicked");
        state.run_mode = GAME_MODE_MARATHON;
        state.mode = PAUSE_GAME;
    }
    else if (is_button_click(button_sprint, src, dst, pos))
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

    // 16,36  83,51
    // debug_button((Rectangle){(22/100),(50/100),100,100},x,y);

    DrawTexturePro(start_texture, (Rectangle){0, 0, start_texture.width, start_texture.height}, (Rectangle){x, y, width, height}, (Vector2){0, 0}, 1, WHITE);
    // debug_button(button_marathon,src,dst,pos);
    // debug_button(button_sprint,src,dst,pos);
    // debug_button(button_help,src,dst,pos);
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
    Rectangle src = (Rectangle){0, 0, new_game_texture.width, new_game_texture.height};
    Rectangle dst = (Rectangle){0, 0, width, height};
    Vector2 pos = (Vector2){x, y};
     if(is_button_click(button_home_game_over,src,dst,pos)){
        reset_state();
        state.mode=START_SCREEN;
     }
   BeginDrawing();
    draw_background();
    print_stats();


    char buf[256];
     
    DrawTexturePro(new_game_texture, (Rectangle){0, 0, new_game_texture.width, new_game_texture.height}, (Rectangle){x, y, width, height}, (Vector2){0, 0}, 1, WHITE);
     sprintf(buf, "%d", state.score);
    putScore(buf,cherry_score_box,src,dst,pos);
     sprintf(buf, "%.2f", state.time);
    putScore(buf,time_score_box,src,dst,pos);
    sprintf(buf, "%d", state.movement);
     putScore(buf,key_score_box,src,dst,pos);
    EndDrawing();
}


void help_screen()
{
    float width = GetScreenWidth() / 2;
    float height = GetScreenHeight() / 2;
    int x = width / 2;
    int y = height / 2;
    Rectangle src = (Rectangle){0, 0, help_texture.width, help_texture.height};
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

    DrawTexturePro(help_texture, (Rectangle){0, 0, help_texture.width, help_texture.height}, (Rectangle){x, y, width, height}, (Vector2){0, 0}, 1, WHITE);
    //debug_button(button_home,src,dst,pos);
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

        if (IsKeyPressed(KEY_M))
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