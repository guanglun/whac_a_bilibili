//welcome www.guanglundz.com

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//thread
#include <pthread.h>

#include "oled.h"
#include "img.h"


/*********************************************************/
//mice
/*********************************************************/
char X_Pos = 63,Y_Pos = 31,X_LCD_Pos = 63,Y_LCD_Pos = 31,Pos_Mark=0,old_X_LCD_Pos=63,old_Y_LCD_Pos=31;
char Left_Check=0,Left_Check_X=0,Left_Check_Y=0,Right_Check=0,Right_Check_X=0,Right_Check_Y=0;
/*********************************************************/

/*********************************************************/
//thread
/*********************************************************/
void thread_mice(void* args)
{
	int fd, retval;
	char buf[6];
	fd_set readfds;
	struct timeval tv;
	fd = open( "/dev/input/mice", O_RDONLY );
	if(fd<0)
	{
		printf("Failed to open \"/dev/input/mice\".\n");
		exit(1);
	}
	else 
	{
		printf("open \"/dev/input/mice\" successfuly.\n");
	}
	
	while(1) 
	{
		// 设置最长等待时间
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		
		FD_ZERO( &readfds );
		FD_SET( fd, &readfds );
		
		retval = select( fd+1, &readfds, NULL, NULL, &tv );
/* 		if(retval==0)
		{
			printf( "Time out!\n" );
		} */
		if(FD_ISSET(fd,&readfds)) 
		{
			// 读取鼠标设备中的数据
			if(read(fd, buf, 6) <= 0) 
			{
				continue;
			}
			
			X_Pos += buf[1];
			if(buf[1]>127&&X_Pos>127) X_Pos = 0;
			else if(X_Pos>127) X_Pos = 127;
			Y_Pos += buf[2];
			if(buf[2]>63&&Y_Pos>63) Y_Pos = 0;
			else if(Y_Pos>63) Y_Pos = 63;
			
			if(!Pos_Mark)
			{
				X_LCD_Pos = X_Pos;
				Y_LCD_Pos = 63-Y_Pos;
				Pos_Mark = 1;
			}
			if((buf[0] & 0x07)==1&&Left_Check==2)
			{
				Left_Check = 1;
				Left_Check_X = X_LCD_Pos;
				Left_Check_Y = Y_LCD_Pos;
			}
			else if((buf[0] & 0x07)==2&&Right_Check==2)
			{
				Right_Check = 1;
				Right_Check_X = X_LCD_Pos;
				Right_Check_Y = Y_LCD_Pos;
			}
			else if((buf[0] & 0x07)==0)
			{
				Left_Check=2;
				Right_Check=2;
			}
	//		printf("Button type = %d, X = %d, Y = %d,X_Pos = %d,Y_Pos = %d\n", (buf[0] & 0x07), (char)buf[1], (char)buf[2],X_LCD_Pos,Y_LCD_Pos);
		}
	}
	close(fd);
}

void thread_olcd(void* args)
{
	word LCD_Cnt=0;
    while(1)
	{
      // sleep(1);
      // LCD_ShowNum(2,4,LCD_Cnt++,8);
	  //LCD_DLY_ms(1000);

    }
}

