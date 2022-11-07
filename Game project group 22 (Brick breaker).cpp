#include <iostream>
#include <stdlib.h>
#include <time.h>         
#include <conio.h>
#include <string.h>                     
#include <dos.h>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


int bricks01[12][2] =  { {1,1},{1,1},{1,1},{1,1},{1,1},{1,1},
						 {1,1},{1,1},{1,1},{1,1},{1,1},{1,1} };	
						 			
int bricks02[12][2]= {   {1,1},{1,1},{1,1},{1,1},{1,1},{1,1},
						 {1,1},{1,1},{1,1},{1,1},{1,1},{1,1} };

int bricks06[12][2]=  {  {1,1},{1,1},{1,1},{1,1},{1,1},{1,1},
						 {1,1},{1,1},{1,1},{1,1},{1,1},{1,1} }; 
						 
int bricks07[12][2]=  {  {1,1},{1,1},{1,1},{1,1},{1,1},{1,1},
						 {1,1},{1,1},{1,1},{1,1},{1,1},{1,1} };
						 
														
int visibleBricks01[12]= {1,1,1,1, 1,1,1,1, 1,1,1,1};
int visibleBricks06[12]= {1,1,1,1,1,1,1, 1,1,1,1,1};

int sliderPos01[2] = {52,80};
int ballPos[2] = {51,88};
int ballPos_refresh[2] = {};

const int SCREEN_WIDTH= 176, SCREEN_HEIGHT = 54, MINX = 3, MINY = 3, MAXX = 172, MAXY = 55;
int random_position=0, startBall = 0,dir = 2, bricksLeft01 = 12,  bricksLeft03 = 12, win = 0, lose = 0;

int Level = 1;  
int sleep_value = 85; 

void gotoxy(int x, int y);
void setcurser(bool visible, DWORD size);
void drawBorder();
void drawBricks();

void clearBricks01();
void clearBricks02();
void ballHitSlider();
void ballHitBrick();
void play();
void instructions();
void reset();
void difficulty();
void level(int level_no);


int main(){
	
		do{
			if(Level==1){

			system("cls");
			setcurser(0,0);		
			reset(); 
			drawBorder();	
			level(Level);		
			
			gotoxy(73,15); cout<<"    'TTTT'";
			gotoxy(73,16); cout<<"     IIII ";
			gotoxy(73,17); cout<<".IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII.";
			gotoxy(72,18); cout<<".IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII.";
			gotoxy(71,19); cout<<".-------------------------------------.";
			gotoxy(70,20); cout<<"//||                                 ||\\\\";
			gotoxy(72,21); cout<<"||          BLOCK BREAKER          ||";
			gotoxy(72,22); cout<<"||                                 ||";
			gotoxy(72,23); cout<<"-------------------------------------";
			gotoxy(72,24); cout<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
			gotoxy(82,28); cout<<"1. Start game";
			gotoxy(82,29); cout<<"2. Instructions";
			gotoxy(82,30); cout<<"3. Quit";
			gotoxy(82,32); cout<<"Select any option: ";
			
			char op = getche();
			if( op=='1'){difficulty(); play();} 
			else if( op=='2') instructions();
			else if( op=='3') exit(0);
				
			}
			
			else{
			
			system("cls");
			setcurser(0,0);
			reset(); 
			level(Level);
			
			play();
			
			}
			
		}while(1);
	
		//play();
		//cout<<endl<<endl;
		
		return 0;
	}


void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);	
} 

void setcurser(bool visible, DWORD size){ //set bool visible = 0  - invisible , 1 - visible
	if(size == 0)
	{
		size = 20; //default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor ;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder(){
	int a=254;
	char d=char(a);
	for(int i=1;i<=177;i++)
		{
			gotoxy(i,1);cout<<d;
		}
	gotoxy(0,SCREEN_HEIGHT);cout<<"   ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		for(int i=0; i<SCREEN_HEIGHT; i++){
		 int c=219;
		gotoxy(1,i+2); cout<<char(c);
		gotoxy(SCREEN_WIDTH+1,i+2); cout<<char(c);
	}
}

