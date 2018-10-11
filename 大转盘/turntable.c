
#include<stdio.h>
#define South 3
#define West 2
#define North 1
#define East 0

typedef int car[2];  //车辆信息 car[0] 出发地 car[1] 目的地

car num[a];  //车辆信息 num[0][0]车辆数

car fork[4][a]; //道口车辆信息  fork[][0][0]车辆数   E,N,W,S;
int cross[3][2];//道口左右道路信息  cross[][0]进路口 cross[][1]出路口
void main()
{

    delieve(num,fork);
    cobegin
    light(fork[0],East);
    light(fork[1],North);
    light(fork[2],West);
    light(fork[3],South);
    coend
}
int light(car* forkcar,int** road,int dire)
{
    for(int i=1;i<=forkcar[0][0];i++)
    {
        if(forkcar[i][1]==dire)
        p(road[dire][1],forkcar[i][1]);
        else
        p(road[(dire+1)%4][1]);
        v(road[0]);
    return 0;
}
int p(int road,car in_car)
{
    road--;

}
