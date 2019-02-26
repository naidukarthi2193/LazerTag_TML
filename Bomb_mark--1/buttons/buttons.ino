int but1=11;
int but2=6;
int but3=7;
unsigned long int but1mills=0,but2mills=0,but3mills=0;
int choice=2;
int flag=0;
void setup() {
  Serial.begin(9600);
  pinMode(but1,INPUT);
int led=8;
  pinMode(but2,INPUT);
  pinMode(but3,INPUT);
  pinMode(led,OUTPUT);
  

}

void loop() {
  if(digitalRead(but1)==HIGH)
  {
  but1mills=millis();
  Serial.print("1 presed");
  }
  if(digitalRead(but2)==HIGH)
  {
    but2mills=millis();
    Serial.print("2 pressed");
  }
  if(digitalRead(but3)==HIGH){
  but3mills=millis();
  Serial.print("3 pressed");  
  }
  
  switch(choice)
  {
    case 1:
    if(but3mills>but2mills && but2mills>but1mills)
      flag=1;
    break;
    case 2:
    if(but2mills>but1mills && but1mills>but3mills)
      flag=1;
      break;
    case 3:
    if(but3mills>but1mills && but1mills>but2mills)
      flag=1;
      break;
      case 4:
    if(but1mills>but3mills && but3mills>but2mills)
      flag=1;
      break;
    default:
    Serial.print("flag not set");
    flag=0;
    break;
  }
  if(flag)
  {
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
  }



  


  
  // put your main code here, to run repeatedly:

}
