//
#include <stdio.h>
#include <graphics.h>      
#include <conio.h>
#include <stdio.h>
#include <time.h>

int mine_row,mine_line,size;
int m_x,m_y;
int **p;
int m_marked;
int m_digged;
int  m_faceX;
int m_faceY;
int mine_number;
int STATE=0;

void draw_box(int x,int y,int width,int heigh,int type,int depth);
void graph();
void draw_area(int w);
void lay_mine(int mine_number);
void draw_mine(int x,int y);
void show_all_data();
void show_number(int x,int y,int number,int w);
void Around_mine_number();
int  Mouse_Click_left(MOUSEMSG *mouse);
void Mouse_Click(unsigned int t1,unsigned int t2,int t);
int dig_mine(int x,int y);
void cal_dig_mine(int x,int y,int *i,int *j);
void dig_mine1(int i,int j);
void dig_mine2(int i,int j);
void draw_flag(int i,int j);
void Mouse_Click_right(MOUSEMSG *mouse);
void put_flag(int i,int j);
void show_game(char str[]);
void smile_face();
void scan_mine();
void Mouse_Move(MOUSEMSG *mouse);
void show_mine_number();
void show_Minenumber(int x,int y,int num);
void initialize();
void show_time(int t);


#define GAME_FAILURE 0
#define GAME_RUNNING 1
#define GAME_RESTART 2

void main()
{      
	printf("行数 列数 雷数\n");
    scanf("%d %d %d",&mine_line,&mine_row,&mine_number);
    fflush(stdin);
     while(1)
	 {    
		 int t1=0L,t2=0L,t=0;
		 initialize();	
	      Mouse_Click(t1,t2,t);
	}
    closegraph();        
}

void graph()
{   
	int i;
    initgraph(800,600);
	size=30;
    m_x=(getwidth()-mine_line*(size+1)-1)/2;
	m_y=(getheight()-mine_row*(size+1)-1)/2;
    
    p=(int **)malloc(sizeof(int *)*mine_row);
	for(i=0;i<mine_row;i++)
        *(p+i)=(int *)malloc(sizeof(int)*mine_line);
	m_faceX=m_x+(mine_line*(size+1)-1)/2-size/2;
    m_faceY=m_y-3-(2*(size+1))*3/4;


}

void draw_area(int w)
{
     int x,y;
	 int i,j;
	 int width,heigh;
	 //总体
	 x=m_x-size;
	 y=m_y-size*2;
	 width=mine_line*(size+1)-1+size*2;
	 heigh=mine_row*(size+1)-1+size*3;
	 draw_box(x,y,width,heigh,1,0);

	 //放小格子的框

	 x=m_x-3;
	 y=m_y-3;
	 width=mine_line*(size+1)+3*2;
     heigh=mine_row*(size+1)+3*2;
	 draw_box(x,y,width,heigh,1,3);
     //左长方形小格
     x=m_x;
	 y=m_y-3-(2*(size+1))*3/4;
	 draw_box(x,y+2,size*3,size,1,2);
	 //右长方形小格
     x=m_x+(mine_line-3)*(size+1);
	 y=m_y-3-(2*(size+1))*3/4;
	 draw_box(x,y+2,size*3,size,1,2);
	 
     //小格子

     y=m_y;
	 x=m_x;
	 for(i=0;i<mine_row;i++)
	 {
		 for(j=0;j<mine_line;j++)
			 draw_box(x+(size+1)*j,y+(size+1)*i,size,size,w,2);
	 }
}

