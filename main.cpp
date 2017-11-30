#include <iostream>
#include <cstring>
#include <graphics.h>
#include <cmath>
#include <ctime>

using namespace std;

const int drops = 170;
const int speedFactorRange[3] = {1,5};
const int posXRange[3] = {1,900};
const int breakingZoneRange[3] = {350,500};
const int circleWidthRange[3]= {1,20};
const int circleInit=1;
const int circleGrowthRange[3]= {1,5};
const int circleChance=100; ///How likely is it that the drop will break into a circle?

int random(int min, int max)
{
    static bool first = true;
    if ( first )
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % (max - min);
}
struct droplet
{
    int pos,velocity,posX,isCircle,CircleWidth=0,speedFactor;
    int init()
    {
        speedFactor=random(speedFactorRange[0],speedFactorRange[1]);
        isCircle=0;
        pos=0;
        velocity=1;
        posX=random(posXRange[0],posXRange[1]);
    }
    int nextStep()
    {
        if(isCircle==0)
        {
            pos+=velocity;
            velocity=((pos+20)/20)+speedFactor;
        }
        if(pos>random(breakingZoneRange[0],breakingZoneRange[1]))
        {
            if(random(1,100)<=circleChance)
            isCircle=1;
            else
                CircleWidth=1000;
            CircleWidth+=random(circleGrowthRange[0],circleGrowthRange[1]);
            if(CircleWidth>random(circleWidthRange[0],circleWidthRange[1]))
            {
                isCircle=0;
                CircleWidth=circleInit;
                init();
            }
        }

    }
};
int draws(droplet rains[1000],int i)
{
    if(rains[i].isCircle==0)
        line(rains[i].posX,rains[i].pos,rains[i].posX,rains[i].pos+15);
    else
    {
        ellipse(rains[i].posX,rains[i].pos,360,360,rains[i].CircleWidth,rains[i].CircleWidth/2);
    }
}
int nextFrame(droplet rains[1000],int inits)
{
    cleardevice();
    for(int i=0; i<inits; i++)
    {
        rains[i].nextStep();
        draws(rains,i);
    }
}
int main()
{

    int gd=DETECT,gm;
    int x=320,y=240,radius;
    // initgraph(&gd, &gm, "C:\\TC\\BGI");
    initwindow(640, 480,"Rain Simulator -by masecla22");
    droplet rains[200];
    int i=0;
    setcolor(3);
    int inits=3;
    while(true)
    {
        if(i<drops&&random(1,20)>15)
        {
            inits++;
            i++;
            //cout<<inits<<"  "<<rains[random(1,(inits-1))].speedFactor<<endl;
            rains[random(1,drops)].init();
        }
        nextFrame(rains,inits);
        Sleep(100);
    }
    getch();
    closegraph();
    return 0;
}
