#include <stdio.h>
#include <stdio.h>
#include <mcp3004.h>
#include <wiringPi.h>

#define relay_IT 2  // GPIO 27 for BCM on it circuit,relay on it 
#define relay_com 3  // GPIO 22 for BCM on it circuit,LED COM
#define relay1 21  // GPIO 5 for BCM on it circuit,LED1
#define relay2 22  // GPIO 6 for BCM  on it circuit,LED2
#define relay3 23  // GPIO 13 for BCM  on it circuit,LED3
#define relay4 25  // GPIO 26 for BCM  on it circuit,LED4
#define relay5 26  // GPIO 12 for BCM  on it circuit,LED5
#define buzzer 27  // GPIO 16 for BCM  on it circuit,buzzer

#define BASE 200      // SPI�����]�w
#define SPI_CHAN 0  



int main ( ) {

   	int value[5];
    int chan[6]={0,1,2,3,4,5};
    int relay[6]={0,21,22,23,25,26};
    int i = 1;
    int j = 1;
   
   wiringPiSetup () ;
   
   mcp3004Setup( BASE, SPI_CHAN );  // 3004�P3008���ۦP�t�CIC
   
   if ( wiringPiSetup ( ) == -1 )  // �]�wWiringPi
      return 2;

     pinMode( relay_IT, OUTPUT );  // �]�w����X 
 
     pinMode( relay_com, OUTPUT );  // �]�w����X
	  
    for (j=1;j<6;j++){
      pinMode( relay[j], OUTPUT );  // �]�w����X 
	  digitalWrite(relay[j],LOW);	
     
	}
//	  pinMode( relay1, OUTPUT );  // �]�w����X 
 //    pinMode( relay2, OUTPUT );  // �]�w����X 
 //    pinMode( relay3, OUTPUT );  // �]�w����X 
 //    pinMode( relay4, OUTPUT );  // �]�w����X 
 //  pinMode( relay5, OUTPUT );  // �]�w����X 
 //  pinMode( buzzer, OUTPUT );  // �]�w����X 
   
   
   digitalWrite (relay_com, LOW) ;	// On for LED
   
   
   while ( 1 ) {
/*  
 	digitalWrite (relay_IT, HIGH) ;	// On
	digitalWrite (relay1, HIGH) ;	// On
	digitalWrite (relay2, HIGH) ;	// On
	digitalWrite (relay3, HIGH) ;	// On
	digitalWrite (relay4, HIGH) ;	// On
	digitalWrite (relay5, HIGH) ;	// On
	digitalWrite (buzzer, HIGH) ;	// On
	
	delay (1000) ;		// mS
	
	digitalWrite (relay_com, LOW) ;	// off
	digitalWrite (relay_IT, LOW) ;	// Off
	digitalWrite (relay1, LOW) ;	// off
	digitalWrite (relay2, LOW) ;	// off
	digitalWrite (relay3, LOW) ;	// off
	digitalWrite (relay4, LOW) ;	// off
	digitalWrite (relay5, LOW) ;	// off
	
	digitalWrite (buzzer, LOW) ;	// off
	
	delay (1000) ;
*/
    
	 i=1; 
	 for (i=1;i<6;i++)
       {
       	 value[i] =  analogRead( BASE + chan[i]) ;  // Ū�������J
       	
		if (value[i] > 400 ){
	   	
		
		  digitalWrite (relay[i], HIGH) ;	// On	
	
		
		  printf ("Value%d = %4d\n",i, value[i]) ;
		  delay( 100 ); 	
		}
       	else {
       	  digitalWrite (relay[i], LOW) ;	// OFF
   
	     printf ("Value%d = %4d\n",i, value[i]) ;
		  delay( 100 ); 	
       		
		   }
         
	   }
	 
	 
	   
       printf("\n");
	
    }
    return 0;
}




