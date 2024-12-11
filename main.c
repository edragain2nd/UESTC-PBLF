#include <SDL2/SDL.h>
#include <stdbool.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct bullet
{
    int x;
    int y;
    struct bullet* next;
};
struct plane
{
    int x;
    int y;
    bool still_live;
    int lives;
    int hit_count;
    struct  bullet* my_bullet;
};
struct enemy
{
   int x;
    int y;
    struct  enemy* next;
};
struct plane playerPlane;
struct enemy* enemyPlane;//head node of enemy
void gameInit()
{   //load image

    //init plane
    playerPlane.x=700;
    playerPlane.y=300;
    playerPlane.still_live=true;
    playerPlane.hit_count=0;
    //init bullet
    playerPlane.my_bullet=(struct bullet*)malloc(sizeof(struct bullet));
    playerPlane.my_bullet->next=NULL;
    //init enemy
    enemyPlane=(struct enemy *)malloc(sizeof(struct enemy));
    enemyPlane->next=NULL;
    //other things to load

}
void gameDraw()
{
    // start to draw background photo
    
    //if playPlane is alive,draw picture
    if (playerPlane.still_live)
    {
    }
    else//draw game over
    {

    }
    //draw enemy
    struct enemy* tempPlane=enemyPlane->next;
    while(tempPlane)
    {
        //draw picture

        tempPlane=tempPlane->next;
    }
    //draw bullet
    struct bullet* playerBullet=playerPlane.my_bullet->next;
    while (playerBullet)
    {
        //draw picture



        playerBullet=playerBullet->next;
    }
    //to end drawing

}
void enemyMove();
void bulletMove();
void backMove();
void planeMove();
void shoot();
void update()
{
    enemyMove();
    bulletMove();
    backMove();
}
void check_hit();

int main(int args, char *argv[])
{ // init graph
    gameInit();
    while (true)
    {
        if(kbhit())
        {
            planeMove();
        }
        update();
        check_hit();
        gameDraw();
        //another need to write
    }
    
    return 0;
}

void planeMove()
{
    char command=getch();
    switch (command)
    {
    case 72:
    case 'W':
    case 'w':
        playerPlane.y=playerPlane.y-20;
        if(playerPlane.y==0)
        {
            playerPlane.y=0;
        }
        break;
    case 80:
    case 'S':
    case 's':
    playerPlane.y=playerPlane.y+20;
    if(playerPlane.y>700)
    {
        playerPlane.y=700;
    }
    break;
    case 75:
    case 'A':
    case 'a':
    playerPlane.x=playerPlane.x-20;
    if(playerPlane.x<0)
    {
        playerPlane.x=0;
    }
    break;
    case 77:
    case 'D':
    case 'd':
    playerPlane.x=playerPlane.x+20;
    if(playerPlane.x>500)
    {
playerPlane.x=500;
    }
    break;
    case 32:
    shoot();
    break;
    //we can add new command to make it have more fearture
    }
}
void addenemyPlane()
{
srand(time(NULL));
int x_random = rand()%501;
struct enemy* newplane=(struct enemy*)malloc(sizeof(struct enemy*));
newplane->x=500;//we need to make it random
newplane->y=0;
newplane->next=enemyPlane->next;
enemyPlane->next=newplane; 
}
void enemyMove(){
    struct enemy* temp_enemyPlane=enemyPlane;
    struct enemy* delete_enemyPlane;
    while(temp_enemyPlane->next!=NULL)
    {
        temp_enemyPlane->next->y+=rand()%10;
        if(temp_enemyPlane->next->y>=800)
        {
            delete_enemyPlane=temp_enemyPlane->next;
            temp_enemyPlane->next=delete_enemyPlane->next;
            free(delete_enemyPlane);
            delete_enemyPlane=NULL;
            continue;
        }
        temp_enemyPlane=temp_enemyPlane->next;
    }
}
void shoot()
{
    struct bullet* new_bullet=(struct bullet *)malloc(sizeof(struct bullet*));
    new_bullet->x=playerPlane.x+30;
    new_bullet->y=playerPlane.y-20;
    new_bullet->next=playerPlane.my_bullet->next;
    playerPlane.my_bullet->next=new_bullet;
}
void bulletMove()
{
    struct bullet* bullet_head=playerPlane.my_bullet;
    struct bullet* delete_bullet;
    while(bullet_head->next!=NULL)
    {
        bullet_head->next->y-=10;
        if(bullet_head->next->y<-50)
        {
            delete_bullet=bullet_head->next;
            bullet_head->next=delete_bullet->next;
            free(delete_bullet);
            delete_bullet=NULL;
            continue;
        }
    struct enemy* tmpEnemy=enemyPlane;
    struct enemy* delete_enemy;
    while(tmpEnemy->next!=NULL)
    {
        if((bullet_head->next->x>=tmpEnemy->next->x)&&(bullet_head->next->x<=tmpEnemy->next->x+80)&&(bullet_head->next->y<=tmpEnemy->next->y+100))
        {
            //load boom 
            delete_enemy=tmpEnemy->next;
            tmpEnemy->next=delete_enemy->next;
            free(delete_enemy);
            delete_enemy=NULL;
            delete_bullet=bullet_head->next;
            bullet_head->next=delete_bullet->next;
            free(delete_bullet);
            delete_bullet=NULL;
        }
        if(tmpEnemy->next==NULL)
        {break;}
        tmpEnemy=tmpEnemy->next;
    }
    if(bullet_head->next==NULL)
    {
        break;
    }
    bullet_head=bullet_head->next;
}}
void backMove()
{}
void check_hit(){ 
    struct enemy* tempEnemy = enemyPlane->next;
    while(tempEnemy){
        if(playerPlane.x < tempEnemy->x + 80 && playerPlane.x + 80 > tempEnemy->x && playerPlane.y < tempEnemy->y + 100 && playerPlane.y + 100 > tempEnemy->y){
            playerPlane.hit_count++;        
            if(playerPlane.hit_count>=3){
                playerPlane.still_live = false;
                printf("Game Over!小趴菜");
                return;
            }
        }
    }
}
