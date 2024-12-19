# UESTC-PBLF
## 项目名称
 飞机大战
 ## 项目简介
 
 飞机大战是一款经典的游戏，本项目利用SDL图形库和C语言进行开发。通过这个项目，可以学习到SDL图形库的使用方法和C语言的基本语法。比如，利用结构体存储子弹和飞机等信息，利用链表的增删查改实添加敌方飞机，飞机移动，存储子弹等操作。在实现经典功能的基础上，本项目还有一些创新点。比如增加了分数统计，升级装备，增加了音效等。

 ## 项目实现
 飞机大战的实现主要分为以下几个部分：
 -定义飞机大战所需结构体并全局定义结构体成员：
 ```c
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

```
- 实现飞机大战的初始化函数：
```c
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
```
- 实现飞机大战的主循环：
```c
int main(int args, char *argv[])
{ // init graph
    gameInit();
    while (true)
    {
        if(kbhit())
        {
            planeMove();
        }
        //another need to write
    }
    
    return 0;
}
```
- 实现飞机大战的绘制函数：
```c
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

```
- 实现飞机大战的移动函数：
```c
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

```
- 实现飞机大战的射击函数：
```c
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
```

-实现飞机大战的敌机移动函数：
```c
void addenemyPlane()
{
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
```

-实现飞机大战的升级装备和分数统计函数：

-实现飞机大战的音效函数：

 ## 分工

 基础： 翁博文
 SDL美工图形：
 拓展内容：
 文档：
 
