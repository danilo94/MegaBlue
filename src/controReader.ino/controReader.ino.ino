#include <SoftwareSerial.h>
#include <SegaController.h>


SoftwareSerial bluetooth(11, 10); // RX, TX
SegaController controller(7, 2, 3, 4, 5, 6, 8);
word currentState=0;
word lastState=0;
bool flagZero = false;
void setup() {
  Serial.begin(115200);
  bluetooth.begin(9600);
  // put your setup code here, to run once:
  
}

void loop() {
  currentState = controller.getState();
  sendState();
  delay(100);
}


void sendState()
{
  byte message=0;
  if (currentState&SC_BTN_UP){
    message+=1;
  }
   if (currentState&SC_BTN_DOWN){
    message+=2;
  }
    if (currentState&SC_BTN_LEFT){
    message+=4;
  }
    if (currentState&SC_BTN_RIGHT){
    message+=8;
  }
    if (currentState&SC_BTN_START){
    message+=16;
  }
    if (currentState&SC_BTN_A){
    message+=32;
  }
    if (currentState&SC_BTN_B){
    message+=64;
  }
    if (currentState&SC_BTN_C){
    message+=128;
  }
  if (message>0){
      Serial.println(message);
      bluetooth.write(message);
      flagZero=false;  
  }
  else{
    if (flagZero==false){
      bluetooth.write(message);
      flagZero=true;
    }
  }

  
}
