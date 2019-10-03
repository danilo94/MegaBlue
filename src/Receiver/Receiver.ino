volatile bool flagSetPins=false;
unsigned long tempoPassado=0;
volatile int statusPin = 0;
byte comando =0;

#define SELECT PA12
#define P1 PB3
#define P2 PB4
#define P3 PB5
#define P4 PB6
#define P6 PB7
#define P9 PB8
#define CSN PA2
#define CE PA3
#include <SegaController.h>
byte pins[] ={P1,P2,P3,P4,P6,P9};
byte signals[]={HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};

void setup() {

  Serial.begin(115200);
  Serial1.begin(9600);
  pinMode (SELECT,INPUT_PULLUP);
  pinMode (P1,OUTPUT);
  pinMode (P2,OUTPUT);
  pinMode (P3,OUTPUT);
  pinMode (P4,OUTPUT);
  pinMode (P6,OUTPUT);
  pinMode (P9,OUTPUT);
  digitalWrite(P1,HIGH);
  digitalWrite(P2,HIGH);
  digitalWrite(P3,HIGH);
  digitalWrite(P4,HIGH);
  digitalWrite(P6,HIGH);
  digitalWrite(P9,HIGH);
  attachInterrupt(SELECT,tickCounter,CHANGE);

}

void loop() {
  
  if (Serial1.available()>0){
    comando = Serial1.read();
  }
  
  
  generateSignals();


  unsigned long tempoInicial = millis();
  
}


void generateSignals(){
  noInterrupts();
  if (flagSetPins == true){
    flagSetPins=false;
    if (statusPin==1){
      
    signals[0]=HIGH;
    signals[1]=HIGH;
    signals[2]=LOW;
    signals[3]=LOW;
    if (comando&(1<<6))
      signals[4]=LOW;
    else
      signals[4]=HIGH;
    if (comando&(1<<5))
       signals[5]=LOW;
    else
       signals[5]=HIGH;
    }


    
    else{
    if (comando&(1<<0))
       signals[0]=LOW;
    else
       signals[0]=HIGH;
       
    if (comando&(1<<1))
       signals[1]=LOW;
    else
       signals[1]=HIGH;
       
    if (comando&(1<<2))
       signals[2]=LOW;
    else
       signals[2]=HIGH;
    if (comando&(1<<3))
       signals[3]=LOW;
    else
       signals[3]=HIGH;

    if (comando&(1<<4))
       signals[4]=LOW;
    else
       signals[4]=HIGH;

    if (comando&(1<<5))
       signals[5]=LOW;
    else
       signals[5]=HIGH;
                   
    }
  }
  signalGenerator();
  interrupts();  
}


void signalGenerator(){
  for (int i=0; i<6; i++){
    digitalWrite(pins[i],signals[i]);
  }
  delayMicroseconds(100);
}


void tickCounter(){
  flagSetPins=true;    
  statusPin = digitalRead(PA12);
}