void drawBricks(){
	
	for( int i=0; i<12;i++)
	{
		if( visibleBricks01[i] == 1){
			int a=219;
			gotoxy(bricks02[i][1], bricks02[i][0]);
			cout<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a);
			gotoxy(bricks01[i][1], bricks01[i][0]);
			cout<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a);
		}
	}
		for( int i=0; i<12;i++){
		if( visibleBricks06[i] == 1){
			int a=176;
			gotoxy(bricks06[i][1], bricks06[i][0]);
			cout<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a);
			gotoxy(bricks07[i][1], bricks07[i][0]);
			cout<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a);
		}
		}
}

void ballHitSlider(){
	if( ballPos[1]>=sliderPos01[1] && ballPos[1]<=sliderPos01[1]+18){
		if( ballPos[0] == sliderPos01[0]-1 ){			
			if( dir == 3 )
				dir = 2;
			else if( dir == 4)
				dir = 1;
		}
	}
}

void clearBricks01(int i){
	{	
		gotoxy(bricks01[i][1]+12,bricks01[i][0]);
		cout<<"\b\b\b\b\b\b\b\b\b\b\b\b            ";
		gotoxy(bricks02[i][1]+12,bricks02[i][0]);
		cout<<"\b\b\b\b\b\b\b\b\b\b\b\b            ";				
	}	
}

void clearBricks02(int i){
	{	
		gotoxy(bricks06[i][1]+12,bricks06[i][0]);
		cout<<"\b\b\b\b\b\b\b\b\b\b\b\b            ";
		gotoxy(bricks07[i][1]+12,bricks07[i][0]);
		cout<<"\b\b\b\b\b\b\b\b\b\b\b\b            ";				
	}	
}

void ballHitBrick(){
		
//set 01
	for(int i=0; i<12; i++){
		
	//upper 13
		//upper
		if(visibleBricks01[i]==1){
			if( ballPos[1]>=bricks01[i][1] && ballPos[1]<=bricks01[i][1]+10)
			{	if( ballPos[0] == bricks01[i][0]-1){
					if 		(dir== 3 ){dir = 2 ;}
					else if (dir== 4 ){dir = 1 ;}
					visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}
					bricksLeft01--;
			}}}
		//below
		if(visibleBricks01[i]==1){
			if( ballPos[1]>=bricks02[i][1] && ballPos[1]<=bricks02[i][1]+10)
			{	if( ballPos[0] == bricks02[i][0]+1){
					if 		(dir== 1 ){dir = 4 ;}
					else if (dir== 2 ){dir = 3 ;}
					visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}		
					bricksLeft01--;
			}}}
		
			
	//right-left edges
		//upper
		if(visibleBricks01[i]==1){
				if(ballPos[1]==bricks01[i][1]-2 && ballPos[0] == bricks01[i][0])
			{	if 		(dir== 4 ){dir = 3 ;}
				else if (dir== 1 ){dir = 2 ;}	
				visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}		
				bricksLeft01--;
			}	
			if(ballPos[1]==bricks01[i][1]+12 && ballPos[0] == bricks01[i][0])
			{	if 		(dir== 3 ){dir = 4 ;}
				else if (dir== 2 ){dir = 1 ;}	
				visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}	
				bricksLeft01--;
			}					
		}
			
		//below
		if(visibleBricks01[i]==1){
			if(ballPos[1]==bricks02[i][1]-2 && ballPos[0] == bricks02[i][0])
			{		
				if 		(dir== 4 ){dir = 3 ;}
				else if (dir== 1 ){dir = 2 ;}
			visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}	
				bricksLeft01--;
			}	
			if(ballPos[1]==bricks02[i][1]+12 && ballPos[0] == bricks02[i][0])
			{	
				if 		(dir== 3 ){dir = 4 ;}
				else if (dir== 2 ){dir = 1 ;}	
			visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}	
				bricksLeft01--;
			}					
		}

	//right-left corners
		//upper
		if(visibleBricks01[i]==1){
			if(ballPos[1]==bricks01[i][1]-2 && ballPos[0] == bricks01[i][0]-1)
			{		
				if 		(dir== 4 )
				{
					dir = 3 ;
					visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}		
					bricksLeft01--;
				}	
			}	
			if(ballPos[1]==bricks01[i][1]+12 && ballPos[0] == bricks01[i][0]-1)
			{	
				if 		(dir== 3 )
				{
					dir = 4 ;	
					visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}	
					bricksLeft01--;
				}
			}					
		}
		
		//bottom
		if(visibleBricks01[i]==1){
			if(ballPos[1]==bricks02[i][1]-2 && ballPos[0] == bricks02[i][0]+1)
			{		
				if 		(dir== 1 )
				{
				dir = 2 ;
				visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}	
				bricksLeft01--;
				}
			}	
			if(ballPos[1]==bricks02[i][1]+12 && ballPos[0] == bricks02[i][0]+1)
			{
				if 		(dir== 2 )
				{
				dir = 1 ;
				visibleBricks01[i] = 0;
						if(visibleBricks01[i] == 0)	{clearBricks01(i);	}		
				bricksLeft01--;
				}
			}				
		}	
	}