void draw_box(int x,int y,int width,int heigh,int type,int depth)
{
    int i;

	setcolor(WHITE);
    
     rectangle(x,y,x+width,y+heigh);
    setfillstyle(BS_SOLID);
    setfillcolor(LIGHTGRAY);
	floodfill(x+width/2,y+heigh/2,WHITE);
     if(0==depth)
	 {
       setcolor(LIGHTGRAY);
       rectangle(x,y,x+width,y+heigh);
       return;
	 }
	if(type==1) setcolor(DARKGRAY);
	else if(type==2) setcolor(WHITE);
	for(i=0;i<depth;i++)
	{
	    line(x+i,y+i,x+width-i,y+i);
		line(x+i,y+i,x+i,y+heigh-i);
	}
	if(type==1) setcolor(WHITE);
	else if(type==2) setcolor(DARKGRAY);
	for(i=0;i<depth;i++)
	{
	    line(x+width-i,y+i,x+width-i,y+heigh-i);
		line(x+i,y+heigh-i,x+width-i,y+heigh-i);
	}
     
}

void lay_mine(int mine_number)
{    
     int i,j,count=0;
	 srand((unsigned)time(NULL));
     for(i=0;i<mine_row;i++)
		 for(j=0;j<mine_line;j++)
			 p[i][j]=0;
    
	 while(count<mine_number)
	 {
         i=rand()%mine_row;
	     j=rand()%mine_line;
         if(p[i][j]+1)
		 {
		 p[i][j]=-1;
		 count++;
		 }
	 }
}

void draw_mine(int x,int y)
{    

	x=x+size/2;
	y=y+size/2+1;
    setcolor(BLACK);
	circle(x,y,size/3);
    setfillstyle(BS_SOLID);
    setfillcolor(BLACK);
	floodfill(x,y,BLACK);
	setfillcolor(BLACK);
	floodfill(x,y,BLACK);
    rectangle(x-size/10,y,x+size/10,y-size*4/10);
    floodfill(x,y-size*4/10+1,BLACK);
}

void show_number(int x,int y,int number,int w)
{
     char str[5];
	 if(number==0)
         str[0]='\0';
	 else if(number<10)
	 {
	     str[0]=number+'0';
		 str[1]='\0';
	 }
	 else if(number<100)
	 {
	     str[0]=number/10+'0';
		 str[1]=number%10+'0';
		 str[2]='\0';
	 }
	 else if(number<1000)
	 {
	     str[0]=number/10+'0';
		 str[1]=number%10/10+'0';
		 str[2]=number%10+'0';
		 str[3]='\0';
	 }
     draw_box(x,y,size,size,w,2);
    settextstyle(size*2/3, size/2, _T("宋体"));
     setbkmode(TRANSPARENT);
	 switch(number)
	 {
	 case 1:
		 setcolor(BLUE);
		 break;
	 case 2:
		 setcolor(GREEN);
		 break;
	 case 3:
		 setcolor(CYAN);
		 break;
	 case 4:
		 setcolor(RED);
		 break;
	 case 5:
		 setcolor(MAGENTA);
		 break;
	 case 6:
		 setcolor(YELLOW);
		 break;
	 case 7:
		 setcolor(WHITE);
		 break;
	 case 8:
		 setcolor(LIGHTGREEN);
		 break;
     default:
		 setcolor(DARKGRAY);
	     break;
	 }
     outtextxy(x+size/4,y+size/6,str);
}

void show_all_data()
{
      int i,j;
	  draw_area(1);
	 for(i=0;i<mine_row;i++)
		 for(j=0;j<mine_line;j++)
		 {
	         if(p[i][j]==-1)
		        draw_mine(m_x+(size+1)*j,m_y+(size+1)*i);
             if(p[i][j]>=0&&p[i][j]<=8)
               show_number(m_x+(size+1)*j,m_y+(size+1)*i,p[i][j],1); 
		 }
}

