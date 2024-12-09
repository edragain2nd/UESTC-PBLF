#include <SDL2/SDL.h>
#include <stdbool.h>
#include <conio.h>

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
void update()
{
    enemyMove();
    bulletMove();
    backMove();
}
int main()
{// init graph
    gameInit();
    while (true)
    {
        if(kbhit())
        {
            planeMove;
        }
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
struct enemy* newplane=(struct enemy*)malloc(sizeof(struct enemy*));
newplane->x=500;//we need to make it random
newplane->y=0;
newplane->next=enemyPlane->next;
enemyPlane->next=newplane; 
}
