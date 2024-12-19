#include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#undef main
struct bullet
{
    int x;
    int y;
    struct bullet *next;
};
struct plane
{
    int x;
    int y;
    bool still_live;
    int lives;
    int score; // 新增变量：杀敌数
    struct bullet *my_bullet;
};
struct enemy
{
    int x;
    int y;
    struct enemy *next;
    int enemykind;
};
struct plane playerPlane;
struct enemy *enemyPlane; // head node of enemy
void addenemyPlane();
void gameDraw();
void enemyMove();
void bulletMove();
void planeMove(SDL_Event e);
void shoot();
void gameInit();
void check_hit();
void update();
void music();
void gamerestart();
int begin, t1, end, t2;
SDL_Window *window = NULL;
SDL_Renderer *rr = NULL;
int most_enemy = 0;
const int FPS = 1000 / 20;
Uint32 _FPS_Timer;
int main(int args, char *argv[])
{ // init graph

    SDL_Init(SDL_INIT_VIDEO);
    // Mix_Init(MIX_INIT_MP3);
    window = SDL_CreateWindow("plane game",
                              500,
                              150,
                              400, 600,
                              SDL_WINDOW_SHOWN);

    rr = SDL_CreateRenderer(window, -1, 0);
    gameInit();
    // music();
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        end = GetTickCount();
        t2 = GetTickCount();
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                planeMove(e); // 处理玩家移动
            }
        }
        update();    // 更新游戏状态
        check_hit(); // 检查碰撞
        gameDraw();  // 绘制游戏画面
        if (SDL_GetTicks() - _FPS_Timer < FPS)
        {
            SDL_Delay(FPS - SDL_GetTicks() + _FPS_Timer);
        }
        _FPS_Timer = SDL_GetTicks();
        if (t2 - t1 >= 2000)
        {
            addenemyPlane(); 
            t1 = t2;
        }
    }

    // Mix_FreeMusic(bgm);
    //  Mix_CloseAudio();
    SDL_DestroyRenderer(rr);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void planeMove(SDL_Event e)
{
    switch (e.key.keysym.sym)
    {
    case SDLK_w:
    case SDLK_UP:
        playerPlane.y = playerPlane.y - 20;
        if (playerPlane.y == 0)
        {
            playerPlane.y = 0;
        }
        break;
    case SDLK_s:
    case SDLK_DOWN:
        playerPlane.y = playerPlane.y + 20;
        if (playerPlane.y > 600)
        {
            playerPlane.y = 600;
        }
        break;
    case SDLK_a:
    case SDLK_LEFT:
        playerPlane.x = playerPlane.x - 20;
        if (playerPlane.x < 0)
        {
            playerPlane.x = 0;
        }
        break;
    case SDLK_RIGHT:
    case SDLK_d:
        playerPlane.x = playerPlane.x + 20;
        if (playerPlane.x > 400)
        {
            playerPlane.x = 400;
        }
        break;
    case SDLK_SPACE:
        shoot();
        break;
        // we can add new command to make it have more fearture
    case SDLK_r: // restart function
      gamerestart();
        break;
    case SDLK_o:
        playerPlane.score += 2;
        break;
    case SDLK_l:
        addenemyPlane();
        break;
    }
}
void addenemyPlane()
{
    if (most_enemy < 4)
    {
        srand((unsigned)time(NULL));
        int a[5] = {-30, -50, 0, 60, 90};
        int b = rand() % 5;
        int x_random = rand() % 401 + a[b];
        if (x_random > 550)
            x_random = 550;
        if (x_random < 50)
            x_random = 50;
        int enemykind = rand() % 43; // show enemykind make it more random
        struct enemy *newplane = (struct enemy *)malloc(sizeof(struct enemy *));
        newplane->x = x_random; // we need to make it random
        newplane->y = 50;
        newplane->next = enemyPlane->next;
        enemyPlane->next = newplane;
        most_enemy++;
    }
}
void enemyMove()
{
    struct enemy *temp_enemyPlane = enemyPlane;
    struct enemy *delete_enemyPlane;
    while (temp_enemyPlane->next != NULL)
    {
        temp_enemyPlane->next->y += rand() % 10;
        if (temp_enemyPlane->next->y >= 800)
        {
            delete_enemyPlane = temp_enemyPlane->next;
            temp_enemyPlane->next = delete_enemyPlane->next;
            free(delete_enemyPlane);
            delete_enemyPlane = NULL;
            continue;
        }
        temp_enemyPlane = temp_enemyPlane->next;
    }
}
void shoot()
{
    struct bullet *new_bullet = (struct bullet *)malloc(sizeof(struct bullet *));
    new_bullet->x = playerPlane.x + 11;
    new_bullet->y = playerPlane.y - 5;
    new_bullet->next = playerPlane.my_bullet->next;
    playerPlane.my_bullet->next = new_bullet;
}
void bulletMove()
{
    struct bullet *bullet_head = playerPlane.my_bullet;
    struct bullet *delete_bullet;
    while (bullet_head->next != NULL)
    {
        bullet_head->next->y -= 10;
        if (bullet_head->next->y < 0)
        {
            delete_bullet = bullet_head->next;
            bullet_head->next = delete_bullet->next;
            free(delete_bullet);
            delete_bullet = NULL;
            continue;
        }
        struct enemy *tmpEnemy = enemyPlane;
        struct enemy *delete_enemy;
        while (tmpEnemy->next != NULL)
        {
            if ((bullet_head->next->x >= tmpEnemy->next->x) && (bullet_head->next->x <= tmpEnemy->next->x + 80) && (bullet_head->next->y <= tmpEnemy->next->y + 40))
            {
                // load boom
                playerPlane.score++; // 分数增加
                delete_enemy = tmpEnemy->next;
                tmpEnemy->next = delete_enemy->next;
                free(delete_enemy);
                delete_enemy = NULL;
                delete_bullet = bullet_head->next;
                bullet_head->next = delete_bullet->next;
                free(delete_bullet);
                delete_bullet = NULL;
                most_enemy--;
            }
            if (tmpEnemy->next == NULL)
            {
                break;
            }
            tmpEnemy = tmpEnemy->next;
        }
        if (bullet_head->next == NULL)
        {
            break;
        }
        bullet_head = bullet_head->next;
    }
}
void check_hit()
{
    struct enemy *tempEnemy = enemyPlane->next;
    while (tempEnemy)
    {
        if (playerPlane.x < tempEnemy->x + 50 && playerPlane.x + 50 > tempEnemy->x && playerPlane.y < tempEnemy->y + 50 && playerPlane.y + 50 > tempEnemy->y)
        {
            playerPlane.still_live = false;
            printf("Your score:%d", playerPlane.score);
            break;
        }
        tempEnemy = tempEnemy->next;
    }
}
//  void music()
//  {
//  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,2048);
//  Mix_Music *bgm=Mix_LoadMUS("./image/bgm.mp3");
//   Mix_PlayMusic(bgm,1);
//  }
void gameInit()
{
    // init plane
    playerPlane.x = 170;
    playerPlane.y = 500;
    playerPlane.still_live = true;
    playerPlane.score = 0; // 初始化分数为0
    // init bullet
    playerPlane.my_bullet = (struct bullet *)malloc(sizeof(struct bullet));
    playerPlane.my_bullet->next = NULL;
    // init enemy
    enemyPlane = (struct enemy *)malloc(sizeof(struct enemy));
    enemyPlane->x = 0;
    enemyPlane->y = 0;
    enemyPlane->next = NULL;
    // init time
    begin = GetTickCount();
    t1 = GetTickCount();
    // add enemy
}
void gameDraw()
{
    SDL_RenderClear(rr);
    // start to draw background photo

    SDL_Surface *background_surf = SDL_LoadBMP("./image/background1.bmp");
    SDL_Surface *myp_surf = NULL;
    SDL_Surface *enp_surf = NULL;
    SDL_Surface *bull_surf = NULL;
    SDL_Surface *go_surf = SDL_LoadBMP("./image/gameover1.bmp");

    if (playerPlane.score > 5) // 升级
    {
        myp_surf = SDL_LoadBMP("./image/myplane3.bmp");
        bull_surf = SDL_LoadBMP("./image/bullet3.bmp");
    }
    else if (playerPlane.score > 2)
    {
        myp_surf = SDL_LoadBMP("./image/myplane2.bmp");
        bull_surf = SDL_LoadBMP("./image/bullet2.bmp");
    }
    else
    {
        myp_surf = SDL_LoadBMP("./image/myplane1.bmp");
        bull_surf = SDL_LoadBMP("./image/bullet1.bmp");
    }

    SDL_Texture *back_te = SDL_CreateTextureFromSurface(rr, background_surf);
    SDL_Texture *mp_te = SDL_CreateTextureFromSurface(rr, myp_surf);

    SDL_Texture *bull_te = SDL_CreateTextureFromSurface(rr, bull_surf);
    SDL_Texture *go_te = SDL_CreateTextureFromSurface(rr, go_surf);

    SDL_SetTextureBlendMode(mp_te, SDL_BLENDMODE_BLEND);

    SDL_SetTextureBlendMode(bull_te, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(go_te, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(myp_surf);

    SDL_FreeSurface(background_surf);
    SDL_FreeSurface(bull_surf);
    SDL_FreeSurface(go_surf);

    SDL_RenderCopy(rr, back_te, NULL, NULL);
    // if playPlane is alive,draw picture
    if (playerPlane.still_live)
    {
        SDL_Rect myplane_rect = {playerPlane.x, playerPlane.y, 50, 67};
        SDL_RenderCopy(rr, mp_te, NULL, &myplane_rect);
    }
    else // draw game over
    {

        // SDL_DestroyTexture(mp_te);
        myp_surf = SDL_LoadBMP("./image/boom.bmp");
        SDL_Texture *mp_te = SDL_CreateTextureFromSurface(rr, myp_surf);
        SDL_SetTextureBlendMode(mp_te, SDL_BLENDMODE_BLEND);
        SDL_Rect myplane_rect = {playerPlane.x, playerPlane.y, 50, 67};
        SDL_RenderCopy(rr, mp_te, NULL, &myplane_rect);
        SDL_FreeSurface(myp_surf);
        SDL_DestroyTexture(back_te);
        SDL_DestroyTexture(bull_te);
        SDL_Rect gameover_rect = {50, 200, 300, 150}; // draw game over
        SDL_RenderCopy(rr, go_te, NULL, &gameover_rect);
    }
    // draw enemy
    struct enemy *tempPlane = enemyPlane->next;
    while (tempPlane)
    {
        tempPlane->enemykind = (4 + enemyPlane->enemykind) % 3;
        if (tempPlane->enemykind == 0)
            enp_surf = SDL_LoadBMP("./image/enemy1.bmp");
        else if (tempPlane->enemykind == 1)
            enp_surf = SDL_LoadBMP("./image/enemy2.bmp");
        else if (tempPlane->enemykind == 2)
            enp_surf = SDL_LoadBMP("./image/enemy3.bmp");
        SDL_Texture *en_te = SDL_CreateTextureFromSurface(rr, enp_surf);
        SDL_SetTextureBlendMode(en_te, SDL_BLENDMODE_BLEND);
        SDL_FreeSurface(enp_surf);
        // draw picture
        SDL_Rect enplane_rect = {tempPlane->x, tempPlane->y, 50, 67};
        SDL_RenderCopy(rr, en_te, NULL, &enplane_rect);
        tempPlane = tempPlane->next;
    }

    // draw bullet
    struct bullet *playerBullet = playerPlane.my_bullet->next;
    while (playerBullet)
    {
        // draw picture
        SDL_Rect bull_rect = {playerBullet->x, playerBullet->y, 30, 30};
        SDL_RenderCopy(rr, bull_te, NULL, &bull_rect);
        playerBullet = playerBullet->next;
    }
    // to end drawing
    SDL_RenderPresent(rr);
}
void gamerestart()
{
  // 删除所有飞机
  struct enemy *tempEnemy = enemyPlane->next;
  struct enemy *deleteEnemy;
  while (tempEnemy != NULL)
  {
    deleteEnemy = tempEnemy;
    tempEnemy = tempEnemy->next;
    free(deleteEnemy);
  }
  enemyPlane->next = NULL; // 清空敌人链表

  // 清除所有子弹
  struct bullet *tempBullet = playerPlane.my_bullet->next;
  struct bullet *deleteBullet;
  while (tempBullet != NULL)
  {
    deleteBullet = tempBullet;
    tempBullet = tempBullet->next;
    free(deleteBullet);
  }
  playerPlane.my_bullet->next = NULL; // 清空子弹链表

  // 初始化玩家飞机
  playerPlane.x = 170;
  playerPlane.y = 500;
  playerPlane.still_live = true;
  playerPlane.score = 0; // 初始化分数为0

  // 初始化子弹链表
  playerPlane.my_bullet = (struct bullet *)malloc(sizeof(struct bullet));
  if (!playerPlane.my_bullet)
  {
    printf("Failed to allocate memory for bullets\n");
    exit(1); // 退出程序或进行其他错误处理
  }
  playerPlane.my_bullet->next = NULL;

  // 初始化敌人链表
  if (enemyPlane)
  {
    free(enemyPlane);
  }
  enemyPlane = (struct enemy *)malloc(sizeof(struct enemy));
  if (!enemyPlane)
  {
    printf("Failed to allocate memory for enemy plane\n");
    exit(1); // 退出程序或进行其他错误处理
  }
  enemyPlane->x = 0;
  enemyPlane->y = 0;
  enemyPlane->next = NULL;

  // 初始化时间
  begin = GetTickCount();
  t1 = GetTickCount();

  // 重置敌人数量
  most_enemy = 0;
}
void update()
{
    enemyMove();
    bulletMove();
}
