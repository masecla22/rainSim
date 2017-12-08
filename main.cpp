#include <iostream>
#include <cstring>
#include <graphics.h>
#include <cmath>
#include <ctime>


using namespace std;



const int drops = 190;
const int speedFactorRange[3] = {1,5};
const int posXRange[3] = {1,900};
const int breakingZoneRange[3] = {350,500};
const int circleWidthRange[3]= {20,30};
const int circleInit=1;
const int circleGrowthRange[3]= {1,1};
const int circleChance=100; ///How likely is it that the drop will break into a circle?
const int breaksOnE=false;
const int timeBetweenFrames=20;
const char keyBindToStop='F';
const int timeToHoldPressed=3000;
const int style=1; /// 0 = rain 1 = snow
const int flakesRandom=false;

int random(int min, int max)
{
    if(min==max)
        return min;
    static bool first = true;
    if ( first )
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % (max - min);
}
int layer=0;
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
            {
            isCircle=1;
                layer++;
            }
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
int draws(droplet rains[1000],int i,int style)
{
    if(rains[i].isCircle==0)
    {
        if(style==0)
        {
        line(rains[i].posX,rains[i].pos,rains[i].posX,rains[i].pos+15);

        }
        if(style==1)
        {
            setcolor(9);
           line(rains[i].posX,rains[i].pos,rains[i].posX,rains[i].pos+15);
           line(rains[i].posX-9,rains[i].pos,rains[i].posX+9,rains[i].pos+15);
           line(rains[i].posX+9,rains[i].pos,rains[i].posX-9,rains[i].pos+15);
        }
    }
    else
    {
        if(style==0)
        ellipse(rains[i].posX,rains[i].pos,360,360,rains[i].CircleWidth,rains[i].CircleWidth/2);
        if(style==1)
        {
        rectangle(0,600,layer,900);
        }
    }
}
int nextFrame(droplet rains[1000],int inits)
{
    cleardevice();
    for(int i=0; i<inits; i++)
    {
        rains[i].nextStep();
        draws(rains,i,style);
    }
}
int main()
{
    char keyBindToStop1;
    keyBindToStop1=tolower(keyBindToStop);
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
        Sleep(timeBetweenFrames);
        if(GetAsyncKeyState(int(keyBindToStop1)-32)!=0)
        {
            Sleep(timeToHoldPressed);
            if(GetAsyncKeyState(int(keyBindToStop1)-32)!=0)
                break;
        }
    }
    getch();
    closegraph();
    return 0;
}

