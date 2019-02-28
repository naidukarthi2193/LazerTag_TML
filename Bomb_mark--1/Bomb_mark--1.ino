#include <TM1637Display.h>

const int CLK = 9; //Set the CLK pin connection to the display
const int DIO = 8; //Set the DIO pin connection to the display
int button =13;                             //button for start of timer
int defbut =2;
int butcount=0;                             //buttoncounter
long int btime=120000;                       //Time for timer  
long int bmin=0,bsec=0;                       
int buzzer=12;                              //buzzer pin 
int buuzertime=2000;
int buzzerdivide=1;                         //buzzer delay time
unsigned long currentmil;                   //track time 
int disp=0 ;
int dsec;
int firstcount=0;
TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.
 void buzzerfun();
void setup() {
  Serial.begin(9600); 
  pinMode(buzzer,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
}

void loop() {
  
  Serial.println(Serial.read());
  currentmil=millis();                      //get current time
  if(digitalRead(button)==LOW){
    butcount++;
  }
 
  if(btime+currentmil>currentmil  && butcount>0)   //if button is pressed and btime is zero
  {
    buzzerfun();                             //buzzer single beep function
    delay(buuzertime/buzzerdivide);          //time difference between 2 beeps
    bmin=btime/60000;                        //conversion to minutes
    bsec=btime-bmin*60000;
    dsec=bsec/1000;
    disp=bmin*100+dsec; //conversion to secconds
    if(bsec==30000||(bmin==0 && bsec==59000)||(bmin==0 && bsec==10000)||(bmin==0 && bsec==7000)||(bmin==0 && bsec==5000)||(bmin==0 && bsec==3000)||(bmin==0 && bsec==1000))    //time at which buzzer freq increases
    buzzerdivide++;                          
    btime=btime-1000;
                       //time reduces every second
    display.showNumberDec(disp);
    Serial.print(bmin);
    Serial.print(" : ");
    Serial.print(bsec);
    Serial.println("");
    Serial.print(disp);
    Serial.print(Serial.read());
if(Serial.read()>0 && disp>10 && firstcount != 1)
{
  
  for(int i=10;i>0;i--)
  {
    display.showNumberDec(i);
    delay(1000);
    Serial.print("btime");
    Serial.print(btime);
    if(i<2)
    firstcount=1;
  }
   
  delay(100);
}

delay(100);
Serial.print(btime);
Serial.println("-1");
if(Serial.read()>50 && btime!=0 && firstcount==1)
{
  Serial.println("loop");
  delay(100);
  btime=0;
  }
    
//  else{
//    display.showNumberDec(0); 
//  }
  if(btime==0)
  {
    digitalWrite(buzzer,HIGH);
    delay(10000);
    digitalWrite(buzzer,LOW);
    delay(100000);
  }
}}
void buzzerfun()                            //funtion for short 1 beep
{
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
}
