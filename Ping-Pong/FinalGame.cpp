#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int bx=80/2,by=20/2,vx=-1,vy=-1,p1t=8,p1b=12,p2t=8,p2b=12;
//bx=ball x-pos, by=ball y-pos
//vx=velocity in x direction, vy=velocity in y direction
//pt=paddle top, pb=paddle bottom.

void gotoxy(short x,short y)	//----------------------------------To Move the cursor to Desired coordinates.
{
	COORD pos= {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void drawboard()	//--------------------------------------Draw the Board (Background).
{
	cout<<"--------------------------------------------------------------------------------";
	gotoxy(0,20);
	cout<<"--------------------------------------------------------------------------------";
	cout<<" w = P1 MoveUp   s = P1 MoveDown   o = P2 MoveUp   l = P2 MoveDown    q = Quit";
}

void drawpaddle()	//------------------------------------Draw the Paddles on both sides.
{
	for(int i=0;i<5;i++)
	{
		gotoxy(0,p1t+i);
		cout<<"||";
	}
	for(int i=0;i<5;i++)
	{
		gotoxy(78,p2t+i);
		cout<<"||";
	}
}

void drawball()	//------------------------------------Draw Ball, Move ball, Decide Winner
{
	if((by+vy)==0||(by+vy)==20)	//If Ball Collide top or bottom, than reverse the Direction.
	{
		vy=vy*-1;
	}
	if((bx+vx)==1)	//If Ball Collides to left paddle, than reverse the direction. else Player 2 wins
	{
		if((by+vy)>=p1t-1&&(by+vy)<=p1b+1)
		{
			vx=vx*-1;
		}
		else
		{
			gotoxy(0,23);
			cout<<"Player 2 wins. Press q to quit, r to restart.";
			char ch;
			pause: //---------------------------Pause, quit or restart game
			ch=getch();
			if(ch=='q')
			{exit(0);}
			else if(ch=='r')
			{
				void restart();
				restart();
			}
			else
			{goto pause;}
		}
	}
	if((bx+vx)==78)	//If Ball Collides to right paddle, than reverse the direction. else Player 2 wins
	{
		if((by+vy)>=p2t-1&&(by+vy)<=p2b+1)
		{
			vx=vx*-1;
		}
		else
		{
			gotoxy(0,23);
			cout<<"Player 1 wins. Press q to quit, r to restart.";
			goto pause;
		}
	}
	gotoxy(bx,by);	//To remove the Ball from previous location.
	cout<<" ";			//Remove previous ball
	bx=bx+vx;				//change x coordinates.
	by=by+vy;				//change y coordinates.
	gotoxy(bx,by);	//To Move the Ball to new location.
	cout<<"0";			//To Print the Ball.
}

void movepaddle()	//-------------------------------To Move Paddle Up or Down.
{
	char ch='k';
	Sleep(100);
	if (kbhit())
    {
        ch = getch();
    }
	drawball();
	
	if(ch=='w'&&p1t>1)	//Move Paddle 1 up
	{
		gotoxy(0,p1b);
		cout<<"  ";
		p1t--;
		p1b--;
		drawpaddle();
	}
	if(ch=='o'&&p2t>1)	// Move Paddle 2 up
	{
		gotoxy(78,p2b);
		cout<<"  ";
		p2t--;
		p2b--;
		drawpaddle();
	}
	
	
	if(ch=='s'&&p1b<19)	//Move Paddle 1 Down
	{
		gotoxy(0,p1t);
		cout<<"  ";
		p1t++;
		p1b++;
		drawpaddle();
	}
	
	if(ch=='l'&&p2b<19)	// Move paddle 2 down
	{
		gotoxy(78,p2t);
		cout<<"  ";
		p2t++;
		p2b++;
		drawpaddle();
	}
	
	
	if(ch=='q')		// Quit Game in Between the match.
	{
		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		exit(0);
	}
	else
	{
		movepaddle();
	}
}

main()
{
	drawboard();
	drawpaddle();
	drawball();
	movepaddle();
	getch();
}

void restart()	//----------------------------------To reset all variables and Restart the game.
{
	system("cls");
	bx=80/2;
	by=20/2;
	vx=-1;
	vy=-1;
	p1t=8;
	p1b=12;
	p2t=8;
	p2b=12;
	main();
}
