#include <MFRC522.h>
#include <SPI.h>
#include <TM1637Display.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
 int co=1;
 const int CLK = 6; 
const int DIO = 7;
int button =4;
int defbut =2;
int butcount=0;                             //buttoncounter
long int btime=120000;                       //Time for timer  
long int bmin=0,bsec=0;                       
int buzzer=2;                              //buzzer pin 
int buuzertime=2000;
int buzzerdivide=1;                         //buzzer delay time
unsigned long currentmil;                   //track time 
int disp=0 ;
int dsec;
int firstcount=0;
TM1637Display display(CLK, DIO);
void buzzerfun();  
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  pinMode(buzzer,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  display.setBrightness(0x0a); 
//  Serial.println("Scan PICC to see UID and type...");
}

void loop() {

  currentmil=millis();                      //get current time
  if(digitalRead(button)==LOW){
    butcount++;
  }
 
  if(btime+currentmil>currentmil  && butcount>0)   //if button is pressed and btime is zero
  {
    buzzerfun();                             //buzzer single beep function
    delay(1000);          //time differece between 2 beeps
    bmin=btime/60000;                        //conversion to minutes
    bsec=btime-bmin*60000;
    dsec=bsec/1000;
    disp=bmin*100+dsec; //conversion to secconds
    if(bsec==30000||(bmin==0 && bsec==59000)||(bmin==0 && bsec==10000)||(bmin==0 && bsec==7000)||(bmin==0 && bsec==5000)||(bmin==0 && bsec==3000)||(bmin==0 && bsec==1000))    //time at which buzzer freq increases
    buzzerdivide++;                          
    btime=btime-1000;
                       //time reduces every second
    display.showNumberDec(disp);
    while( mfrc522.PICC_IsNewCardPresent()){
      display.showNumberDec(co);
      co++;
//      delay(1000);
      
    }

    
    if(co>10)
    btime=0;
//    else
//    co=0;
  }
   if(btime==0)
  {
    digitalWrite(buzzer,HIGH);
    delay(10000);
    digitalWrite(buzzer,LOW);
    delay(100000);
  }
  
//   Look for new cards
//  if ( mfrc522.PICC_IsNewCardPresent()) {
//    Serial.print("Defuse : ");
//    Serial.print(count);
//    count++;
//    return;
//  }

}
void buzzerfun()                            //funtion for short 1 beep
{
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
}
