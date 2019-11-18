/*
 * final.c
 *
 * Created: 6/16/2016 3:05:12 PM
 * Author : Anil Gawali
 */ 

#include <avr/io.h>
#include <string.h>
#include "init.h"
#define ref 179 // reference voltage for sensor input
#define F_CPU 8000000UL
int d1=87;
int d2=160;
int main()
{
   
		port();
		timer();
		
		unsigned char s[7];
		int i, c, p[7],a1,a2,a3,a4,a5,a6;
		
		s[0]=0, p[0]=0;
				
		
		while (1)   // Main code begins.
		{
			for (i=1;i<7;i++)      // sensor reading
			{
				s[i]=read_adc(i);
				
			}
			for (i=1;i<7;i++)    // led glow after sensor compare
			{
				if (s[i]<ref)
				{
					p[i]=1;
					cbit(PORTC,(8-i));
				}
				else
				{
					p[i]=0;
					sbit(PORTC,(8-i));
				}
					
			}
		
        if (p[1]==0 && p[2]==0 && p[3]==1 && p[4]==1 && p[5]==0 && p[6]==0) 
		c=1;
		
        else if (p[1]==0 && p[2]==0 && p[3]==1 && p[4]==0 && p[5]==0 && p[6]==0)
        c=2;
		  
		else if (p[1]==0 && p[2]==0 && p[3]==0 && p[4]==1 && p[5]==0 && p[6]==0)
        c=3;
		
		else if (p[1]==1 && p[2]==1 && p[3]==1 && p[4]==1 && p[5]==0 && p[6]==0)
		c=4;
		
		else if (p[1]==1 && p[2]==1 && p[3]==0 && p[4]==0 && p[5]==1 && p[6]==1)
		c=5;
		
		else if (p[1]==1 && p[2]==1 && p[3]==0 && p[4]==1 && p[5]==1 && p[6]==1)
		c=6;
		
		else if (p[1]==1 && p[2]==1 && p[3]==1 && p[4]==0 && p[5]==1 && p[6]==1)
		c=7;
		
		else if (p[1]==1 && p[2]==1 && p[3]==0 && p[4]==0 && p[5]==0 && p[6]==0)
		c=8;
		
		else if (p[1]==1 && p[2]==1 && p[3]==1 && p[4]==1 && p[5]==1 && p[6]==1)
		c=9;
		
		 
		else c=65;
		
        sbit(PORTB,2);
	switch (c)
		{
			case 1: forward(d1,d2);  //001100  
					break;

 			case 2: forward(0,d2);       //001000
					break;
			
			case 3: forward(d1,0);      //000100
					break;
			
			case 4: _delay_ms(50);
			          left90();            //111100
	                _delay_ms(750);
			case 5: forward(d1,d2);    //110011
		            break;
		  
		    case 6:  forward(0,d2);       //110111
		             break;
		    
			case 7: forward(d1,0);      //111011
			        break;
		    
			case 8: forward(0,d2);       //110000
			        break;  
		   
		    case 9: cbit(PORTB,2);
			        forward(d1,d2);     //111111   make this 111111 condition sirf test karne ke liye kiya hai
		  }
      }
   // return 0;
			
			}
			