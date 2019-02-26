#include <TM1637Display.h>

const int CLK = 9; //Set the CLK pin connection to the display
const int DIO = 8; //Set the DIO pin connection to the display
long int btime=120000;                       //Time for timer  
long int bmin=0,bsec=0;   
unsigned long currentmil;
int disp=0 ;

TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.

void setup()
{
  
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
}


void loop()
{
  currentmil=millis();    
  if(btime+currentmil>currentmil)
  {
    bmin=btime/60000;
    bsec=btime-bmin*60000; 
    bsec=bsec/1000;
    disp=bmin*100+bsec;
    display.showNumberDec(disp);  
    btime=btime-1000;
    delay(1000);
  }
  
}
