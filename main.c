#include <SDL2/SDL.h>
#include <stdbool.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
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
    struct bullet *my_bullet;
};
struct enemy
{
    int x;
    int y;
    struct enemy *next;
};
struct plane playerPlane;
struct enemy *enemyPlane; // head node of enemy
void addenemyPlane();
void gameDraw();
void enemyMove();
void bulletMove();
void backMove();
void planeMove();
void shoot();
void gameInit();
void update()
{
    enemyMove();
    bulletMove();
    backMove();
}
void check_hit();
int begin, t1, end, t2;
SDL_Window *window = NULL;
SDL_Renderer *rr = NULL;
int main(int args, char *argv[])
{ // init graph

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("plane game",
                              400,
                              400,
                              400, 600,
                              SDL_WINDOW_SHOWN);

    rr = SDL_CreateRenderer(window, -1, 0);
    gameInit();
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
        }
        planeMove(); // 处理玩家移动
        update();    // 更新游戏状态
        check_hit(); // 检查碰撞
        gameDraw();  // 绘制游戏画面
        if (end - begin >= 50)
        {
            SDL_Delay(50 - (GetTickCount() - end)); // 控制帧率
            begin = GetTickCount();
        }
        if (t2 - t1 >= 3000)
        {
             addenemyPlane();// 每3秒添加一个敌人
            t1 = t2;
        }
    }

    SDL_DestroyRenderer(rr);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void planeMove()
{
    char command = getch();
    switch (command)
    {
    case 72:
    case 'W':
    case 'w':
        playerPlane.y = playerPlane.y - 20;
        if (playerPlane.y == 0)
        {
            playerPlane.y = 0;
        }
        break;
    case 80:
    case 'S':
    case 's':
        playerPlane.y = playerPlane.y + 20;
        if (playerPlane.y > 700)
        {
            playerPlane.y = 700;
        }
        break;
    case 75:
    case 'A':
    case 'a':
        playerPlane.x = playerPlane.x - 20;
        if (playerPlane.x < 0)
        {
            playerPlane.x = 0;
        }
        break;
    case 77:
    case 'D':
    case 'd':
        playerPlane.x = playerPlane.x + 20;
        if (playerPlane.x > 500)
        {
            playerPlane.x = 500;
        }
        break;
    case 32:
        shoot();
        break;
        // we can add new command to make it have more fearture
    }
}
void addenemyPlane()
{
    srand(time(NULL));
    int x_random = rand() % 501;
    struct enemy *newplane = (struct enemy *)malloc(sizeof(struct enemy *));
    newplane->x = 170; // we need to make it random
    newplane->y = 200;
    newplane->next = enemyPlane->next;
    enemyPlane->next = newplane;
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
    new_bullet->x = playerPlane.x ;
    new_bullet->y = playerPlane.y - 20;
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
        if (bullet_head->next->y < -50)
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
            if ((bullet_head->next->x >= tmpEnemy->next->x) && (bullet_head->next->x <= tmpEnemy->next->x + 80) && (bullet_head->next->y <= tmpEnemy->next->y + 100))
            {
                // load boom
                delete_enemy = tmpEnemy->next;
                tmpEnemy->next = delete_enemy->next;
                free(delete_enemy);
                delete_enemy = NULL;
                delete_bullet = bullet_head->next;
                bullet_head->next = delete_bullet->next;
                free(delete_bullet);
                delete_bullet = NULL;
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
void backMove()
{
}
void check_hit()
{
    struct enemy *tempEnemy = enemyPlane->next;
    while (tempEnemy)
    {
        if (playerPlane.x < tempEnemy->x + 80 && playerPlane.x + 80 > tempEnemy->x && playerPlane.y < tempEnemy->y + 100 && playerPlane.y + 100 > tempEnemy->y)
        {
            playerPlane.still_live = false;
            break;
        }
        tempEnemy = tempEnemy->next;
    }
}
void gameInit()
{
    // init plane
    playerPlane.x = 170;
    playerPlane.y = 500;
    playerPlane.still_live = true;
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
    SDL_Surface *background_surf = SDL_LoadBMP("./image/background.bmp");
    SDL_Surface *myp_surf = SDL_LoadBMP("./image/myplane.bmp");
    SDL_Surface *enp_surf = SDL_LoadBMP("./image/enemy.bmp");
    SDL_Texture *back_te = SDL_CreateTextureFromSurface(rr, background_surf);
    SDL_Texture *mp_te = SDL_CreateTextureFromSurface(rr, myp_surf);
    SDL_Texture *en_te = SDL_CreateTextureFromSurface(rr, enp_surf);
    
    SDL_SetTextureBlendMode(mp_te, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(en_te, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(myp_surf);
    SDL_FreeSurface(enp_surf);
    SDL_FreeSurface(background_surf);

    SDL_RenderCopy(rr, back_te, NULL, NULL);
    // if playPlane is alive,draw picture
    if (playerPlane.still_live)
    {
        SDL_Rect myplane_rect = {playerPlane.x, playerPlane.y, 50, 50};
        SDL_RenderCopy(rr, mp_te, NULL, &myplane_rect);
    }
    else // draw game over
    {
        SDL_DestroyTexture(mp_te);
        SDL_DestroyTexture(en_te);
        SDL_DestroyTexture(back_te);
        // still no draw gameover
    }
    // draw enemy
    struct enemy *tempPlane = enemyPlane->next;
    while (tempPlane)
    {
        // draw picture
        SDL_Rect enplane_rect = {tempPlane->x, tempPlane->y, 50, 50};
        SDL_RenderCopy(rr, en_te, NULL, &enplane_rect);
        tempPlane = tempPlane->next;
    }

    // draw bullet
    struct bullet *playerBullet = playerPlane.my_bullet->next;
    while (playerBullet)
    {
        // draw picture

        playerBullet = playerBullet->next;
    }
    // to end drawing
    SDL_RenderPresent(rr);
}