//set 3			
	for(int i=0; i<12; i++){
		
	//upper 13
		//upper
		if(visibleBricks06[i]==1){
			if( ballPos[1]>=bricks06[i][1] && ballPos[1]<=bricks06[i][1]+10)
			{
				if( ballPos[0] == bricks06[i][0]-1){
					if 		(dir== 3 ){dir = 2 ;}
					else if (dir== 4 ){dir = 1 ;}
					visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}
					bricksLeft03--;
				}
			}
		}
		//below
		if(visibleBricks06[i]==1){
			if( ballPos[1]>=bricks07[i][1] && ballPos[1]<=bricks07[i][1]+10)
			{
				if( ballPos[0] == bricks07[i][0]+1){
					if 		(dir== 1 ){dir = 4 ;}
					else if (dir== 2 ){dir = 3 ;}
					visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}		
					bricksLeft03--;
				}
			}
		}
			
	//right-left edges
		//upper
		if(visibleBricks06[i]==1){
			
			if(ballPos[1]==bricks06[i][1]-2 && ballPos[0] == bricks06[i][0])
			{		
				if 		(dir== 4 ){dir = 3 ;}
				else if (dir== 1 ){dir = 2 ;}
			visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}		
				bricksLeft03--;
			}	
			if(ballPos[1]==bricks06[i][1]+12 && ballPos[0] == bricks06[i][0])
			{
				if 		(dir== 3 ){dir = 4 ;}
				else if (dir== 2 ){dir = 1 ;}
			visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}	
				bricksLeft03--;
			}					
		}
			
		//below
		if(visibleBricks06[i]==1){
			if(ballPos[1]==bricks07[i][1]-2 && ballPos[0] == bricks07[i][0])
			{	
				if 		(dir== 4 ){dir = 3 ;}
				else if (dir== 1 ){dir = 2 ;}
			visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}	
				bricksLeft03--;
			}	
			if(ballPos[1]==bricks07[i][1]+12 && ballPos[0] == bricks07[i][0])
			{
				if 		(dir== 3 ){dir = 4 ;}
				else if (dir== 2 ){dir = 1 ;}
			visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}	
				bricksLeft03--;
			}					
		}

	//right-left corners
		//upper
		if(visibleBricks06[i]==1){
			if(ballPos[1]==bricks06[i][1]-2 && ballPos[0] == bricks06[i][0]-1)
			{		
				if 		(dir== 4 )
				{
					dir = 3 ;
					visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}		
					bricksLeft03--;
				}
			}	
			if(ballPos[1]==bricks06[i][1]+12 && ballPos[0] == bricks06[i][0]-1)
			{
				if 		(dir== 3 )
				{
					dir = 4 ;
					visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}	
					bricksLeft03--;
				}
			}					
		}
		
		//bottom
		if(visibleBricks06[i]==1){
			if(ballPos[1]==bricks07[i][1]-2 && ballPos[0] == bricks07[i][0]+1)
			{		
				if 		(dir== 1 )
				{
				dir = 2 ;
				visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}	
				bricksLeft03--;
				}
			}	
			if(ballPos[1]==bricks07[i][1]+12 && ballPos[0] == bricks07[i][0]+1)
			{	
				if 		(dir== 2 )
				{
				dir = 1 ;
				visibleBricks06[i] = 0;
						if(visibleBricks06[i] == 0)	{clearBricks02(i);	}		
				bricksLeft03--;
				}
			}				
		}	
	}
}

