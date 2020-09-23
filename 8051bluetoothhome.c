#include<reg51.h>
#include<reg51.h>  
#define kam P1 

void lcd_initi();  
void lcd_dat(unsigned char a );  
void lcd_cmd(unsigned char b );  
void delay(unsigned int n);  
void display(unsigned char s, unsigned char r)  ;
sbit rs=P2^0;  
sbit rw=P2^1;  
sbit en=P2^2; 

sbit Fan=P0^0;
sbit Light=P0^1;
sbit TV=P1^2;

		int o=0;
		int r=0;
		//unsigned   char Charin;
char s[];
unsigned	int l;
	unsigned int w; 
	int j=0;
unsigned char *str;
unsigned char *Charin;
unsigned char *p;
void delay(int time)
{
 unsigned int i,j;
 for(i=0;i<time;i++)
 for(j=0;j<1275;j++);
}

void Serialwrite(char byte)
{
  SBUF=byte;
  while(!TI);
  TI=0;
}

void Serialprintln(char *p)
{
  while(*p)
  {
    Serialwrite(*p);
    p++;
  }
 
}

void Serialbegin()
{
   TMOD=0x20;
   SCON=0x50;
   TH1=0xfd;
   TR1=1;
}
void display(unsigned char *s, unsigned char r)  
{  
unsigned int w;  
for(w=0;w<r;w++)  
{  
lcd_dat(s[w]);  
}  
}  

void display1(unsigned char *s, unsigned char r)  
{  
unsigned int w;  
for(w=0;w<r;w++)  
{  
lcd_dat(*s);
s++;  
}  
}  




void lcd_initi()  
{  
lcd_cmd(0x01);  
delay(10);  
lcd_cmd(0x38);  
delay(10);  
lcd_cmd(0x06);  
delay(10);  
lcd_cmd(0x0c);  
delay(10);  
}  
void lcd_dat(unsigned char dat)  
{  
kam = dat;  
rs=1;  
rw=0;  
en=1;  
delay(10);  
en=0;  
}  
  
void lcd_cmd(unsigned char cmd)  
{  
kam=cmd;  
rs=0;  
rw=0;  
en=1;  
delay(10);  
en=0;  
}  


void main()
{lcd_initi(); 
  P1=0x00;
  Serialbegin();
  Serialprintln("System Ready...");
	display("System Ready...",15);
  delay(10);

	l=0;
	while(1)
  {
lcd_cmd(0x80);  
delay(10);  


 while(!RI);
 *Charin=SBUF;
	*str=*Charin;
lcd_cmd(0x01);
		 RI=0;       
      if(*str=='a')
				
      { lcd_cmd(0x01);
				display("LIGHT ON",8);  

        Fan=1;
  
        delay(100);
      }
      else if(*str=='b')
				
      { 
				lcd_cmd(0x01);
				display("LIGHT OFF",9); 
        Fan=0;
        Serialprintln(" Fan OFF");
        delay(50);
      }

       else if(*str=='c')
      { lcd_cmd(0x01);
				display("FAN ON",6);  
        Light=1;
        Serialprintln(" FAN ON");
        delay(50);
      }

       else if(*str=='d')
      {lcd_cmd(0x01);
        display("FAN OFF",7); 
				Light=0;
        Serialprintln(" FAN ON");
        delay(50);
      }

     
      }
      str=0;
  }
}