int button =13;                             //button for start of timer
int butcount=0;                             //buttoncounter
long int btime=120000;                       //Time for timer  
long int bmin=0,bsec=0;                       
int buzzer=12;                              //buzzer pin 
int buuzertime=2000;
int buzzerdivide=1;                         //buzzer delay time
unsigned long currentmil;                   //track time  
void setup() {
  Serial.begin(9600); 
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT);
}

void loop() {
  currentmil=millis();                      //get current time
  if(digitalRead(button)==HIGH)
  butcount=1;
  if(btime+currentmil>currentmil  && butcount==1)   //if button is pressed and btime is zero
  {
    buzzerfun();                             //buzzer single beep function
    delay(buuzertime/buzzerdivide);          //time difference between 2 beeps
    bmin=btime/60000;                        //conversion to minutes
    bsec=btime-bmin*60000;                   //conversion to secconds
    if(bsec==30000||(bmin==0 && bsec==59000)||(bmin==0 && bsec==10000)||(bmin==0 && bsec==7000)||(bmin==0 && bsec==5000)||(bmin==0 && bsec==3000)||(bmin==0 && bsec==1000))    //time at which buzzer freq increases
    buzzerdivide++;                          
    btime=btime-1000;                        //time reduces every second
    Serial.print(bmin);
    Serial.print(" : ");
    Serial.print(bsec);
    Serial.println("");
  } 
}
void buzzerfun()                            //funtion for short 1 beep
{
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
}
  
  
