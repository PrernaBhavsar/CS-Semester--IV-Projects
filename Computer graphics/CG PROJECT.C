#include<stdio.h>
#include<graphics.h>


float calculate(int n, int r);
float power(float a, int b);
int fact(int a);
void drawman();
void bounce();
void bound(float x, float y, int fillcolor, int boundcolor);

float x[100], ys[100], yinp, y[100], xn, yn, u, c, ytemp, yincr;
int gd=DETECT, gm, r, i, k, score=3, valid, n=3;
float slope1, slope2;
void main()
{
    initgraph(&gd,&gm," ");
    printf("\n\n\nINITIAL NO OF LIVES = %d\n",score);
    printf("\nPress any key to continue -->");
    getch();
    cleardevice();
    for(k=1;k<=5;k++)
    {
	x[0]=(float)100;
	y[0]=(float)350;
	clrscr();
	cleardevice();
	drawman();
	setcolor(BLUE);
	circle(100,350,20);
	bound(100,350,BLUE,BLUE);
	printf("\nEnter three points for the throw.\n");
	setlinestyle(1,0,1);
	setcolor(RED);
	for(i=1;i<=n;i++)
	    {
		scanf("%f%f",&x[i],&y[i]);
		//y[i]=getmaxy()-yinp;
		ys[i]=getmaxy()-y[i];
		line(x[i-1],y[i-1],x[i],y[i]);
	    }

	getch();
	valid = 1;
	for(i=1;i<=n;i++)
	{
	   if(i!=n)
	   {    //Once it goes below the reference, it cannot go above later
		if(y[i]>y[i-1] && y[i+1]<=y[i])
		{
		   valid = 0;
		   break;
		}
		//Provided the slope is not Undefined
		if(!(x[i+1]==x[i] || x[i]==x[i-1]))
		{ //If slope of first line is <1, the slope of the next line also
		  //has to be less than one
		  //You cannot have something like _/ as your throw style
		  slope1= (ys[i]-ys[i-1])/(x[i]-x[i-1]);
		  slope2= (ys[i+1]-ys[i])/(x[i+1]-x[i]);
		  if((slope1>=0 && slope1<=1) && (slope2>=1))
		  {
		    valid=0;
		    break;
		  }
		}
	    }
	    //X should always increase
	   if(x[i]<x[i-1])
	   {
	      valid=0;
	      break;
	   }
	  else if(x[i]==x[i-1]  && ys[i]>=ys[i-1])
	   {
	       valid=0;
	       break;
	   }
	}
	if(valid==0)
	{
	    printf("\nINVALID TURN! YOU LOSE A LIFE :(");
	    score = score -1;
	    printf("\n\nNO OF LIVES LEFT: %d", score);
	    getch();
	    if(score==0)
	    break;
	    continue;
	}

	for(u=0.001;u<1;u=u+0.001)
	  {
	       cleardevice();
	       xn=0;
	       yn=0;
	       for(r=0;r<=n;r++)
	       {
		 c = calculate(n,r);
		 xn = xn + c*power(1-u,n-r)*power(u,r)*x[r];
		 yn = yn + c*power(1-u,n-r)*power(u,r)*y[r];
	       }
	       drawman();
	       setcolor(BLUE);
	       circle(xn,yn,20);
	       bound(xn,yn,BLUE,BLUE);
	       delay(1);
	}

	x[0]=xn;
	y[0]=yn;
	ytemp=yn;
	yincr = (getmaxy()-ytemp)/3;
	for(i=1;i<=5;i++)
	{
	    x[i]=xn;
	    if(i%2==0)
	    {
		y[i]=ytemp+yincr;
		ytemp=y[i];
	    }
	    else
	    {
		y[i]=getmaxy()-20;
	    }
	}
	for(i=1;i<=5;i++)
	{
	    if(i%2==0)
	    {
		for(u=y[i-1];u>=y[i];u=u-1.1)
		    {
			bounce();
		    }
	    }
	    else
	    {
		for(u=y[i-1];u<=y[i];u=u+1.1)
		    {
			bounce();
		    }
	    }
	}
	for(u=xn;u<=xn+30;u=u+1)
	{
	    cleardevice();
	    drawman();
	    setcolor(BLUE);
	    circle(u,getmaxy()-20,20);
	    bound(xn,u,BLUE,BLUE);
	    delay(30);
	}
	printf("\n%f %f",xn,yn);
	if((yn>=0 && yn<=100) && (xn>=520 && xn<=580))
	{
	score=score+1;
	printf("\nGOAL!!");
	printf("\n\nNO OF LIVES LEFT: %d",score);
	}
	else
	{
	score=score-1;
	printf("\nYOU MISSED THE BASKET!");
	printf("\n\nNO OF LIVES LEFT: %d",score);
	}
	getch();
	clrscr();
	cleardevice();
    }
    clrscr();
    cleardevice();
    if(score==0)
    {
     printf("\n\n\nGAME OVER!!");
    }
    else
    {
     printf("\n\n\nWell played!\n\n");
     printf("NO OF LIVES: %d", score);
    }
    getch();
    closegraph();
}

int fact(int a)
{
     int f=1, i;
     for(i=1;i<=a;i++)
	{
	    f = f*i;
	}
     return f;
}

float calculate(int n, int r)
{
    return ((float)fact(n)/(fact(r)*fact(n-r)));
}

float power(float a, int b)
{
     if(b==0)
	return 1;

     else
	return (a*power(a,b-1));
}

void drawman()
{
    int edge[100]= {640-130,120,640,120,640,130,640-130,130};
    int basket[100] = {640-130,130,640-50,130,640-60,180,640-120,180};
    setcolor(WHITE);
    circle(50,350,15);
    line(50,365,50,430);
    line(50,390,85,360);
    line(50,390,15,360);
    line(50,430,90,480);
    line(50,430,10,480);
    setfillpattern("SOLID_FILL",BROWN);
    setcolor(BROWN);
    fillpoly(4,edge);
    setfillpattern("HATCH_FILL",RED);
    setcolor(RED);
    fillpoly(4,basket);
}

void bounce()
{
    cleardevice();
    drawman();
    setcolor(BLUE);
    circle(xn,u,20);
    bound(xn,u,BLUE,BLUE);
    delay(1);
}
void bound(float x, float y, int fillcolor, int boundcolor)
{
    if(getpixel(x,y)!=fillcolor && getpixel(x,y)!=boundcolor)
    {
     putpixel(x,y,fillcolor);
     bound(x+1,y,fillcolor,boundcolor);
     bound(x-1,y,fillcolor,boundcolor);
     bound(x,y+1,fillcolor,boundcolor);
     bound(x,y-1,fillcolor,boundcolor);

    }


}