void play(){
	
	system("cls");
	drawBricks();
	drawBorder();
		bool refresh=0;
	    int count01=0,count02=1,count_border=0;
	    
	//random slider(with ball) position    
	srand(time(0));
	random_position=(rand()%32)*3+32;
	
	if(random_position%2==0){
		
		sliderPos01[1]=random_position;
		dir=2;
	}
	else{
		
		sliderPos01[1]=random_position-3;
		dir=1;	
	}
	
	ballPos[1]=sliderPos01[1]+8;
	 
	while(1){
		if(refresh == 1)
			{
			int count02=1;
			count02=count02++;
			}
		if(count02>count01)
			{
			gotoxy(ballPos_refresh[1]+3,ballPos_refresh[0]);
			cout<<"\b\b\b   ";
			}
		gotoxy(sliderPos01[1],sliderPos01[0]);
		int a=254,b=118;
		cout<<"<<"<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<">>";
		ballPos_refresh[1]=ballPos[1];
		ballPos_refresh[0]=ballPos[0];
		gotoxy(ballPos[1],ballPos[0]);cout<<"(@)"; 
		if(kbhit()){
			char ch = getch();
			if( ch=='d'||ch =='D'|| ch==77){
				if(sliderPos01[1]<156 && startBall==1)
					sliderPos01[1] = sliderPos01[1]+6;
			gotoxy(sliderPos01[1],sliderPos01[0]);
			cout<<"\b\b\b\b\b\b\b\b        ";
			}
			if( ch=='a'||ch=='A'||ch==75){
				if(sliderPos01[1] >2 && startBall==1)
					sliderPos01[1] =sliderPos01[1]-6;
			gotoxy(sliderPos01[1]+19,sliderPos01[0]);
			cout<<"         ";
			}
			else
			if (ch==32){
				startBall = 1;
			}
			if(ch==27){
				break;
			}
		}
			{
			gotoxy(sliderPos01[1],sliderPos01[0]);
			int a=254,b=118;
			cout<<"<<"<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<char(a)<<">>";
			}
		if( startBall == 1){
			refresh=1;
			if( dir == 1) { // TOP RIGHT
				ballPos[0] = ballPos[0] - 1;
				ballPos[1] = ballPos[1] + 2;
				if( ballPos[1] > MAXX ){
				dir = 2;
				}
			else if( ballPos[0] < MINY ){
					dir = 4;
				}
			}
			else if( dir == 2) {// TOP LEFT
				 ballPos[0] = ballPos[0] - 1;
			 	 ballPos[1] = ballPos[1] - 2;
				if( ballPos[0] < MINY ){
					dir = 3;
				}
				else if( ballPos[1] < MINX ){
					dir = 1;
				}		
			}
			else if( dir == 3) {//BOTTOM LEFT
				ballPos[0] = ballPos[0] + 1;
				ballPos[1] = ballPos[1] - 2;	
				if( ballPos[0] > MAXY ){
					lose = 1;
					break;
				}
				else if( ballPos[1] < MINX ){
					dir = 4;
					}
			}
		else if( dir == 4) {//BOTTOM RIGHT
				ballPos[0] = ballPos[0] + 1;
				ballPos[1] = ballPos[1] + 2;
				if( ballPos[1] > MAXX ){
						dir = 3;
			}
				else if( ballPos[0] > MAXY ){
					lose = 1;
					break;
				}
			}

			ballHitSlider();
		}	
		ballHitBrick();
		
		if( bricksLeft01 == 0 && bricksLeft03 == 0){
			win = 1;
			break;
		}			
		Sleep(sleep_value);
				count_border==count_border++;
		if (count_border==100)
			{
			drawBricks();	
				drawBorder();
			count_border=0;
			}
	}
	
	if( lose == 1){
		
		Level=1;
		system("cls");	
		drawBorder();
		gotoxy(70,24); cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		gotoxy(70,25); cout<<"-------------------------------------";
		gotoxy(70,26); cout<<"||                                 ||";
		gotoxy(70,27); cout<<"||            YOU LOSE             ||";
		gotoxy(70,28); cout<<"||                                 ||";
		gotoxy(70,29); cout<<"-------------------------------------";
		gotoxy(70,30); cout<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
		cout<<"\a";
		gotoxy(100,40); cout<<"Press any key to go back to Menu.";
		getch();
	}
	
	if( win == 1){
		
		Level+=1;      
		system("cls");
		drawBorder();
		
		if(Level==4){
		
		Level=1;	
		gotoxy(70,24); cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		gotoxy(70,25); cout<<"-------------------------------------";
		gotoxy(70,26); cout<<"||                                 ||";
		gotoxy(70,27); cout<<"||            YOU WIN              ||";
		gotoxy(70,28); cout<<"||                                 ||";
		gotoxy(70,29); cout<<"-------------------------------------";
		gotoxy(70,30); cout<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
		gotoxy(100,40); cout<<"Press any key to go back to Menu.";
		getch();
		
		}
		else{
			
		gotoxy(70,20); cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		gotoxy(70,21); cout<<"-------------------------------------";
		gotoxy(70,22); cout<<"||                                 ||";
		gotoxy(70,23); cout<<"||         LEVEL COMPLETE!         ||";
		gotoxy(70,24); cout<<"||                                 ||";
		gotoxy(70,25); cout<<"-------------------------------------";
		gotoxy(70,26); cout<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
		
		gotoxy(60,30); cout<<"   PRESS ANY KEY TO GO TO -------> || LEVEL 0"<<Level<<" || <--------";
		
		getch();
		
		}
		
	}		
}

