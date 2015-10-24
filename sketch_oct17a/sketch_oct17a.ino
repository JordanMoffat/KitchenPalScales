#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account information
  

const int input1 = A1;
const int input2 = A5;

const int P1 = A3; // Input button P1 on A3
const int P2 = A4; // Input button P2 A4

float Calibration = 0;
float finalnum = 0;

byte ethernetMACAddress[] = ETHERNET_SHIELD_MAC;
EthernetClient client;

int numRuns = 1;   // Execution count, so this doesn't run forever
int maxRuns = 10;   // Maximum number of times the Choreo should be executed

int buttonState = 0;
int p2state = 0;

//8, A0, 3, 5, 6, 7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // initialize the pushbutton pin as an input:
  pinMode(1, INPUT);
  pinMode(4, INPUT);

  int inputstate = analogRead(1);

   Serial.print("DHCP:");
  if (Ethernet.begin(ethernetMACAddress) == 0) {
    Serial.println("FAIL");
    while(true);
  }
  Serial.println("OK");
  delay(5000);

  Serial.println("Setup complete.\n");
  Serial.print("Pin A1: " + String((inputstate * (5.0 / 1023))) + "\n");



}

void loop() {
  buttonState = digitalRead(P1);
  p2state = digitalRead(P2);



  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  //
  if (buttonState == HIGH) {
    // turn LED on:

  } else {
    // turn LED off:
    Serial.print("Reading Started.... \n");
    delay(10000);



    int inputstate1 = analogRead(1);

    int test1 = (inputstate1);
    delay(1000);
    int inputstate2 = analogRead(1);
    int test2 = (inputstate2);
    delay(1000);
    int inputstate3 = analogRead(1);
    int test3 = (inputstate3);
    delay(1000);
    int inputstate4 = analogRead(1);
    int test4 = (inputstate4);
    delay(1000);

    float av = ((test1 + test2 + test3 + test4) / 4);
    float cal = (av - Calibration);


    Serial.print("Average = " + String(cal) + "\n");


    int twoinputstate1 = analogRead(1);
    int twotest1 = (twoinputstate1);
    delay(1000);
    int twoinputstate2 = analogRead(1);
    int twotest2 = (twoinputstate2);
    delay(1000);
    int twoinputstate3 = analogRead(1);
    int twotest3 = (twoinputstate3);
    delay(1000);
    int twoinputstate4 = analogRead(1);
    int twotest4 = (twoinputstate4);
    delay(1000);

    float twoav = ((twotest1 + twotest2 + twotest3 + twotest4) / 4);
    float twocal = (twoav - Calibration);
    Serial.print("Average = " + String(twocal) + "\n");

    //wait for 10 seconds to allow readings to settle.
    //do four readings, average them
    //punt readings to parse.

     int threeinputstate1 = analogRead(1);
    int threetest1 = (twoinputstate1);
    delay(1000);
    int threeinputstate2 = analogRead(1);
    int threetest2 = (threeinputstate2);
    delay(1000);
    int threeinputstate3 = analogRead(1);
    int threetest3 = (threeinputstate3);
    delay(1000);
    int threeinputstate4 = analogRead(1);
    int threetest4 = (threeinputstate4);
    delay(1000);

    float threeav = ((threetest1 + threetest2 + threetest3 + threetest4) / 4);
    float threecal = (threeav - Calibration);
    Serial.print("Average = " + String(threecal) + "\n");


     int fourinputstate1 = analogRead(1);
    int fourtest1 = (twoinputstate1);
    delay(1000);
    int fourinputstate2 = analogRead(1);
    int fourtest2 = (fourinputstate2);
    delay(1000);
    int fourinputstate3 = analogRead(1);
    int fourtest3 = (fourinputstate3);
    delay(1000);
    int fourinputstate4 = analogRead(1);
    int fourtest4 = (fourinputstate4);
    delay(1000);

    float fourav = ((fourtest1 + fourtest2 + fourtest3 + fourtest4) / 4);
    float fourcal = (fourav - Calibration);
    Serial.print("Average = " + String(fourcal) + "\n");

    float overall = ((cal + twocal+threecal+fourcal));
    if (overall <= 0) {
      overall = 0;

      Serial.print("Overall Average: " + String((overall)) + "\n");
    } else if (overall > 0) {
      Serial.print("Overall Average: " + String((overall/4)*10) + "\n");
      finalnum = (overall/4)*10;
      Serial.print((overall/4) /500);
    }

    if (numRuns <= maxRuns) {
    Serial.println("Running UpdateObject - Run #" + String(numRuns++));

    TembooChoreo UpdateObjectChoreo(client);

    // Invoke the Temboo client
    UpdateObjectChoreo.begin();

    // Set Temboo account credentials
    UpdateObjectChoreo.setAccountName(TEMBOO_ACCOUNT);
    UpdateObjectChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    UpdateObjectChoreo.setAppKey(TEMBOO_APP_KEY);

    String RESTAPIKeyValue = "4e85Pva8SfFOq8dvBTUfhD20XVUxNpsicoC2wMes";
    UpdateObjectChoreo.addInput("RESTAPIKey", RESTAPIKeyValue);
    String ObjectIDValue = "sBdw9q2dqH";
    UpdateObjectChoreo.addInput("ObjectID", ObjectIDValue);
    String ApplicationIDValue = "fKFcxAML9tqkehYq0UxpMhkjSLIVdZEgIXTNLEtt";
    UpdateObjectChoreo.addInput("ApplicationID", ApplicationIDValue);
    String ObjectContentsValue = "{\n\"weight\":\""+String(finalnum)+"\"\n}";
    UpdateObjectChoreo.addInput("ObjectContents", ObjectContentsValue);
    String ClassNameValue = "scales";
    UpdateObjectChoreo.addInput("ClassName", ClassNameValue);
    // Identify the Choreo to run
    UpdateObjectChoreo.setChoreo("/Library/Parse/Objects/UpdateObject");

    // Run the Choreo; when results are available, print them to serial
    UpdateObjectChoreo.run();

    while(UpdateObjectChoreo.available()) {
      char c = UpdateObjectChoreo.read();
      Serial.print(c);
    }
    UpdateObjectChoreo.close();
  }

  Serial.println("\nWaiting...\n");
  delay(30000); // wait 30 seconds between UpdateObject calls

    //  Serial.print("clicked ");

  }
  if (p2state == HIGH) {


    // turn LED on:

  } else {

    Serial.print("Calibration Started... \n");

    delay(500);

    int cali1 = analogRead(1);
    Serial.print("... \n");

    delay(1000);
    int cali2 = analogRead(1);
    Serial.print("... \n");
    delay(1000);
    int cali3 = analogRead(1);
    Serial.print("... \n");
    delay(1000);
    int cali4 = analogRead(1);
    Serial.print("... \n");
    delay(1000);
    Serial.print("... \n");
    float av = ((cali1 + cali2 + cali3 + cali4) / 4);
    Serial.print("... \n");
  
    Calibration = av;
    Serial.print("... \n");
    Serial.print("calibration finished \n");
    // turn LED off:
     //Serial.print(String(analogRead(1))+"\n");

  }





}