void game_start(void)
{
	byte xx=0,yy=0,RPI[8]={0,0,0,0,0},A_RPI_Start[8]={0,0,0,0,0},A_RPI_Stop[8]={0,0,0,0,0},A_RPI_ii=0;
	byte AA0=0,AA1=0,AA2=0,AA3=0,AA4=0,AA5=0,AA6=0,AA7=0,Rank=15,NumString_Rank[10]={0,0,0,0,0,0,0,0,0,0},NumString_RPI[10]={0,0,0,0,0,0,0,0,0,0};
	byte NumString_Die_Cnt[10];
	byte Die_Cnt[8]={0,0,0,0,0},Die_Num=0,ca=0;
	dword CNT=1,Rand_Cnt=0,RPI_Cnt=0;
	
	Num2String(RPI_Cnt,3,NumString_RPI);
	Num2String(Rank,3,NumString_Rank);
	
	Draw_BMP(gImage_start);
	sleep(2);
	Draw_BMP(gImage_start);
	sleep(1);
	Draw_BMP(gImage_anykey);
	
	while(1)
	{
		 if(Left_Check==1)
		 {
			 Left_Check=0;
			 break;
		 }
	}
	srand((int) time(0));
	while(1)
	{
	  if(Pos_Mark)
	  {
		  
		  if(X_LCD_Pos>119)X_LCD_Pos=119;
		  if(Y_LCD_Pos>55)Y_LCD_Pos=55;
		  
		  old_X_LCD_Pos=X_LCD_Pos;
		  old_Y_LCD_Pos=Y_LCD_Pos;
		  Pos_Mark = 0;
	  }
	  
	  CNT++;
	  Rand_Cnt++;
	  Num2String(Die_Num,1,NumString_Die_Cnt);
	  LCD_W_BMP(0,16,24,24,gImage_A_RPI[RPI[0]],1);
	  LCD_W_BMP(30,16,24,24,gImage_A_RPI[RPI[1]],1);
	  LCD_W_BMP(60,16,24,24,gImage_A_RPI[RPI[2]],1);
	  LCD_W_BMP(90,16,24,24,gImage_A_RPI[RPI[3]],1);
	  
	  LCD_W_BMP(0,40,24,24,gImage_A_RPI[RPI[4]],1);
	  LCD_W_BMP(30,40,24,24,gImage_A_RPI[RPI[5]],1);
	  LCD_W_BMP(60,40,24,24,gImage_A_RPI[RPI[6]],1);
	  LCD_W_BMP(90,40,24,24,gImage_A_RPI[RPI[7]],1);
	  
	  LCD_P6x8Str(0,0,"BB:",1);
	  LCD_P6x8Str(0,1,"RANK:",1);
	  LCD_P6x8Str(60,1,"DIE:",1);
	  LCD_P6x8Str(60,0,"BiliBili",1);
	  LCD_P6x8Str(30,0,NumString_RPI,1);
	  LCD_P6x8Str(30,1,NumString_Rank,1);
	  LCD_P6x8Str(90,1,NumString_Die_Cnt,1);
	  
	  LCD_W_BMP(X_LCD_Pos,Y_LCD_Pos,8,8,OLED_mice,1);
	  
	  Draw_BMP(LCD_Buffer);
	  LCD_W_BMP(old_X_LCD_Pos,old_Y_LCD_Pos,8,8,OLED_mice,0);
	  
	  LCD_P6x8Str(0,0,"BB:",0);
	  LCD_P6x8Str(0,1,"RANK:",0);
	  LCD_P6x8Str(90,1,"DIE:",0);
	  LCD_P6x8Str(60,0,"BiliBili",1);
	  LCD_P6x8Str(30,0,NumString_RPI,0);
	  LCD_P6x8Str(30,1,NumString_Rank,0);
	  LCD_P6x8Str(80,1,NumString_Die_Cnt,0);
	  
	  LCD_W_BMP(0,16,24,24,gImage_A_RPI[RPI[0]],0);
	  LCD_W_BMP(30,16,24,24,gImage_A_RPI[RPI[1]],0);
	  LCD_W_BMP(60,16,24,24,gImage_A_RPI[RPI[2]],0);
	  LCD_W_BMP(90,16,24,24,gImage_A_RPI[RPI[3]],0);
	  
	  LCD_W_BMP(0,40,24,24,gImage_A_RPI[RPI[4]],0);
	  LCD_W_BMP(30,40,24,24,gImage_A_RPI[RPI[5]],0);
	  LCD_W_BMP(60,40,24,24,gImage_A_RPI[RPI[6]],0);
	  LCD_W_BMP(90,40,24,24,gImage_A_RPI[RPI[7]],0);
	    
	  if(Rand_Cnt >= Rank)
	  {
		  Rand_Cnt=0;
		  switch(rand()%8)
		  {
			  case 0:if(A_RPI_Stop[0]==0) {A_RPI_Stop[0]=1;A_RPI_Start[0]=1;}break;
			  case 1:if(A_RPI_Stop[1]==0) {A_RPI_Stop[1]=1;A_RPI_Start[1]=1;}break;
			  case 2:if(A_RPI_Stop[2]==0) {A_RPI_Stop[2]=1;A_RPI_Start[2]=1;}break;
			  case 3:if(A_RPI_Stop[3]==0) {A_RPI_Stop[3]=1;A_RPI_Start[3]=1;}break;
			  case 4:if(A_RPI_Stop[4]==0) {A_RPI_Stop[4]=1;A_RPI_Start[4]=1;}break;
			  case 5:if(A_RPI_Stop[5]==0) {A_RPI_Stop[5]=1;A_RPI_Start[5]=1;}break;
			  case 6:if(A_RPI_Stop[6]==0) {A_RPI_Stop[6]=1;A_RPI_Start[6]=1;}break;
			  case 7:if(A_RPI_Stop[7]==0) {A_RPI_Stop[7]=1;A_RPI_Start[7]=1;}break;
			  default:break;	  
		  }
	  }
	  if(CNT==2)
	  {
		  for(A_RPI_ii=0;A_RPI_ii<8;A_RPI_ii++)
		  {
			  if(A_RPI_Start[A_RPI_ii]==1)	
			  {
					if(RPI[A_RPI_ii]<4)RPI[A_RPI_ii]++;
					else 
					{
						Die_Num++;
						A_RPI_Start[A_RPI_ii]=2;
					}
						
			  }		   
		      if(A_RPI_Stop[A_RPI_ii]==2)
			  {
				  if(RPI[A_RPI_ii]<8)
					  RPI[A_RPI_ii]++;
				  else 
				  {
						RPI[A_RPI_ii]=0;
						A_RPI_Stop[A_RPI_ii]=0;
						A_RPI_Start[A_RPI_ii]=0;
				  }
			  }
					  
		  }
		  if(Right_Check==1)
		  {
			  LCD_Init();
			  Right_Check=0;
		  }
		  if(Left_Check==1)
		  {
			  if( 4 <Left_Check_X&& 24 >Left_Check_X&& 18 <Left_Check_Y&&35>Left_Check_Y&&A_RPI_Stop[0]==1)
			  {
					  A_RPI_Stop[0]=2;
					  RPI[0]=5;
					  RPI_Cnt++;
					  Die_Num--;
					  ca=1;
			  }
			  else if( 34 <Left_Check_X&& 49 >Left_Check_X&& 18 <Left_Check_Y&& 35 >Left_Check_Y&&A_RPI_Stop[1]==1)
			  {
				  A_RPI_Stop[1]=2;
				  RPI[1]=5;
				  RPI_Cnt++;
				  Die_Num--;
				  ca=1;
			  }  
			  else if( 63 <Left_Check_X&& 80 >Left_Check_X&& 18 <Left_Check_Y&& 35 >Left_Check_Y&&A_RPI_Stop[2]==1)
			  {
				  A_RPI_Stop[2]=2;
				  RPI[2]=5;
				  RPI_Cnt++;
				  Die_Num--;
				  ca=1;
			  }  
			  else if( 93 <Left_Check_X&& 109 >Left_Check_X&& 18 <Left_Check_Y&& 35 >Left_Check_Y&&A_RPI_Stop[3]==1)
			  {
				  A_RPI_Stop[3]=2;
				  RPI[3]=5;
				  RPI_Cnt++;
				  Die_Num--;
				  ca=1;
			  }  
			  else if( 4 <Left_Check_X&& 24 >Left_Check_X&& 43 <Left_Check_Y&&67>Left_Check_Y&&A_RPI_Stop[4]==1)
			  {
				  A_RPI_Stop[4]=2;
				  RPI[4]=5;
				  RPI_Cnt++;
				  Die_Num--;
				  ca=1;
			  }
			  else if( 34 <Left_Check_X&& 49 >Left_Check_X&& 43 <Left_Check_Y&& 67 >Left_Check_Y&&A_RPI_Stop[5]==1)
			  {
				  A_RPI_Stop[5]=2;
				  RPI[5]=5;
				  RPI_Cnt++;
				  Die_Num--;
				  ca=1;
			  }  
			  else if( 63 <Left_Check_X&& 80 >Left_Check_X&& 43 <Left_Check_Y&& 67 >Left_Check_Y&&A_RPI_Stop[6]==1)
			  {
				  A_RPI_Stop[6]=2;
				  RPI[6]=5;
				  RPI_Cnt++;
				  Die_Num--;
				  ca=1;
			  }  
			  else if( 93 <Left_Check_X&& 109 >Left_Check_X&& 43 <Left_Check_Y&& 67 >Left_Check_Y&&A_RPI_Stop[7]==1)
			  {
				  A_RPI_Stop[7]=2;
				  RPI[7]=5;
				  RPI_Cnt++;
				  Die_Num--;
				  ca=1;
			  }  
			  if(ca)
			  {
				  if(!(RPI_Cnt%11)) Rank--;
				  Num2String(RPI_Cnt,3,NumString_RPI);
				  Num2String(Rank,3,NumString_Rank);
				  Left_Check=0;
				  ca=0;
			  }
		  }

		  CNT=0;
	  }
	  if(Die_Num>=5)
	  {
	  
			Draw_BMP(gImage_gameover);
		    LCD_P8x16Str(75,5,NumString_RPI);
		    printf("Game Score:%d\n",RPI_Cnt);
			sleep(3);
			while(1)
			{
				 if(Left_Check==1)
				 {
					 Left_Check=0;
					 break;
				 }
			}			
			return 0;
	  }
	}	
}

int main(int argc,char **argv)
{

	pthread_t pid1, pid2; //thread

	LCD_Init();


	if(pthread_create(&pid1, NULL, thread_mice, NULL))
    {
        return -1;
    }

	while(1)
	{
		game_start();
	}
	return 0;
}