void instructions(){
	system("cls");
	drawBorder();
	gotoxy(65,17);cout<<"Instructions....";
	gotoxy(65,22);cout<<"1. Use 'A' key to move slider to left";
	gotoxy(65,24);cout<<"2. Use 'D' key to move slider to right";
	gotoxy(65,26);cout<<"3. Press 'spacebar'' to start the game";
	gotoxy(65,28);cout<<"\t\t\tPress any key to go back to menu";
	getch();
}

void reset()
{
	for(int i=0; i<18; i++)
	visibleBricks01[i]= 1;
	
 	for(int k=0; k<18; k++)
 	visibleBricks06[k]= 1;
 	  
	random_position=0; 
	sliderPos01[0] = 52;
	sliderPos01[1] = 80;
	ballPos[0] = 51;
	ballPos[1] = 88;
	ballPos_refresh[0] = 0;
	ballPos_refresh[1] = 0;

	startBall = 0;
	dir = 2;
	bricksLeft01 = 12;
	bricksLeft03 = 12;
	win = 0;
	lose = 0;
}

void difficulty()
{
	system("cls");
	drawBorder();
			
	gotoxy(71,17); cout<<"-- Select difficulty --";
	gotoxy(78,19); cout<<"-------------";		
	gotoxy(78,20); cout<<"|  1. Easy  |";
	gotoxy(78,21); cout<<"-------------";
	
	gotoxy(82,22); cout<<"-------------";
	gotoxy(82,23); cout<<"| 2. Medium |";
	gotoxy(82,24); cout<<"-------------";
	
	gotoxy(86,25); cout<<"-------------";
	gotoxy(86,26); cout<<"|  3. Hard  |";
	gotoxy(86,27); cout<<"-------------";
	
	char diffi = getche();		
	if(diffi=='1')sleep_value=120;   
	else if(diffi=='2')sleep_value=65;
	else if(diffi=='3')sleep_value=35; 
	else sleep_value=85;
}

