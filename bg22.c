/*
ball game    v1.2
...nithin   agnithin@yahoo.com
aim of the gam is to stop the ball from hitting the right wall
by moving the box. 10 pts r given 4 stopping it once.
speed adds as the score increases by 100.
*/

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>


int midx, midy, x, y, sx, sy, by, scr, spd, ch=3;
int r=20, i, d=0;

/*
midx,midy = mid of screen
x,y       = coordinates of ball  (initial pos can be changed)
sx,sy     = direction for ball to mov (1 for +ve, 0 for -ve)
by        = location of box
scr       = score
spd       = speed
ch        = menu choice
r         = radius of ball
i         = for internel loops
d         = debugging mode on / off
*/

void load();
void menu();
void box();
void gamover();
void credit();
/*/////////////////////////////ball*/
void ball()
{  x=y=22;sx=sy=1;scr=0;spd=2;
   setbkcolor(8);
   cleardevice();
   setcolor(1);                                  /*color 4 border*/
   rectangle(0,0,getmaxx(),getmaxy() );          /* border*/

   while(1)
   {
	if(x>(midx*2-3)-r)
	{ 	sx=0;
		/*scr=scr-10;*/
		gamover();                         /*conditions for*/
		sound(100);                        /* ball to move*/
	}
	if(x<(r+3))
	{	sx=1;   sound(100);}

	if(y>(midy*2-3)-r)
	{	sy=0;   sound(100);}
	if(y<(r+3))
	{	sy=1;   sound(100);}

	if(x==getmaxx()-45-r && y>by-20 && y<(by+80))
	{
		sx=0;
		scr=scr+10;
		sound(500);
		if(scr%100==0)                     /*if score inc by 100*/
		{
			spd++;  		   /*inc speed*/
			sound(600);
			delay(100);
			nosound();
		}
	}

	if(sx==0)  x=x-spd;                      /*ball*/
	else  x=x+spd;                           /*movment*/

	if(sy==0)  y=y-spd;                      /*ball*/
	else y=y+spd;                            /*movement*/

	setcolor(1);                             /*ball outline color*/
	setfillstyle( SOLID_FILL, 3 );           /*ball color*/
	fillellipse(x, y, r, r);                 /*draw ball*/


	for(i=0;i<12;i=i+2)
		arc(x, y, 230+i*6, 40-i*6, r-i);    /*for 3d touch*/

	/*  settextstyle(4, HORIZ_DIR, 0);*/        /*4 writing inside the ball*/
	/*outtextxy(x-10,y-20,"N");*/
	nosound();
	gotoxy(5,2);
	printf("* BALL GAME v1.2 *");
	printf("                                   SCORE:%3d",scr);                 /*disp score*/
	printf("    SPEED:%2d",spd-1);            /*and speed*/
	if(d==1)
	{
		gotoxy(getmaxx()-60,1);
		printf("debugging mode ");
		printf("\n\n#box:\nby=%d  ",by);
		printf("\n\n#ball:");
		printf("\nx=%d  \ny=%d  ",x,y);
		printf("\n\ngetmaxx = %d",getmaxx());
		printf("\ngetmaxy = %d",getmaxy());
	}

	setcolor(7);
	if(kbhit())                             /*if i/p, mov box*/
		box();
	else                                   /*if no i/p disp in same pos*/
		rectangle(getmaxx()-40,by,getmaxx()-30,by+60);

	delay(10);
	setfillstyle( SOLID_FILL, 8 );                /*clear ball & box*/
	setcolor(8);
	fillellipse(x, y, r, r);
	rectangle(getmaxx()-40,by,getmaxx()-30,by+60);
   }
}
/*///////////////////////////////box*/
void box()
{
   switch(getch())
   {
      case 0x48:                         /*up key  */
	   if(by<5)
		break;
	   else
		by=by-12;                 /*can be inc further to mov faster*/
		break;

      case 0x50:                         /*down key*/
	   if(by>getmaxy()-65)
		break;
	   else
		by=by+12;                 /*can be inc further to mov faster*/
	   break;
      /*case 0x4b://left
      case 0x4d://right  */
      case 'p':
	       rectangle(getmaxx()-40,by,getmaxx()-30,by+60); /*disp box*/
	       for(i=0;i<midx;i=i+4)
	       rectangle(midx-i-50,midy-i-10,midx+i+50,midy+i+10);
	       rectangle(midx-50,midy-10,midx+50,midy+10);
	       outtextxy(midx-35,midy-11,"PAUSED");
	       getch();
	       cleardevice();
	       setcolor(1);
	       rectangle(0,0,getmaxx(),getmaxy() );
	       break;
      case 'd':
	       if(d==0)
		       d=1;
	       else
	       {
		       d=0;
		       cleardevice();
		       setcolor(1);
		       rectangle(0,0,getmaxx(),getmaxy() );
	       }
	       break;
      case 0x1b:                         /*esc key */
	       menu();

      }
   rectangle(getmaxx()-40,by,getmaxx()-30,by+60); /*disp box*/

   return;
}
/*////////////////////////////////load screen*/
void load()
{
   setcolor(3);
   rectangle(1,1,getmaxx()-1,getmaxy()-1 );     /*border*/
   settextstyle(8, HORIZ_DIR, 9);
   outtextxy(30,20,"BALL GAME");

   gotoxy(37,18);
   printf("LOADING");
   rectangle(midx-210,midy+30,midx+201,midy+50);
   for(i=0;i<=50;i++)                          /*loading disp loop */
   {
	gotoxy(14+1+i,17+1);
	printf("Ý");
	/*sound(100+10*i);*/
	delay(100);
	gotoxy(33,17);
	printf("%3d % Complete",i*2);
   }
   delay(200);
}
/*///////////////////////////////menu */
void menu()
{
while(1)                                      /*menu */
   {
	cleardevice();
	rectangle(1,1,getmaxx()-1,getmaxy()-1 );  /*border*/
	setcolor(3);
	settextstyle(8, HORIZ_DIR, 9);
	outtextxy(30,20,"BALL GAME");
	settextstyle(2, HORIZ_DIR, 7);
	outtextxy(midx-27,midy+10,"START");
	outtextxy(midx-38,midy+50,"CREDITS");
	outtextxy(midx-19,midy+90,"EXIT");

	ch=ch%2;
	rectangle(midx-50,midy+50-ch*40,midx+50,midy+75-ch*40); /*selection*/
	switch(getch())
	{
		case 72:  ch++;  break;                   /*up key*/
		case 80:  ch--;  break;                   /*down key*/
		case 13:                                  /*enter key*/
			if(ch==1)
				ball();
			else if(ch==0)
				credit();
			else if(ch==-1)
				exit(1);
	}
   }
}
/*////////////////////////////gamover */
void gamover()
{
	setcolor(3);
	for(i=0;i<135;i++)
	{
		circle(midx,midy,i*3);
		delay(15);
	}
	setfillstyle(SOLID_FILL,7);
	for(i=0;i<100;i++)
	{
		fillellipse(midx,midy-20,3*i,20);
		delay(15);
	}
	setcolor(1);
	settextstyle(4, HORIZ_DIR, 0);
	outtextxy(midx-80,midy-40,"GAME OVER");
	delay(400);
	getch();
	menu();
}
/*///////////////////////credits */
void credit()
{
	setcolor(7);
	randomize();
	for(i=0;i<2*midx;i++)                  /*random lines*/
	{
		rectangle(1,1,rand()%100+i,midy*2);
		delay(10);
	}

	for(i=0;i<2*midx;i++)                 /*clrs space for writing*/
	{
		 circle(midx*2-i,midy*2-90,8);
	   /*	rectangle(midx*2,midy*2-100,midx*2-i,midy*2-80);*/
		delay(8);
	}
	setcolor(1);
	settextstyle(3, HORIZ_DIR, 3);
	outtextxy(20,midy*2-108,"created by,");
	setcolor(7);
	for(i=0;i<2*midx;i++)
	{
	       circle(i,midy*2-60,8);
	       delay(8);
	}
	setcolor(1);
	settextstyle(3, HORIZ_DIR, 3);
	outtextxy(midx*2-100,midy*2-78,"...nithin");
	delay(200);
	settextstyle(4, HORIZ_DIR, 0);

	setfillstyle(SOLID_FILL,7);
	for(i=0;i<100;i++)
	{
		fillellipse(midx,midy+25,2*i,20);
		delay(15);
	}
	outtextxy(midx-133,midy,"agnithin@yahoo.com");
	getch();
	setcolor(8);
	for(i=0;i<2*midx;i++)                   /*clears screen*/
	{
		rectangle(1,1,i,midy*2);
		delay(8);
	}
	setcolor(3);
	return;
}

/*//////////////////////main()*/
int main(void)
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "c:\\tc\\bgi");   /*change this to ur tc dir*/

   midx = getmaxx() / 2;
   midy = getmaxy() / 2;
   by=getmaxy()-70;
   setbkcolor(8);
   load();                           /*disp loading screen*/
   menu();
   ball();                           /*main game          */
   closegraph();

   return 0;
}