void Around_mine_number()
{
     int i,j;
	 for(i=0;i<mine_row;i++)
		 for(j=0;j<mine_line;j++)
	 {   
         if(p[i][j]==-1)
			 continue;
	     if(i==0&&j==0)//左上角
		 {
		   if(p[i][j+1]==-1) p[i][j]++;
		   if(p[i+1][j+1]==-1) p[i][j]++;
		   if(p[i+1][j]==-1) p[i][j]++;
		 }
		 else if((j==mine_line-1)&&(i==0)) //右上角
		 {
		   if(p[i][j-1]==-1) p[i][j]++;
		   if(p[i+1][j]==-1) p[i][j]++;
		   if(p[i+1][j-1]==-1) p[i][j]++;
		 }
		 else if((i==mine_row-1)&&(j==0))//左下角
		 {
		   if(p[i][j+1]==-1) p[i][j]++;
		   if(p[i-1][j+1]==-1) p[i][j]++;
		   if(p[i-1][j]==-1) p[i][j]++;
		 }
		 else if((i==mine_row-1)&&(j==mine_line-1)) //右下角
		 {
		   if(p[i][j-1]==-1) p[i][j]++;
		   if(p[i-1][j]==-1) p[i][j]++;
		   if(p[i-1][j-1]==-1) p[i][j]++;
		 }
		 else if(i==0&&(j<mine_line-1&&j>0)) //上边
		 {
		   if(p[i][j-1]==-1) p[i][j]++;
		   if(p[i][j+1]==-1) p[i][j]++;
		   if(p[i+1][j]==-1) p[i][j]++;
		   if(p[i+1][j-1]==-1) p[i][j]++;
		   if(p[i+1][j+1]==-1) p[i][j]++;		 
		 }
          else if((i==mine_row-1)&&(j<mine_line-1&&j>0))//下边
		  {
		   if(p[i][j+1]==-1) p[i][j]++;
		   if(p[i][j-1]==-1) p[i][j]++;
		   if(p[i-1][j]==-1) p[i][j]++;
		   if(p[i-1][j+1]==-1) p[i][j]++;
		   if(p[i-1][j-1]==-1) p[i][j]++;
		  }
		  else if((i<mine_row-1&&i>0)&&j==0) //左边
		  {
		   if(p[i][j+1]==-1) p[i][j]++;
		   if(p[i-1][j]==-1) p[i][j]++;
		   if(p[i-1][j+1]==-1) p[i][j]++;
		   if(p[i+1][j]==-1)  p[i][j]++;
		   if(p[i+1][j+1]==-1) p[i][j]++;
		  }
		  else if((i<mine_row-1&&i>0)&&j==mine_line-1) //右边
		  {
		   if(p[i][j-1]==-1) p[i][j]++;
		   if(p[i+1][j]==-1) p[i][j]++;
		   if(p[i+1][j-1]==-1) p[i][j]++;
		   if(p[i-1][j]==-1) p[i][j]++;
		   if(p[i-1][j-1]==-1) p[i][j]++;
		  }
		  else
		  {
		   if(p[i][j+1]==-1) p[i][j]++;
		   if(p[i][j-1]==-1) p[i][j]++;
		   if(p[i+1][j]==-1) p[i][j]++;
		   if(p[i+1][j+1]==-1) p[i][j]++;
		   if(p[i+1][j-1]==-1) p[i][j]++;
		   if(p[i-1][j]==-1) p[i][j]++;
		   if(p[i-1][j+1]==-1) p[i][j]++;
		   if(p[i-1][j-1]==-1) p[i][j]++;
		  }
	 }
}

void Mouse_Click(unsigned int t1,unsigned int t2,int t)
{
	int state;
	int x,y;
     MOUSEMSG mouse;	 
	 while(1)
	 {  
		 t1 = time(NULL);
      if(t1!=t2)
      {     
		  if(STATE==1)
		  {
          if(t<999) 
			  t++;
          show_time(t);
          t2=t1;
		  }
      }
		      if(!MouseHit())
			      continue;
			  show_mine_number();
		    mouse=GetMouseMsg();
            x=m_x+mine_line*(size+1)-1;
	        y=m_y+mine_row*(size+1)-1;
	     
		       Mouse_Move(&mouse);
		       switch(mouse.uMsg)
			   {
		          case WM_LBUTTONDOWN :                               //鼠标左键
	              state=Mouse_Click_left(&mouse);
			      break;
                  case WM_RBUTTONDOWN :
			      Mouse_Click_right(&mouse);
			      break;
			   }
		
	              
                  
     if(m_marked+m_digged==mine_row*mine_line&&m_marked==mine_number)
	 {
		 show_game("SUCCESSFUL!");
		 getch();
		 break;
	 }
	 if(state==GAME_FAILURE)
	 {
          show_game("FAILURE!");
		  getch();
		 break;
	 }
     if(state==GAME_RESTART)
	 break;

	}
}