void level(int level_no){	

//****************************************LEVEL-01*********************************************
//set 01
int bricks_set_1_a[12][2] = { {16,16},{16,54},{16,72},{16,90},{16,108},{16,146},
						      {26,16},{ 6,54},{26,72},{26,90},{ 6,108},{26,146}  };
								
int bricks_set_1_b[12][2] = { {17,16},{17,54},{17,72},{17,90},{17,108},{17,146},
						      {27,16},{ 7,54},{27,72},{27,90},{ 7,108},{27,146}  };					

//set 02
int bricks_set_1_c[12][2] = { {11,20},{32,54},{11,72},{11,90},{32,108},{11,142},
						      {21,16},{21,54},{21,72},{21,90},{21,108},{21,146}  };
						      
int bricks_set_1_d[12][2] = { {12,20},{33,54},{12,72},{12,90},{33,108},{12,142},         
						      {22,16},{22,54},{22,72},{22,90},{22,108},{22,146}  };
						      
//*********************************************************************************************					

//****************************************LEVEL-02*********************************************
//set 03
int bricks_set_2_a[12][2] = { {4,24},{12,24},{20,24},{4,58},{12,62},{20,72},
						      {12,82},{4 ,86},{4,120},{8,142},{16 ,124},{20,128} };	
							  		
int bricks_set_2_b[12][2] = { {5,24},{13,24},{21,24},{5,58},{13,62},{21,72},
						      {13,82},{5 ,86},{5,120},{9,142},{17 ,124},{21,128} };					

//set 04
int bricks_set_2_c[12][2] = { {8,24},{16,24},{20,40},{8,60},{16,64},{16,80},
				              {8,84},{8,112},{4,136},{12,132},{20,112},{20,144} };
				              
int bricks_set_2_d[12][2] = { {9,24},{17,24},{21,40},{9,60},{17,64},{17,80},
						      {9,84},{9,112},{5,136},{13,132},{21,112},{21,144} };
						      
//*********************************************************************************************	

//****************************************LEVEL-03*********************************************
//set 05
int bricks_set_3_a[12][2] = { {9,20},{17,20},{25,20},{29,42},{29,74},{29,106},
						      {25,58},{25,90},{21,74},{9,146},{17,146},{25,146} };
							  			
int bricks_set_3_b[12][2] = { {10,20},{18,20},{26,20},{30,42},{30,74},{30,106},
						      {26,58},{26,90},{22,74},{10,146},{18,146},{26,146} };					

//set 06
int bricks_set_3_c[12][2] = { {13,20},{21,20},{29,20},{29,58},{29,90},{29,122},
						      {25,74},{25,106},{21,90},{13,146},{21,146},{29,146} };
						      
int bricks_set_3_d[12][2] = { {14,20},{22,20},{30,20},{30,58},{30,90},{30,122},
						      {26,74},{26,106},{22,90},{14,146},{22,146},{30,146} };
						      
//*********************************************************************************************
		
	int *pointer1;
	int *pointer2;
	
	pointer1 = &bricks01[0][0];
	pointer2 = &bricks_set_1_a[0][0];
	
	if(level_no==2)                   //...................loading level2 ...................
	pointer2 = &bricks_set_2_a[0][0]; 
	
	else if(level_no==3)              //......................loading level3.................
	pointer2 = &bricks_set_3_a[0][0]; 
	

			for(int m=0; m<24; m++)
			*(pointer1+m) = *(pointer2+m);
		
			for(int n=24; n<48; n++)
			*(pointer1+n+8) = *(pointer2+n);
		
			for(int p=48; p<72; p++)
			*(pointer1+p+16) = *(pointer2+p);
		
			for(int q=72; q<96; q++)
			*(pointer1+q+24) = *(pointer2+q);
		
}


