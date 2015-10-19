#include <EEPROM.h>
#include "TembooAccount.h"
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>
#include <LiquidCrystal.h>

const int P1 = A3; // Input button P1 on A3
const int P2 = A4; // Input button P2 A4

int buttonState = 0;

//8, A0, 3, 5, 6, 7
 LiquidCrystal lcd(8, A0, 4, 5, 6, 7); 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin(8,2);
   lcd.print("hello");




  // initialize the pushbutton pin as an input:
  pinMode(P1, INPUT);

}

void loop() {
buttonState = digitalRead(P1);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    
  } else {
    // turn LED off:
    Serial.print("clicked ");
   
  }

  

}