int  Mouse_Click_left(MOUSEMSG *mouse)
{     
	int x,y;
	 int i,j;
int state;

	 x=m_x+mine_line*(size+1)-1;
	 y=m_y+mine_row*(size+1)-1;
	   if(x>=(mouse->x)&&(mouse->x)>=m_x&&(mouse->y)<=y&&(mouse->y)>=m_y)
	   {
		   STATE=1;
           cal_dig_mine(mouse->x,mouse->y,&i,&j);
           state=dig_mine(i,j);
		   return state;
	   }
  x=m_faceX+size*4/3;
  y=m_faceY+size*4/3;
  if((mouse->x)>m_faceX&&(mouse->x)<x&&(mouse->y)<y&&(mouse->y)>m_faceY)
	 {
	      draw_box(m_faceX,m_faceY,size*4/3,size*4/3,0,1);
		   smile_face();
		   state=GAME_RESTART;
		   return state;
	 }
    
}



int dig_mine(int i,int j)
{
	 if(p[i][j]==-1)
	 {
		int i,j;
	   for(i=0;i<mine_row;i++)
		 for(j=0;j<mine_line;j++)
	          if(p[i][j]==-1)
			  {
				  draw_box(m_x+(size+1)*j,m_y+(size+1)*i,size,size,1,2);
		         draw_mine(m_x+(size+1)*j,m_y+(size+1)*i);
			  }
		return GAME_FAILURE;
	 }
	 else if(0<p[i][j]&&p[i][j]<=8)
	 {
        show_number(m_x+(size+1)*j,m_y+(size+1)*i,p[i][j],1);
		p[i][j]+=10;
		m_digged++;
		return GAME_RUNNING;
	 }
	 else if(p[i][j]==0)
	 {
	      draw_box(m_x+(size+1)*j,m_y+(size+1)*i,size,size,1,2);
          p[i][j]+=10;
		  m_digged++;
       dig_mine1(i,j);
	 }
     return GAME_RUNNING;
}
void cal_dig_mine(int x,int y,int *i,int *j)
{

	 *i=(y-m_y)/(size+1);
	 *j=(x-m_x)/(size+1);
}

void dig_mine1(int i,int j)
{
     dig_mine2(i,j-1);
	 dig_mine2(i,j+1);
	 dig_mine2(i+1,j);
	 dig_mine2(i+1,j+1);
	 dig_mine2(i+1,j-1);
	 dig_mine2(i-1,j);
	 dig_mine2(i-1,j+1);
	 dig_mine2(i-1,j-1);
}
void dig_mine2(int i,int j)
{
     if(0>i||i>=mine_row)
		 return;
	 if(0>j&&j>=mine_line)
		 return;
	 dig_mine(i,j);
}


void draw_flag(int i,int j)
{    
	 int depth;
     setcolor(RED);
     line(m_x+(size+1)*j+size*3/8,m_y+(size+1)*i+size/8,m_x+(size+1)*j+size*6/8,m_y+(size+1)*i+size*5/8);
	 line(m_x+(size+1)*j+size*3/8,m_y+(size+1)*i+size/8,m_x+(size+1)*j+size*3/8,m_y+(size+1)*i+size*5/8);
	 line(m_x+(size+1)*j+size*3/8,m_y+(size+1)*i+size*5/8,m_x+(size+1)*j+size*6/8,m_y+(size+1)*i+size*5/8);
     setfillstyle(BS_SOLID);
     setfillcolor(RED);
 	 floodfill(m_x+(size+1)*j+size*3/8+1,m_y+(size+1)*i+size/8+3,RED);
	 setcolor(BLACK);
	 for(depth=0;depth<2;depth++)
	 line(m_x+(size+1)*j+size*3/8-depth,m_y+(size+1)*i+size/8,m_x+(size+1)*j+size*3/8-depth,m_y+(size+1)*i+size*7/8);
}

