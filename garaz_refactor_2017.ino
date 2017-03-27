      //pin 2 nieczynny
      //pin 3 nieczynny
      //pin 4 niewiadomo, raczej nic
      //pin 5 lcd change display btn
      //pin 6 terometr dht22 no1
      //pin 7 terometr dht22 no2
      //pin 8 restetPin
      //pin 9 rs485 not buzzer->48 teraz
      //pins 10 rs485 - not double 2
      //pins 11 rs485 - not double 1
      //pins 12 - flash na podejzdzie
      //params 10, 11, 12, 20, 19, 18 , 17, 16
      
      
      #define TIMEOUT     5000
      #define DEST_IP2    "panel.panzpogodna.pl"
      #define DEST_HOST2   "panel.panzpogodna.pl"
      
      //termometr libraries
      #include "DHT.h"
      DHT dht(6, DHT22);
      DHT dht2(7, DHT22);
      DHT dht3(22, DHT22);
      DHT dht4(23, DHT22);
      
      #include <Wire.h>
      #include <Adafruit_Sensor.h>
      #include <Adafruit_BMP085_U.h>
      Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
      
      #include <PCF8574.h>
      PCF8574 expander(0x20);
      PCF8574 expander2(0x21);
      PCF8574 expander3(0x22);
      PCF8574 expander4(0x23);
      PCF8574 expander5(0x24);
      
      #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x21, 16, 2); // 0x27 is the I2C bus address for an unmodified backpack
      
      long index = 0;
      char bufor [60];
      int indexOfSendSequence = 0;
      const int resetPin = 8;
      const int kontraktor_garaz = 34;
      int closeGateButtonState = 1;
      int closeGateButtonLastState = 0;
      long lastDebounceTime = 0;
      const int buttonPin = 5;
      int buttonPushCounter = 0;
      int buttonState = 1;
      int lastButtonState = 1;
      double pressureGlobal;
      int brightnessGlobal;
      double humidityOutsideGlobal;
      double tempOutsideGlobal;
      double humidityGarageGlobal;
      double tempGarageGlobal;
      double humidityPiwnicaGlobal;
      double tempPiwnicaGlobal;
      double humidityPralniaGlobal;
      double tempPralniaGlobal;
      char globalIp[13];
      
      //expand for mega
      
      const int buttonArmedPin = 24;  //przycisk uzbrajania na okno - kontraktor
      const int ledArmedPin =  25;  //lampka sygnalizujaca uzbrojenie kontraktor
      const int kontraktor_1_Switch = 26;   //kontraktor 1 do okna w piwnicy 1
      const int sirenRelay = 27;   //alarm siren relay
      const int resetSwitch = 28;   //resetAllAlarms
      const int buttonArmedAlarmPin = 29;  //przycisk uzbrajania alarmu na czujink ruchu
      const int ledArmedAlarmPin =  30;  //lampka sygnalizujaca uzbrojenie kontraktor
      const int moveDetectorSwitch = 31;   //detektor ruchu
      
      const int kontraktor_2_Switch = 32;   //kontraktor 2 do okna w piwnicy 1
      const int kontraktor_3_Switch = 33;   //kontraktor 1 do okna w piwnicy pod sypialnia
      const int wall_lights_Switch = 35;
      const int kontraktor_wisniowski = 36;   //kontraktor do bramy wisniowki
      
      const int gardenLight_1_Switch = 37;   //kontraktor 2 do okna w piwnicy pod kuchnia
      const int gardenLight_2_Switch = 38;   //kontraktor 2 do okna w piwnicy pod kuchnia
      
      const int ledGarageArmedPin = 39;  //przycisk uzbrajania alarmu na czujink ruchu w garazu
      const int buttonArmedGaragePin = 40;  //przycisk uzbrajania alarmu na czujink ruchu w garazu
      const int sirenRelayGarage = 44;   //alarm siren relay garage
      const int moveDetectorGarageSwitch = 41;   //detektor ruchu w garazu
      
      const int garageDoorSwitch = 43;   //otwieranie drzwi garazowych
      const int gate_1_Switch = 42;   //otwieranie bramy 1
      const int gate_2_Switch = 45;   //otwieranie bramy 2
      
      const int buzzer = 48;
      const int podjazdLightsRelay = 47;   //wlaczenie swiatel sciennych na podjezdzie relay
      //const int free = 46;   //
      
      int buttonArmedCounter = 0;
      int buttonArmedState = 1;
      int lastButtonArmedState = 1;
      
      int buttonArmedAlarmCounter = 0;
      int buttonArmedAlarmState = 1;
      int lastButtonArmedAlarmState = 1;
      
      int buttonArmedGarageCounter = 0;
      int buttonArmedGarageState = 1;
      int lastButtonArmedGarageState = 1;
      
      int contractor_1_Counter = 0;
      int contractor_1_State = 1;
      int lastContractor_1_State = 1;
      
      int contractor_2_Counter = 0;
      int contractor_2_State = 1;
      int lastContractor_2_State = 1;
      
      int contractor_3_Counter = 0;
      int contractor_3_State = 1;
      int lastContractor_3_State = 1;
      
      // int contractor_4_Counter = 0;
      // int contractor_4_State = 1;
      //int lastContractor_4_State = 1;
      
      // int contractor_5_Counter = 0;
      // int contractor_5_State = 1;
      // int lastContractor_5_State = 1;
      
      // int contractor_6_Counter = 0;
      // int contractor_6_State = 1;
      // int lastContractor_6_State = 1;
      
      int gardenLight_1_Counter = 1;
      int gardenLight_1_State = 1;
      int lastGardenLight_1_State = 1;
      
      int gardenLight_2_Counter = 1;
      int gardenLight_2_State = 1;
      int lastGardenLight_2_State = 1;
      
      int wall_lights_Switch_Counter = 1;
      int wall_lights_Switch_State = 1;
      int lastWall_lights_SwitchState = 1;
      
      
      //int wisniowskiKontraktorState = 0;
      int wisniowskiKontraktorLastState = 1;
      
      
      int garageDoor_State = 1;
      int lastGarageDoor_State = 1;
      
      int gate_1_State = 1;
      int lastGate_1_State = 1;
      
      // int gate_2_State = 1;
      // int lastGate_2_State = 1;
      //brama wjazdowa double click
      long buttonTimer = 0;
      long longPressTime = 1000;
      boolean buttonActive = false;
      boolean longPressActive = false;
      
      boolean onePress = false;
      boolean dev = false;
      int resetValue;
      long sendFrequency;
      
      int resetState = 0;
      int moveDetectorState = 0;
      int moveDetectorStateGarage = 0;
      
      boolean garageArmed = false;
      boolean sendNotification = true;
      //boolean remoteReset=false;
      boolean systemHasLaunched = false;
      //============2.0=================
      #include <SoftwareSerial.h>
      #include <SPI.h>
      //#include <DS1302.h>
      #include <SD.h>
      
      File myFile;
      //485
      #define SSerialRX        10  //Serial Receive pin
      #define SSerialTX        11  //Serial Transmit pin
      #define SSerialTxControl 9   //RS485 Direction control
      #define RS485Transmit    HIGH
      #define RS485Receive     LOW
      SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX
      /*-----( Declare Variables )-----*/
      int byteReceived;
      String message;
      
      char tempCharArr[20];
      int transmissionType = 0;
      byte tempIndex = 0;
      String paramString;
      
      
      
      //DS1302
      //DS1302 rtc(2, 3, 4);    // Change the pins here if you want
      
      
      
      
      //sim800L
      enum _parseState {
        PS_DETECT_MSG_TYPE,
        PS_IGNORING_COMMAND_ECHO,
        PS_READ_CMTI_STORAGE_TYPE,
        PS_READ_CMTI_ID,
        PS_READ_CMGR_STATUS,
        PS_READ_CMGR_NUMBER,
        PS_READ_CMGR_SOMETHING,
        PS_READ_CMGR_DATE,
        PS_READ_CMGR_CONTENT
      };
      
      byte state = PS_DETECT_MSG_TYPE;
      char buffer[80];
      byte pos = 0;
      int lastReceivedSMSId = 0;
      boolean validSender = false;
      
      boolean gateStanChange = false;
      
      void resetBuffer() {
        memset(buffer, 0, sizeof(buffer));
        pos = 0;
      }
      
      
      //===============
      
      
      
      
      void setup() {
      
        digitalWrite(resetPin, HIGH); //We need to set it HIGH immediately on boot
        pinMode(resetPin, OUTPUT);
      
        Serial.begin(9600);
        Serial1.begin(115200);
      
        Serial1.setTimeout(TIMEOUT);
        delay(2000);
      
      
      
        //==========2.0==================
      
        //sim 800l
        delay(2000);
        Serial2.begin(9600);
        Serial2.setTimeout(TIMEOUT);
        delay(1000);
        Serial2.write("AT+CMGF=1\r\n");
        delay(1000);
        Serial.println("serialSIM800 Setup Complete!");
        delay(1000);
        //   respondSMS(0);
      
        //485
        delay(500);
        pinMode(SSerialTxControl, OUTPUT);
        digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver
        RS485Serial.begin(9600);   // set the data rate
      
        /*
          delay(500);
          // SD
          Serial.print("Initializing SD card...");
          if (!SD.begin(5)) {
           Serial.println("initialization failed!");
           return;
          }
          Serial.println("initialization done.");
      
      
          delay(500);*/
        //expander3.begin();
        //expander4.begin();
        //expander5.begin();
      
      
        delay(500);
      
        //====================
      
        pinMode(13, OUTPUT);
        digitalWrite(13, LOW);
      
        //change lcd display button no 5
        pinMode(buttonPin, INPUT);
      
        //garage close gate kontractor no.34
        pinMode(kontraktor_garaz, INPUT);
      
        //single relay module
        pinMode(12, OUTPUT);
        digitalWrite(12, HIGH);
      
        //2 relay module
        pinMode(50, OUTPUT);
        digitalWrite(50, LOW);
      
        pinMode(52, OUTPUT);
        digitalWrite(52, LOW);
      
      
        //-----------------expand for mega
      
      
        pinMode(ledArmedPin, OUTPUT);
        pinMode(buttonArmedPin, INPUT);
      
        pinMode(sirenRelay, OUTPUT);
        digitalWrite(sirenRelay, HIGH);
      
        pinMode(kontraktor_1_Switch, INPUT);
        pinMode(kontraktor_2_Switch, INPUT);
        pinMode(kontraktor_3_Switch, INPUT);
        //pinMode(kontraktor_4_Switch, INPUT);
        pinMode(kontraktor_wisniowski, INPUT);

        
        pinMode(wall_lights_Switch, INPUT);
      
        pinMode(gardenLight_1_Switch, INPUT);
        pinMode(gardenLight_2_Switch, INPUT);
      
        pinMode(garageDoorSwitch, INPUT);
        pinMode(gate_1_Switch, INPUT);
        pinMode(gate_2_Switch, INPUT);
      
        pinMode(resetSwitch, INPUT);
      
        pinMode(ledArmedAlarmPin, OUTPUT);
        pinMode(buttonArmedAlarmPin, INPUT);
        pinMode(moveDetectorSwitch, INPUT);
      
        pinMode(ledGarageArmedPin, OUTPUT);
        digitalWrite(ledGarageArmedPin, LOW);
        pinMode(buttonArmedGaragePin, INPUT);
        digitalWrite(buttonArmedGaragePin, LOW);
      
        pinMode(sirenRelayGarage, OUTPUT);
        digitalWrite(sirenRelayGarage, HIGH);
      
        pinMode(moveDetectorGarageSwitch, INPUT);
      
        //---------end of expand for mega-------------
        pinMode(podjazdLightsRelay, OUTPUT);
        digitalWrite(podjazdLightsRelay, HIGH);
        bmp.begin();
        //Serial.println("BMP 180 works");
      
        //4 relay module
        expander.begin();
        expander.write(0, HIGH);
        expander.write(1, HIGH);
        expander.write(2, HIGH);
        expander.write(3, HIGH);
      
        //expander 2 dla lcd
        expander2.begin();
      
        lcd.init();
        displayDataLcd(" Pan z Pogodna", "    Wita !");
      
        //termometr
        dht.begin();
        dht2.begin();
        dht3.begin();
        dht4.begin();
      
        delay(1000);
      
        if (!dev) {
      
          if (wyslij("AT+RST", "OK", 200))
            Serial.println("Reset esp8266");
      
          while (!wyslij("AT", "OK", 200)) {
            Serial.println("error on esp8266");
            delay(1000);
          }
      
          delay(1000);
      
          wyslij("AT+CIPMODE=0", "OK", 200);
          Serial.println("CIPMODE - OK!");
      
          delay(1000);
      
          wyslij("AT+CIPMUX=1", "OK", 200);
          Serial.println("CIPMUX - OK!");
      
          //temp
          wyslij("AT+CWMODE=1", "OK", 500);
          //Serial.println("AT+CWMODE=3");
      
          wyslij("AT+CWJAP=\"magda\",\"12345678\"", "OK", 5000);
          Serial.println("Polaczono z siecia!");
      
          wyslij("AT+CIPSERVER=1,80", "OK", 5000);
          Serial.println("Uruchomiono serwer :)");
      
          getIp();
          resetValue = 75;
        } else {
          resetValue = 750;
        }
        // index=59500;
        index = 119500;
        buzz(1, 2000);
      
      }
      
      
      void loop() {
      
      
        while (Serial2.available()) {
          parseATText(Serial2.read());
          //Serial.write(Serial2.read());
        }
      
      
        /*
          if (Serial2.available()) {
            Serial.write(Serial2.read());
          }
          if (Serial.available()) {
            Serial2.write(Serial.read());
          }
        */
      
        //==========2.0=====================
      
        if (RS485Serial.available()) {
          //byteReceived = RS485Serial.read()-48;    // Read received byte
          byteReceived = RS485Serial.read();    // Read received byte
          // Serial.write(byteReceived);        // Show on Serial Monitor
      
          message = "";
          onePress = false;
      
          if (byteReceived) {
      
            if (byteReceived == 'a') {
              for (int i = 0; i < sizeof(tempCharArr); ++i) {
                tempCharArr[i] = (char)0;
              }
              tempIndex = 0;
      
            }
      
            if (byteReceived != 'a' && byteReceived != 'b') {
              tempCharArr[tempIndex] = byteReceived;
              tempIndex++;
      
            } else if (byteReceived == 'b') {
              String paramString(tempCharArr);
      
              if (paramString == "0") { //get lights states
                readStates("light");
      
              } else if (paramString == "1") { //set podjazd lights
      
                digitalWrite(podjazdLightsRelay, !digitalRead(podjazdLightsRelay));
                readStates("light");
      
              } else if (paramString == "2") { //set ogrod lights 1
      
                digitalWrite(52, !digitalRead(52));
                readStates("light");
      
              } else if (paramString == "3") { //set ogrod lights 2
      
                digitalWrite(50, !digitalRead(50));
                readStates("light");
      
              } else if (paramString == "4") { //garaz flash
      
                if (!onePress) {
                  onePress = true;
                  flashGarageLights();
                  readStates("light");
                }
      
              } else if (paramString == "5") { //sypailania flash
      
                if (!onePress) {
                  onePress = true;
                  flashSypialniaLights();
                  readStates("light");
                }
      
              } else if (paramString == "6") { //obchod lights
      
                if (!onePress) {
                  onePress = true;
                  flashSypialniaLights();
                  //delay(1000);
                  flashGarageLights();
                  readStates("light");
                }
      
              } else if (paramString == "7") { //get gates state
      
                readStates("gate");
      
              } else if (paramString == "8") { //toggle brama wjazdowa
      
                if (!onePress) {
                  onePress = true;
                  moveBramaWjazdowa();
                  readStates("gate");
                }
      
              } else if (paramString == "9") { //toggle brama garazowa
      
                if (!onePress) {
                  onePress = true;
                  moveGarageGate();
                  readStates("gate");
                }
      
              } else if (paramString == "10") { //toggle brama wjazdowa i brama garazowa
      
                if (!onePress) {
                  onePress = true;
          
                  moveGarageGate();
                  delay(1000);
                  moveBramaWjazdowa(); 

                  readStates("gate");
                }
      
      
              } else if (paramString == "11") { // get all alarms
      
                readStates("alarm");
      
              } else if (paramString == "12") { //alarm okna w piwnicy
      
                readStates("alarm");
      
              } else if (paramString == "13") { // alarm w piwnicy
      
                readStates("alarm");
      
              } else if (paramString == "14") {// alarm w garazu
      
                if (!onePress) {
      
                  onePress = true;
      
                  if (!garageArmed) {
      
                    garageArmed = true;
                    digitalWrite(ledGarageArmedPin, HIGH);
      
                  } else {
      
                    if (digitalRead(sirenRelayGarage) == HIGH) {//off armed alarm when siren is not working
                      digitalWrite(ledGarageArmedPin, LOW);
                      garageArmed = false;
                      buttonArmedGarageCounter = 0;
                    }
      
                  }
                  delay(100);
                  readStates("alarm");
      
                }
      
              } else if (paramString == "15") { // get siren state
      
                if (!onePress) {
      
                  onePress = true;
      
                  readStates("napad");
                }
      
              } else if (paramString == "16") { //wlacz/wylacz syrene i lampy w ogrodzie - NAPAD
      
                if (!onePress) {
      
                  onePress = true;
      
                  digitalWrite(sirenRelayGarage, !digitalRead(sirenRelayGarage));
                  delay(100);
      
                  if (digitalRead(sirenRelayGarage) == LOW) { //gdy zalaczona syrena odpal lampy ogrodowe i flash lights
      
                    digitalWrite(50, 1);
                    digitalWrite(52, 1);
                    digitalWrite(podjazdLightsRelay, LOW);
                    delay(100);
      
                    flashSypialniaLights();
                    //delay(50);
                    flashGarageLights();
      
                  } else {
                    digitalWrite(50, 0);
                    digitalWrite(52, 0);
                    digitalWrite(podjazdLightsRelay, HIGH);
                  }
      
                  readStates("napad");
                }
      
              } else if (paramString == "17") { //refresh data
      
                if (!onePress) {
      
                  onePress = true;
                  delay(100);
                  pushDataToHomeArduino();
                  delay(100);
                  readStates("lights");
                }
              } else if (paramString == "18") { //reset all alarms
      
                if (!onePress) {
      
                  onePress = true;
                  resetAlarms();
      
                  readStates("napad");
                }
              } else if (paramString == "19") {
      
                if (!onePress) {
      
                  onePress = true;
                  //resetAlarms();
      
                  respondSMS(0);
                }
      
              } else if (paramString == "20") { //notification ruch bramy garazowej
      
                if (!onePress) {
      
                  onePress = true;
                  respondSMS(120);
                }
      
              } else if (paramString == "21") { //notification ruch bramy wjazdowej
      
                if (!onePress) {
      
                  onePress = true;
                  respondSMS(121);
                }
      
              } else if (paramString == "22") { // brama wjazdowej na podworko
      
                if (!onePress) {
      
                   onePress = true;
                   moveBramaPodworko();
                   readStates("gate");
                 
                }
      
              }
            }
          }
      
        }
      
        //=======================================
      
        //garaz kontraktor
        int readingGarageKontraktor = digitalRead(kontraktor_garaz);
        if (readingGarageKontraktor != closeGateButtonLastState) {
          if (readingGarageKontraktor == HIGH) {
      
            digitalWrite(podjazdLightsRelay, HIGH);
            registerBramaMovement("close", "yes", "garaz");
      
          } else {
      
            //brightnessGlobal=3;
            if (brightnessGlobal < 3) {
              digitalWrite(podjazdLightsRelay, LOW);
              delay(500);
              flashGarageLights();
            }
            registerBramaMovement("close", "no", "garaz");
          }
        }
        closeGateButtonLastState = readingGarageKontraktor;
      
      
      
        //wisniowski kontraktor
        int readingWisniowskiKontraktor = digitalRead(kontraktor_wisniowski);
        if (readingWisniowskiKontraktor != wisniowskiKontraktorLastState) {
          if (readingWisniowskiKontraktor == HIGH) {
            
            registerBramaMovement("close", "yes", "wisniowski");
          } else {
            
            registerBramaMovement("close", "no", "wisniowski");
          }
        }
        wisniowskiKontraktorLastState = readingWisniowskiKontraktor;
      
      
      
      
        if (!dev) {
          //receiver pins numbers
          while (Serial1.available() > 0)
          {
      
            if (Serial1.find("+IPD,")) {
      
              delay(1000);
      
              Serial1.find("pin=");
              int connectionId = 0;
              int pinNumber = (Serial1.read() - 48) * 10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
              pinNumber += (Serial1.read() - 48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
      
              String webpage ;
              webpage += "HTTP/1.1 200 OK\r\n";
              webpage += "Content-Type: text/html\r\n";
              webpage += "Access-Control-Allow-Origin: *\r\n\r\n";
              webpage += "<!DOCTYPE HTML>\r\n<html>\r\n";
      
              if (pinNumber == 12) { //flash na podejzdzie
      
                flashGarageLights();
                webpage += "ok";
      
              } else if ( pinNumber == 10) { //one of two in doble relay switch ogrodowe
      
                digitalWrite(52, !digitalRead(52)); // toggle pin
                if (digitalRead(52) == 1 ) {
                  webpage += "ok";
                } else {
                  webpage += "ok";
                }
      
              } else if (pinNumber == 11 ) { //one of two in doble relay switch ogrodowe
      
                digitalWrite(50, !digitalRead(50)); // toggle pin
                if (digitalRead(50) == 1 ) {
                  webpage += "ok";
                } else {
                  webpage += "ok";
                }
      
              } else if (pinNumber == 20 ) { //switch both relays at one time//ogrodowe
      
                if (digitalRead(50) == 1 && digitalRead(52) == 1) {
                  digitalWrite(50, 0);
                  digitalWrite(52, 0);
                  webpage += "ok";
                } else if (digitalRead(50) == 1 || digitalRead(52) == 1) {
                  digitalWrite(50, 0);
                  digitalWrite(52, 0);
                  webpage += "ok";
                } else if (digitalRead(50) == 0 || digitalRead(52) == 0) {
                  digitalWrite(50, 1);
                  digitalWrite(52, 1);
                  webpage += "ok";
                }
      
              } else if (pinNumber == 19 ) { //1 switch of 4 switch module// swiatlo na tarasie
      
                flashSypialniaLights();
                webpage += "ok";
      
              } else if (pinNumber == 18 ) { //1 switch of 4 switch module// barama wisniowski 1 - główna
      
                moveBramaPodworko();
                webpage += "ok";
      
              } else if (pinNumber == 17 ) { //1 switch of 4 switch module// barama garazowa
      
                moveGarageGate();
                webpage += "ok";
      
              } else if (pinNumber == 16 ) { //1 switch of 4 switch module barama wisniowski 2 - moja
      
                moveBramaWjazdowa();
                webpage += "ok";
      
      
              } else if (pinNumber == 15 ) { //wall lights toggle
      
                digitalWrite(podjazdLightsRelay, !digitalRead(podjazdLightsRelay));
                webpage += "ok";
      
      
              } else if (pinNumber == 14 ) { //obchod garaz & sypialnia
      
                flashSypialniaLights();
                //delay(100);
                flashGarageLights();
      
                webpage += "ok";
      
      
              } else if (pinNumber == 13 ) { //free
      
                webpage += "ok";
      
              }
              webpage += "</html>\n";
      
              sprintf(bufor, "AT+CIPSEND=%d,%d", connectionId, webpage.length());
              if (wyslij(bufor, ">", 200))
                Serial.println("Wysylanie");
              if (wyslij(webpage, "OK", 200))
                //Serial.println("Wyslano");
      
                //sprintf(bufor,"AT+CIPCLOSE=%d",connectionId);
                if (wyslij("AT+CIPCLOSE=0", "OK", 200))
                  Serial.println("Zamknieto");
      
            }
          }
        }
      
        //expand for mega 17.05.2016
      
        /*
          //check 1st contarctor state and send it to sql
          contractor_1_State = digitalRead(kontraktor_1_Switch);
          if (contractor_1_State != lastContractor_1_State) {
            if (contractor_1_State == LOW) {
              contractor_1_Counter = 1;
            }else{
              contractor_1_Counter = 0;
            }
            lastContractor_1_State = contractor_1_State;
            sendContractorState("1",String(contractor_1_Counter));
          }
        */
      
      
        // gardenlight_1 switch
        gardenLight_1_State = digitalRead(gardenLight_1_Switch);
        if (gardenLight_1_State != lastGardenLight_1_State) {
          if (gardenLight_1_State == HIGH) {
            gardenLight_1_Counter++;
          }
          lastGardenLight_1_State = gardenLight_1_State;
          if (gardenLight_1_Counter % 2 == 0) {
            digitalWrite(52, HIGH); // toggle lights 1 in garden pin
          } else {
            digitalWrite(52, LOW); // toggle lights 1 in garden pin
          }
        }
      
      
        // gardenlight_2 switch
        gardenLight_2_State = digitalRead(gardenLight_2_Switch);
        if (gardenLight_2_State != lastGardenLight_2_State) {
          if (gardenLight_2_State == HIGH) {
            gardenLight_2_Counter++;
          }
          lastGardenLight_2_State = gardenLight_2_State;
          if (gardenLight_2_Counter % 2 == 0) {
            digitalWrite(50, HIGH); // toggle lights 2 in garden pin
          } else {
            digitalWrite(50, LOW); // toggle lights 2 in garden pin
          }
        }
      
      
        //wall_light switch
        wall_lights_Switch_State = digitalRead(wall_lights_Switch);
        if (wall_lights_Switch_State != lastWall_lights_SwitchState) {
          if (wall_lights_Switch_State == HIGH) {
            wall_lights_Switch_Counter++;
          }
          lastWall_lights_SwitchState = wall_lights_Switch_State;
          buzz(1, 500);
          if (wall_lights_Switch_Counter % 2 == 0) {
            digitalWrite(podjazdLightsRelay, LOW); // toggle lights on wall
          } else {
            digitalWrite(podjazdLightsRelay, HIGH); // toggle lights on wall
          }
        }
      
      
      
        //on/off gate 1 door relay
        gate_1_State = digitalRead(gate_1_Switch);//brama podworko switch
        if (gate_1_State != lastGate_1_State) {
          if (gate_1_State == HIGH) {
            buzz(1, 500);
            // Serial.println("nigdy nie zaluwaze tez wiadomosci");
            moveBramaPodworko();
          }
        }
        lastGate_1_State = gate_1_State;
      
      
      
      
        //on/off gate 2 door relay
        //wisniowki gate moja

        //double click on switch to brama delay
        if (digitalRead(gate_2_Switch) == HIGH) {
          if (buttonActive == false) {
            buttonActive = true;
            buttonTimer = millis();
          }
          if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {
            longPressActive = true;
            buzz(2, 500);
            //poczekaj 15 sekund zamin zamknisz brame
            delay(15000);
            moveBramaWjazdowa();
          }
      
        } else {
          if (buttonActive == true) {
            if (longPressActive == true) {
              longPressActive = false;
            } else {
              buzz(1, 500);
              moveBramaWjazdowa();
            }
            buttonActive = false;
          }
        }

        //on/off garage door relay
        garageDoor_State = digitalRead(garageDoorSwitch);
        if (garageDoor_State != lastGarageDoor_State) {
          if (garageDoor_State == HIGH) {
            buzz(1, 500);
            delay(2000);
            moveGarageGate();
          }
        }
        lastGarageDoor_State = garageDoor_State;
      
      
      
        //uzbrajanie alarmu w garazu
        buttonArmedGarageState = digitalRead(buttonArmedGaragePin);
        if (buttonArmedGarageState != lastButtonArmedGarageState) {
          if (buttonArmedGarageState == HIGH) {
            buttonArmedGarageCounter++;
          }      
          if (buttonArmedGarageCounter % 2 == 0) {
            if (digitalRead(sirenRelayGarage) == HIGH) {//off armed alarm when siren is not working
              digitalWrite(ledGarageArmedPin, LOW);
              garageArmed = false;
              buttonArmedGarageCounter = 0;
            }
          } else //pierwsze klikniecie - wlaczenie
            if (digitalRead(moveDetectorGarageSwitch) == LOW) {
              garageArmed = true;
              digitalWrite(ledGarageArmedPin, HIGH);
              delay(100);
            } else {
              delay(100);
              digitalWrite(ledGarageArmedPin, HIGH);
              delay(100);
              digitalWrite(ledGarageArmedPin, LOW);
              delay(100);
              digitalWrite(ledGarageArmedPin, HIGH);
              delay(100);
              digitalWrite(ledGarageArmedPin, LOW);
            }
        }
        lastButtonArmedGarageState = buttonArmedGarageState;


      
        if (garageArmed) {
          moveDetectorStateGarage = digitalRead(moveDetectorGarageSwitch);
          if (moveDetectorStateGarage == HIGH ) {
            digitalWrite(sirenRelayGarage, LOW);
            if (sendNotification) {
              String firedAlarm;
              if (digitalRead(sirenRelayGarage) == LOW) {
                firedAlarm = "1";
              } else {
                firedAlarm = "0";
              }
              message = "e" + String(firedAlarm);
              answerToR485Request(message);
              sendNotification = false;
            }
      
            delay(500);
          }
        }
      
        /*
          //uzbrajania alarmu w piwnicy
          buttonArmedAlarmState = digitalRead(buttonArmedAlarmPin);
          if (buttonArmedAlarmState != lastButtonArmedAlarmState) {
            if (digitalRead(moveDetectorSwitch) == LOW) {
              if (buttonArmedAlarmState == HIGH) {
                buttonArmedAlarmCounter++;
              }
              delay(500);
            } else {
              for (int u = 0; u < 4; u++) {
                digitalWrite(ledArmedAlarmPin, !digitalRead(ledArmedAlarmPin));
                delay(100);
              }
            }
          }
          lastButtonArmedAlarmState = buttonArmedAlarmState;
          if (buttonArmedAlarmCounter % 2 == 0) {
            digitalWrite(ledArmedAlarmPin, LOW);
          } else {
            armDetectorAlarm();
      
          }
      
      
          //uzbrajania alarmu kontraktora
          buttonArmedState = digitalRead(buttonArmedPin);
          if (buttonArmedState != lastButtonArmedState) {
            if (digitalRead(kontraktor_1_Switch) == HIGH) {
              if (buttonArmedState == HIGH) {
                buttonArmedCounter++;
              }
              delay(500);
            } else {
              for (int u = 0; u < 4; u++) {
                digitalWrite(ledArmedPin, !digitalRead(ledArmedPin));
                delay(100);
              }
            }
          }
          lastButtonArmedState = buttonArmedState;
          if (buttonArmedCounter % 2 == 0) {
            digitalWrite(ledArmedPin, LOW);
          } else {
            // digitalWrite(ledArmedPin, HIGH);
            armContractorAlarm();
          }
      
        */
      
        resetState = digitalRead(resetSwitch);
        if (resetState == HIGH) {
          resetAlarms();
        }
      
        //------------end of expand for mega
      
      
        // putton push counter
        buttonState = digitalRead(buttonPin);
        if (buttonState != lastButtonState) {
          if (buttonState == HIGH) {
            if (buttonPushCounter == 13) {
              buttonPushCounter = 0;
            }
            buttonPushCounter++;
      
            switch (buttonPushCounter) {
              case 1:
                displayDataLcd("Cisnienie", String(pressureGlobal) + " hPa");
                break;
              case 2:
                displayDataLcd("Janosc", String(brightnessGlobal) + " / 10");
                break;
              case 3:
                displayDataLcd("Temp. zew", String(tempOutsideGlobal) + " C");
                break;
              case 4:
                displayDataLcd("Wilgotnosc zew", String(humidityOutsideGlobal) + " %");
                break;
              case 5:
                displayDataLcd("Temp. garaz", String(tempGarageGlobal) + " C");
                break;
              case 6:
                displayDataLcd("Wilgotnosc garaz  ", String(humidityGarageGlobal) + " %");
                break;
              case 7:
                displayDataLcd("Temp. piwnica", String(tempPiwnicaGlobal) + " C");
                break;
              case 8:
                displayDataLcd("Wilgotnosc piwnica", String(humidityPiwnicaGlobal) + " %");
                break;
              case 9:
                displayDataLcd("Temp. pralnia", String(tempPralniaGlobal) + " C");
                break;
              case 10:
                displayDataLcd("Wilgotnosc pralnia  ", String(humidityPralniaGlobal) + " %");
                break;
              case 11:
                displayDataLcd("Reset z 75", String(indexOfSendSequence));
                break;
              case 12:
                displayDataLcd("Ip server", String(globalIp));
                break;
              case 13:
                displayDataLcd("Index z 120000", String(index));
                break;
      
            }
      
          }
          delay(50);
        }
        lastButtonState = buttonState;
      
      
      
        //==============2.0============
      
      
        /*
      
          //wykrywania zmiany polozenia bramy
          if (!gateStanChange) {
      
            message = "d" + String(0);
            int messageLen = message.length() + 1;
            char buffer[messageLen];
            message.toCharArray(buffer, messageLen);
            digitalWrite(SSerialTxControl, RS485Transmit);
            RS485Serial.write(buffer);
            delay(100);
            digitalWrite(SSerialTxControl, RS485Receive);
      
            gateStanChange = true;
          }
        */
      
        //=============================
      
      
      
      
        //alternative thread
      
        if (dev) {
          sendFrequency = 60000;
        } else {
          sendFrequency = 119900; //20minut
        }
      
        //sendFrequency=3000;
      
      
        if (index >= sendFrequency) { //10 minut sekund
      
          //jasnosc
          //Serial.println("Jasnosc "+String(jasnosc));
          brightnessGlobal = analogRead(0) / 128;
      
          humidityOutsideGlobal = dht2.readHumidity();
          tempOutsideGlobal = dht2.readTemperature();
      
          humidityGarageGlobal = dht.readHumidity();
          tempGarageGlobal = dht.readTemperature();
      
      
          humidityPiwnicaGlobal = dht3.readHumidity();
          tempPiwnicaGlobal = dht3.readTemperature();
      
          humidityPralniaGlobal = dht4.readHumidity();
          tempPralniaGlobal = dht4.readTemperature();
      
      
      
          if (isnan(tempOutsideGlobal) || isnan(tempGarageGlobal) || isnan(tempPiwnicaGlobal) || isnan(tempPralniaGlobal)) {
            reset();
          }//else{
      
          // Serial.println("temp piwnica " + String(tempPiwnicaGlobal));
          // Serial.println("temp pralnia " + String(tempPralniaGlobal));
      
      
          //pressure
          sensors_event_t event;
          bmp.getEvent(&event);
          //double pressure;
      
          //pressure=event.pressure;
          pressureGlobal = event.pressure;
      
          displayDataLcd("Temp. garaz", String(tempGarageGlobal) + " C");
          buttonPushCounter = 0;
      
      
      
          if (!dev) {
      
            pushDataToHomeArduino();
      
            String cmd = "AT+CIPSTART=1,\"TCP\",\""; cmd += DEST_IP2; cmd += "\",80";
            if (wyslij(cmd, "OK", 200)) {
              Serial.println("AT+CIPSTART=1");
            }
      
            delay(1000);
            Serial1.println("AT+CIPSTATUS=?");
            if (wyslij("AT+CIPSTATUS", "OK", 200)) {
              Serial.println("AT+CIPSTATUS OK");
            }
      
            cmd = "GET /arduinoGate/garazDaneController.php?tO=" + String(tempOutsideGlobal) + "&hO=" + String(humidityOutsideGlobal) + "&tG=" + String(tempGarageGlobal) + "&hG=" + String(humidityGarageGlobal) + "&tP=" + String(tempPiwnicaGlobal) + "&hP=" + String(humidityPiwnicaGlobal) + "&tPr=" + String(tempPralniaGlobal) + "&hPr=" + String(humidityPralniaGlobal) + "&b=" + String(brightnessGlobal) + "&p=" + String(pressureGlobal) + "&ip=" + String(globalIp) + " HTTP/1.1\r\nHost: ";
            // cmd="GET /arduinoGate/garazDaneController.php?hO=70&tG=80 HTTP/1.1\r\nHost: ";
            cmd += DEST_HOST2;
            cmd += ":80\r\n\r\n";
            delay(1000);
      
      
            //Serial.println(cmd);
      
            sprintf(bufor, "AT+CIPSEND=%d,%d", 1, cmd.length());
            if (wyslij(bufor, ">", 200))
              Serial.println("Wysylanie");
            if (wyslij(cmd, "OK", 200))
              Serial.println("Wyslano");
            if (wyslij("AT+CIPCLOSE=1", "OK", 200)) {
              Serial.println("Zamknieto");
              index = 0;
              buzz(3, 2000);
              digitalWrite(13, HIGH);
              systemHasLaunched = true;
            } else {
      
              digitalWrite(13, LOW);
              reset();
      
            }
          }
      
          indexOfSendSequence++;
      
        }
      
        if (indexOfSendSequence == resetValue) {
          reset();
        }
      
        index++;
        delay(10);
      
      }
      
      void pushDataToHomeArduino() {
      
        //Serial.println("push data to home arduino");
        message = "a" + String(int(tempOutsideGlobal)) + "b" + String(int(humidityOutsideGlobal)) + "c" + String(int(pressureGlobal));
      
        //send485Message();
        answerToR485Request(message);
      
      }
      
      void readStates(String area) {
      
        if (area == "light") {
      
          //1.podjazd
          //2.ogrod 1
          //3.ogrod 2
      
          if (digitalRead(podjazdLightsRelay) == LOW) {
            message = "z" + String(1) + String(digitalRead(52)) + String(digitalRead(50));
          } else {
            message = "z" + String(0) + String(digitalRead(52)) + String(digitalRead(50));
          }
      
        } else if (area == "gate") {
      
          //1.brama wjazdowa 
          //2.brama garazowa
          //3. brama na podworko //tymczasowo zawsze 0 bo nie ma kontraktora zainstalowanego

           message = "z" + String(!digitalRead(kontraktor_wisniowski)) + String(!digitalRead(kontraktor_garaz)) + String(0);
      
        } else if (area == "alarm") {
      
          //1. garage move detector alarm
      
          message = "z" + String(garageArmed) + String(0) + String(0);
      
        } else if (area == "napad") {
      
          //1. siren garage
      
          if (digitalRead(sirenRelayGarage) == HIGH) {
            message = "z" + String(0);
          } else {
            message = "z" + String(1);
          }
        }
      
      
        answerToR485Request(message);
      
      
      }
      
      void answerToR485Request(String message) {
      
        delay(100);
        int messageLen = message.length() + 1;
        char buffer[messageLen];
        message.toCharArray(buffer, messageLen);
        digitalWrite(SSerialTxControl, RS485Transmit);  // Enable RS485 Transmit
        RS485Serial.write(buffer);          // Send byte to Remote Arduino
        delay(100);
        digitalWrite(SSerialTxControl, RS485Receive);
      
      }
      
      void writeSd() {
      
        myFile = SD.open("example3.txt", FILE_WRITE);
      
        if (myFile) {
          Serial.print("Writing to example3.txt...");
          myFile.println("testing 1, 2, 3.");
      
          myFile.close();
          Serial.println("done.");
        } else {
      
          Serial.println("error opening example3.txt");
        }
      
        // re-open the file for reading:
        myFile = SD.open("example3.txt");
        if (myFile) {
          Serial.println("example3.txt");
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {
            Serial.write(myFile.read());
          }
          // close the file:
          myFile.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening example3.txt");
        }
      
      
      }
      
      
      
      
      void buzz( int indexBuzz, int frequency) {
      
        for (int i = 0; i < indexBuzz; i++) {
          tone(buzzer, frequency, 200);
          delay(200);
        }
      }
      
      
      
      void reset() {
        systemHasLaunched = false;
        buzz(10, 2000);
        indexOfSendSequence = 0;
      
        String zdalnyReset;
        zdalnyReset = "1";
        message = "f" + String(zdalnyReset);
        answerToR485Request(message);
      
        delay(8000);
      
        digitalWrite(resetPin, LOW);
      }
      
      boolean wyslij(String Komenda_AT, char *Odpowiedz_AT, int czas_czekania) {
        Serial1.println(Komenda_AT);
        delay(czas_czekania);
        while (Serial1.available() > 0) {
          if (Serial1.find(Odpowiedz_AT)) {
            // Serial.println(Serial1.read()-48);
            return 1;
          }
        }
        return 0;
      }


      
      void registerBramaMovement(String action, String state, String gate) {
      
        if (systemHasLaunched) {

          //zmaiana stany bram na ekranie glownym lcd
          if (gate == "garaz") {
            //rs 485 dla ekranu  - stan bramy garazowej
            if (state == "no") {
              message = "d" + String(0);
            } else {
              message = "d" + String(1);
            }
      
          } else if (gate == "wisniowski") {
            //rs 485 dla ekranu  - stan bramy wjazdowej wisniowski
            if (state == "no") {
              message = "g" + String(0);
            } else {
              message = "g" + String(1);
            }
          }
          answerToR485Request(message);


      
          //=====SEND TO SQL=========
      
          String cmd = "AT+CIPSTART=2,\"TCP\",\""; cmd += DEST_IP2; cmd += "\",80";
          if (wyslij(cmd, "OK", 200)) {
            //Serial.println("AT+CIPSTART=1");
          }
      
          delay(1000);
          
          Serial1.println("AT+CIPSTATUS=?");
          if (wyslij("AT+CIPSTATUS", "OK", 200)) {
            Serial.println("AT+CIPSTATUS OK");
          }
          
          if (gate == "garaz") {
            cmd = "GET /arduinoGate/bramaController.php?" + String(action) + "=" + String(state) + " HTTP/1.1\r\nHost: "; cmd += DEST_HOST2; cmd += ":80\r\n\r\n";
          }else if (gate == "wisniowski") {
    
            cmd = "GET /arduinoGate/wisniowskiController.php?" + String(action) + "=" + String(state) + " HTTP/1.1\r\nHost: "; cmd += DEST_HOST2; cmd += ":80\r\n\r\n";
          }
          
          //Serial.println(cmd);
          sprintf(bufor, "AT+CIPSEND=%d,%d", 2, cmd.length());
          if (wyslij(bufor, ">", 200))
            Serial.println("Wysylanie");
          if (wyslij(cmd, "OK", 200))
            Serial.println("Wyslano");
          if (wyslij("AT+CIPCLOSE=2", "OK", 200)) {
            Serial.println("Zamknieto");
            buzz(2, 2000);
          } else {
            digitalWrite(13, LOW);
            reset();
          }
        }
      }
      
      
      
      void displayDataLcd(String lineOne, String lineTwo) {
        lcd.clear();
        int lineOneLength = lineOne.length() + 1;
        char charBuf1[lineOneLength];
        lineOne.toCharArray(charBuf1, lineOneLength) ;
        for (int i = 0; i < lineOneLength - 1; i++) {
          lcd.setCursor(i, 0);
          lcd.print(charBuf1[i]);
        }
        int lineTwoLength = lineTwo.length() + 1;
        char charBuf2[lineTwoLength];
        lineTwo.toCharArray(charBuf2, lineTwoLength) ;
        for (int j = 0; j < lineTwoLength - 1; j++) {
          lcd.setCursor(j, 1);
          lcd.print(charBuf2[j]);
        }
      }
      
      void getIp() {
        String smallIp;
        Serial1.println("AT+CIFSR");
        //Serial.println(Serial1.readString());
        smallIp = Serial1.readString().substring(27, 40);
        //Serial.println(smallIp);
        smallIp.toCharArray(globalIp, 13);
      }
      
      
      
      
      
      //expand mega
      
      
      void armContractorAlarm() {
        if (digitalRead(sirenRelay) == HIGH) {
          contractor_1_State = digitalRead(kontraktor_1_Switch);
        }
        if (contractor_1_State == LOW) {
          digitalWrite(sirenRelay, LOW);
          digitalWrite(ledArmedPin, !digitalRead(ledArmedPin));
          delay(500);
        } else {
          digitalWrite(ledArmedPin, HIGH);
        }
      }
      
      
      void armDetectorAlarm() {
        if (digitalRead(sirenRelay) == HIGH) {
          moveDetectorState = digitalRead(moveDetectorSwitch);
        }
      
        if (moveDetectorState == HIGH) {
          digitalWrite(sirenRelay, LOW);
          digitalWrite(ledArmedAlarmPin, !digitalRead(ledArmedAlarmPin));
          delay(500);
        } else {
          digitalWrite(ledArmedAlarmPin, HIGH);
        }
      }
      
      
      void armDetectorGarageAlarm() {
      
      
      
      }
      
      /*
      void sendContractorState(String number, String state) {
        Serial.println("kontraktor " + number + " = " + state);
      }
      */
      
      
      void resetAlarms() {
        sendNotification = true;
        garageArmed = false;
        buttonArmedCounter = 0;
        buttonArmedAlarmCounter = 0;
        buttonArmedGarageCounter = 0;
        //digitalWrite(moveDetectorStateGarage,LOW);
        digitalWrite(sirenRelay, HIGH);
        digitalWrite(sirenRelayGarage, HIGH);
        digitalWrite(buttonArmedPin, LOW);
        digitalWrite(buttonArmedAlarmPin, LOW);
        digitalWrite(buttonArmedGaragePin, LOW);
        digitalWrite(ledArmedPin, LOW);
        digitalWrite(ledArmedAlarmPin, LOW);
        digitalWrite(ledGarageArmedPin, LOW);
        digitalWrite(kontraktor_1_Switch, LOW);
      
      
      }
      
      
      void flashGarageLights() {

        digitalWrite(12, LOW);
        delay(300);
        digitalWrite(12, HIGH);
      
      }
      
      void flashSypialniaLights() {
        delay(10);
        expander.write(0, 0);
        delay(500);
        expander.write(0, 1);
        delay(10);

      }
      
      void moveGarageGate() {
        expander.toggle(2);
        delay(200);
        expander.toggle(2);
      }
      
      void moveBramaWjazdowa() {
        expander.toggle(3);
        delay(200);
        expander.toggle(3);
      }
      
      void moveBramaPodworko() {
        expander.toggle(1);
        delay(200);
        expander.toggle(1);
      }
      
      
      
      void parseATText(byte b) {
      
        buffer[pos++] = b;
      
        if ( pos >= sizeof(buffer) )
          resetBuffer(); // just to be safe
      
        switch (state) {
          case PS_DETECT_MSG_TYPE:
            {
              if ( b == '\n' )
                resetBuffer();
              else {
                if ( pos == 3 && strcmp(buffer, "AT+") == 0 ) {
                  state = PS_IGNORING_COMMAND_ECHO;
                }
                else if ( pos == 6 ) {
                  if ( strcmp(buffer, "+CMTI:") == 0 ) {
                    Serial.println("Received CMTI");
                    state = PS_READ_CMTI_STORAGE_TYPE;
                  }
                  else if ( strcmp(buffer, "+CMGR:") == 0 ) {
                    Serial.println("Received CMGR");
                    state = PS_READ_CMGR_STATUS;
                  }
                  resetBuffer();
                }
              }
            }
            break;
      
          case PS_IGNORING_COMMAND_ECHO:
            {
              if ( b == '\n' ) {
                //Serial.print("Ignoring echo: ");
                //Serial.println(buffer);
                state = PS_DETECT_MSG_TYPE;
                resetBuffer();
              }
            }
            break;
      
          case PS_READ_CMTI_STORAGE_TYPE:
            {
              if ( b == ',' ) {
                Serial.print("SMS storage is ");
                Serial.println(buffer);
                state = PS_READ_CMTI_ID;
                resetBuffer();
              }
            }
            break;
      
          case PS_READ_CMTI_ID:
            {
              if ( b == '\n' ) {
                lastReceivedSMSId = atoi(buffer);
                Serial.print("SMS id is ");
                Serial.println(lastReceivedSMSId);
                Serial2.print("AT+CMGR=");
                Serial2.println(lastReceivedSMSId);
                state = PS_DETECT_MSG_TYPE;
                resetBuffer();
              }
            }
            break;
      
          case PS_READ_CMGR_STATUS:
            {
              if ( b == ',' ) {
                Serial.print("CMGR status: ");
                Serial.println(buffer);
                state = PS_READ_CMGR_NUMBER;
                resetBuffer();
              }
            }
            break;
      
          case PS_READ_CMGR_NUMBER:
            {
              if ( b == ',' ) {
                Serial.print("CMGR number: ");
                Serial.println(buffer);
                // Uncomment these two lines to check the sender's cell number
                validSender = false;
                if ( strcmp(buffer, "\"+48501986543\",") == 0 )
                  validSender = true;
      
                state = PS_READ_CMGR_SOMETHING;
                resetBuffer();
              }
            }
            break;
      
          case PS_READ_CMGR_SOMETHING:
            {
              if ( b == ',' ) {
                Serial.print("CMGR something: ");
                Serial.println(buffer);
                state = PS_READ_CMGR_DATE;
                resetBuffer();
              }
            }
            break;
      
          case PS_READ_CMGR_DATE:
            {
              if ( b == '\n' ) {
                Serial.print("CMGR date: ");
                Serial.println(buffer);
                state = PS_READ_CMGR_CONTENT;
                resetBuffer();
              }
            }
            break;
      
          case PS_READ_CMGR_CONTENT:
            {
              if ( b == '\n' ) {
                Serial.print("CMGR content: ");
                Serial.print(buffer);
                //delete all msgs
                Serial2.write("AT+CMGD=1,4\r\n");
                if (validSender) {
                  String str(buffer);
                  str.trim();
                  if (str.equals("0")) {
                    respondSMS(0);
                  } else if (str.equals("1")) {
                    respondSMS(1);
                  } else if (str.equals("2")) {
                    respondSMS(2);
                  } else if (str.equals("3")) {
                    respondSMS(3);
                  } else if (str.equals("5")) {
                    respondSMS(4);
                  } else if (str.equals("6")) {
                    respondSMS(5);
                  } else if (str.equals("7")) {
                    respondSMS(6);
                  } else if (str.equals("8")) {
                    respondSMS(7);
                  } else if (str.equals("9")) {
                    respondSMS(8);
                  } else if (str.equals("10")) {
                    respondSMS(9);
                  } else if (str.equals("11")) {
                    respondSMS(10);
                  } else if (str.equals("12")) {
                    respondSMS(11);
                  } else if (str.equals("13")) {
                    respondSMS(12);
                  } else if (str.equals("4")) {//ruch bramy podworkowej
                    respondSMS(13);
                  }
                }
      
                //Serial1.print("AT+CMGD=");
                //Serial1.println(lastReceivedSMSId);
                state = PS_DETECT_MSG_TYPE;
                resetBuffer();
              }
            }
            break;
        }
      }
      
      void send485Message() {
        int messageLen = message.length() + 1;
        char buffer[messageLen];
        message.toCharArray(buffer, messageLen);
        digitalWrite(SSerialTxControl, RS485Transmit); // Enable RS485 Transmit
        RS485Serial.write(buffer); // Send byte to Remote Arduino
        delay(100);
        digitalWrite(SSerialTxControl, RS485Receive);
      }
      
      
      void respondSMS(int request) {
      
        delay(1000);
        Serial2.write("AT+CMGS=\"501986543\"\r\n");
        delay(1000);
      
        if (request == 0) { //test
      
          Serial2.write("0:komendy\r\n1:pogoda\r\n2:garaz\r\n3:status\r\n4:br. podworko\r\n5:br. wjazdowa\r\n6:br. garazowa\r\n7:ruch obu bram\r\n8:sw. obchod\r\n9:sw. podjazdowe\r\n10:sw. ogrod\r\n11:napad\r\n12:reset\r\n13:off system");
      
        } else if (request == 1) { //pogoda
      
          String pogoda = "";
          pogoda = "temperatura powietrza: " + String(tempOutsideGlobal) + " C\r\nwiglotnosc powietrza: " + String(humidityOutsideGlobal) + " %\r\ncisnienie atmosferyczne: " + String(pressureGlobal) + " hPa";
          for (int i = 0; i < pogoda.length(); i++) {
            Serial2.write(pogoda[i]);
          }
      
      
        } else if (request == 2) { // status garaz
      
          String satatusBrmayGarazowej = "";
          if (digitalRead(kontraktor_garaz) == HIGH) {
            satatusBrmayGarazowej = "ZAMKNIETA";
          } else {
            satatusBrmayGarazowej = "OTWARTA";
          }
          delay(200);
          String garaz2 = "";
          garaz2 = "brama garazowa jest " + String(satatusBrmayGarazowej) + "\r\ntemperatura w garazu: " + String(tempGarageGlobal) + " C\r\nwilgotnosc w garazu: " + String(humidityGarageGlobal) + " %";
          for (int i = 0; i < garaz2.length(); i++) {
            Serial2.write(garaz2[i]);
          }
      
        } else if (request == 3) { // status wszystkiego
      
          String satatusBrmayGarazowej = "";
          if (digitalRead(kontraktor_garaz) == HIGH) {
            satatusBrmayGarazowej = "ZAMKNIETA";
          } else {
            satatusBrmayGarazowej = "OTWARTA";
          }


          String satatusBrmayWjazdowej = "";
          if (digitalRead(kontraktor_wisniowski) == HIGH) {
            satatusBrmayWjazdowej = "ZAMKNIETA";
          } else {
            satatusBrmayWjazdowej = "OTWARTA";
          }

      
          String swiatlaNaPodjezdzie = "";
          if (digitalRead(podjazdLightsRelay) == HIGH) {
            swiatlaNaPodjezdzie = "WYLACZONE";
          } else {
            swiatlaNaPodjezdzie = "WLACZONE";
          }
      
          String swiatlaOgrodowe = "";
          if (digitalRead(50) == HIGH || digitalRead(52) == HIGH) {
            swiatlaOgrodowe = "WLACZONE";
          } else {
            swiatlaOgrodowe = "WYLACZONE";
          }
      
          String syrenaStatus = "";
          if (digitalRead(sirenRelayGarage) == LOW ) {
            syrenaStatus = "WLACZONA";
          } else {
            syrenaStatus = "WYLACZONA";
          }
      
          String statusAll = "";
          statusAll = "brama garazowa jest " + String(satatusBrmayGarazowej) + "\r\nbrama wjazdowa jest " + String(satatusBrmayWjazdowej) + "\r\nswiatla na podjezdzie sa " + String(swiatlaNaPodjezdzie) + "\r\nswiatla ogrodowe sa " + swiatlaOgrodowe + "\r\nsyrena jest " + syrenaStatus;
          for (int i = 0; i < statusAll.length(); i++) {
            Serial2.write(statusAll[i]);
          }
      
          delay(200);
      
      
        } else if (request == 4) { //ruch bramy wjazdowej
      
          delay(1000);
          
          String satatusBrmayWjazdowej="";
          if (digitalRead(kontraktor_wisniowski) == HIGH){
            satatusBrmayWjazdowej = "W tej chwili sie OTWIERA";
          } else {
            satatusBrmayWjazdowej = "W tej chwili sie ZAMYKA";
          }
          String wjazd = "";
          wjazd= "ruszono brame WJAZDOWA. "+ satatusBrmayWjazdowej;
          for (int i = 0; i < wjazd.length(); i++){
            Serial2.write(wjazd[i]);
          }

          delay(1000);
          
          moveBramaWjazdowa();
          
        } else if (request == 5) { //ruch bramy garazowa

          delay(1000);
      
          String satatusBrmayGarazowej = "";
          if (digitalRead(kontraktor_garaz) == HIGH) {
            satatusBrmayGarazowej = "W tej chwili sie OTWIERA";
          } else {
            satatusBrmayGarazowej = "W tej chwili sie ZAMYKA";
          }
      
          String garaz = "";
          garaz = "ruszono brame GARAZOWA. " + satatusBrmayGarazowej;
          for (int i = 0; i < garaz.length(); i++) {
            Serial2.write(garaz[i]);
          }
          
          delay(1000);

          moveGarageGate();
          
      
        } else if (request == 6) { // ruch obu bram

          delay(1000);

          String satatusBrmayGarazowej = "";
          if (digitalRead(kontraktor_garaz) == HIGH) {
            satatusBrmayGarazowej = "OTWIERA";
          } else {
            satatusBrmayGarazowej = "ZAMYKA";
          }

          String satatusBrmayWjazdowej="";
          if (digitalRead(kontraktor_wisniowski) == HIGH){
            satatusBrmayWjazdowej = "OTWIERA";
          } else {
            satatusBrmayWjazdowej = "ZAMYKA";
          }
          
      
          String bothGates = "";
          bothGates = "ruszono obie bramy:\r\nGARAZOWA teraz sie " + satatusBrmayGarazowej + "\r\nWJAZDOWA teraz się  "+ satatusBrmayGarazowej;
          for (int i = 0; i < bothGates.length(); i++) {
            Serial2.write(bothGates[i]);
          }

          delay(1000);
          moveGarageGate();
          delay(1000);
          moveBramaWjazdowa();  
  
      
        } else if (request == 7) { //swiatla obchod
      
          flashSypialniaLights();
          //delay(50);
          flashGarageLights();
          Serial2.write("wlaczono tryb obchod!");
      
        } else if (request == 8) { //swiatla podjazd
      
          digitalWrite(podjazdLightsRelay, !digitalRead(podjazdLightsRelay));
          delay(50);
          String swiatlaNaPodjezdzie = "";
          if (digitalRead(podjazdLightsRelay) == HIGH) {
            swiatlaNaPodjezdzie = "WYLACZONE";
          } else {
            swiatlaNaPodjezdzie = "WLACZONE";
          }
      
          String switlaPodjzdowe = "";
          switlaPodjzdowe = "swiatla na podjezdzie sa teraz " + swiatlaNaPodjezdzie;
          for (int i = 0; i < switlaPodjzdowe.length(); i++) {
            Serial2.write(switlaPodjzdowe[i]);
          }
      
      
        } else if (request == 9) { // swiatla ogrod
      
          digitalWrite(50, !digitalRead(50));
          delay(50);
          digitalWrite(52, !digitalRead(52));
      
          String swiatlaOgrodowe = "";
          if (digitalRead(50) == HIGH || digitalRead(52) == HIGH) {
            swiatlaOgrodowe = "WLACZONE";
          } else {
            swiatlaOgrodowe = "WYLACZONE";
          }
      
          String switlaOgr = "";
          switlaOgr = "swiatla ogrodowe sa teraz " + swiatlaOgrodowe;
          for (int i = 0; i < switlaOgr.length(); i++) {
            Serial2.write(switlaOgr[i]);
          }
      
        } else if (request == 10) { // napad
      
          String napadStatus = "";
      
          digitalWrite(sirenRelayGarage, !digitalRead(sirenRelayGarage));
          //delay(100);
      
          if (digitalRead(sirenRelayGarage) == LOW) { //gdy zalaczona syrena odpal lampy ogrodowe i flash lights
      
            napadStatus = "WLACZONY";
            digitalWrite(50, 1);
            digitalWrite(52, 1);
            digitalWrite(podjazdLightsRelay, LOW);
            delay(100);
      
      
            flashSypialniaLights();
            delay(50);
            flashGarageLights();
      
      
          } else {
            napadStatus = "WYLACZONY";
            digitalWrite(50, 0);
            digitalWrite(52, 0);
            digitalWrite(podjazdLightsRelay, HIGH);
          }
      
          String napad = "";
          napad = "napad jest teraz " + napadStatus;
          for (int i = 0; i < napad.length(); i++) {
            Serial2.write(napad[i]);
          }
      
        } else if (request == 11) {
      
          Serial2.write("Rozpoczeto zdalny reset systemu");
          delay(1000);
          String zdalnyReset;
          zdalnyReset = "1";
          message = "f" + String(zdalnyReset);
          answerToR485Request(message);
      
        } else if (request == 12) {
      
          Serial2.write("wylaczono system");
          delay(1000);
          String zdalnyReset;
          zdalnyReset = "2";
          message = "f" + String(zdalnyReset);
          answerToR485Request(message);
      
        } else if (request == 13) {//ruch bramy podworko

          delay(1000);
          
          String satatusBramyPodworko="";
          //if (digitalRead(kontraktor_wisniowski) == HIGH){
           // satatusBramyPodworko = "W tej chwili sie OTWIERA";
          //} else {
          //  satatusBramyPodworko = "W tej chwili sie ZAMYKA";
          //}
          satatusBramyPodworko="RUSZA SIE W KOTRAS STRONE";
          
          String podworko = "";
          podworko= "ruszono brame na PODWORKO. "+ satatusBramyPodworko;
          for (int i = 0; i < podworko.length(); i++){
            Serial2.write(podworko[i]);
          }

          delay(1000);
          moveBramaPodworko();

      
        }  else if (request == 120) { //Notyfikacja - ruch bramy garazowej
      
          Serial2.write("Notyfikacja - ruch bramy garazowej");
      
        }else if (request == 121) { //Notyfikacja - ruch bramy wjazdowej
      
          Serial2.write("Notyfikacja - ruch bramy wjazdowej");
      
        }
      
        delay(1000);
        Serial2.write((char)26);
        delay(1000);
        // Serial.println("SMS has been sent");
      }