void Mouse_Click_right(MOUSEMSG *mouse)
{
     int x,y;
	 int i,j;
	 x=m_x+mine_line*(size+1)-1;
	 y=m_y+mine_row*(size+1)-1;     
       if(x>=(mouse->x)&&(mouse->x)>=m_x&&(mouse->y)<=y&&(mouse->y)>=m_y)
	   {
           cal_dig_mine(mouse->x,mouse->y,&i,&j);
           put_flag(i,j);
	   }
}

void  put_flag(int i,int j)
{
      if(p[i][j]>=-1&&p[i][j]<=8)
	  {
		  draw_flag(i,j);
		  p[i][j]+=20;
		  m_marked++;
		  return ;
	  }
	  if(p[i][j]>=19&&p[i][j]<=28)
	  {
		  p[i][j]-=20;
	     draw_box(m_x+(size+1)*j,m_y+(size+1)*i,size,size,2,2);
		 m_marked--;
		 return ;
	  }
}

void show_game(char str[])
{
	int x,y;
    settextstyle(2*size, size, _T("宋体"));
	setcolor(RED);
    x=mine_line*(size+1)-1-textwidth(str);
	y=mine_row*(size+1)-1-textheight(str);
	x=x/2+m_x;
	y=y/2+m_y;
    outtextxy(x+size/4,y+size/6,str);
}



void smile_face()
{
  int x,y;
  
  x=m_faceX+size*2/3;
  y=m_faceY+size*2/3;
  setcolor(RED);
  circle(x,y,size*2/3);
  line(x-size/3,y-size/4,x-size/6,y-size/4);
  line(x+size/6,y-size/4,x+size/3,y-size/4);
  line(x-size/6,y+size/4,x+size/6,y+size/4);
}


void Mouse_Move(MOUSEMSG *mouse)
{
     int x,y;
     x=m_faceX+size*4/3;
     y=m_faceY+size*4/3;
	 if((mouse->x)>m_faceX&&(mouse->x)<x&&(mouse->y)<y&&(mouse->y)>m_faceY)
	 {
	      draw_box(m_faceX,m_faceY,size*4/3,size*4/3,2,1);
		   smile_face();
	 }
	 else
	 {
	       draw_box(m_faceX,m_faceY,size*4/3,size*4/3,0,0);
	       smile_face();
	 }
}


void show_mine_number()
{
  int x,y,width,heigh;

  x=m_x;
  y=m_y-(2*(size+1))*3/4;
  width=size*3;
  heigh=size;
  draw_box(x,y,width,heigh,1,2);
  show_Minenumber(x,y,mine_number-m_marked);
}

void show_Minenumber(int x,int y,int num)
{
  char str[6];
  int i=0;
  if(num>=10000) 
	  return;
  if(num<0)
  {
    str[i++]='-';
    num=-num;
  }
  if(num>=1000)
  {
    str[i++]=num/1000+48;
    num=num%1000;
  }
  if(num>=100)
  {
    str[i++]=num/100+48;
    num=num%100;
  }
  if(num>=10)
  {
    str[i++]=num/10+48;
    num=num%10;
  }
  str[i++]=num+48;
  str[i]='\0';
  settextstyle(size*2/3, size/2, _T("宋体"));
  setcolor(RED);
  setbkmode(TRANSPARENT);
  outtextxy(x+size/4,y+size/6,str);
}

void initialize()
{
	      STATE=0;
		  graph();
		  m_marked=0;
          m_digged=0;
	      draw_area(2);
		  smile_face();
          lay_mine(mine_number);
          Around_mine_number();	
}

void show_time(int t)
{
  int x,y,width,heigh;
  x=m_x+(mine_line-3)*(size+1);;
  y=m_y-3-(2*(size+1))*3/4+1;
  width=size*3;
  heigh=size;
  draw_box(x,y,width,heigh,1,2);
  show_Minenumber(x,y,t);
}