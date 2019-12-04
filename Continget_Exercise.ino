//Dowload and include the Pro Trinket Board from Adafruit, in tools -> Board -> Board Manager -> [BOARD]. For more information consult www.adafruit.com
//Dowload and include the next libraries 
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//This code is essential for the correct functioning of the display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
File myFile;

//This pins are the same that in the diagram of the connection.
const int  button = 5; // pin that the pushbutton is attached to
const int vibrating = 6; //pin that the vibrating motor is attached to
const int  fsr = A0;//pin that the force-sensitive sensor is attached to
int fsrReading;
int fsrState;
int ledState=1;
int lastPin1State,lastPin2State;
int pin1State;
 
void setup() {
pinMode(button, INPUT);
pinMode(vibrating, OUTPUT);
pinMode(fsr,INPUT);
pinMode (10, OUTPUT); 
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
display.clearDisplay();
display.display();

//This past create the file in the micro SD and start the record. 
  if (!SD.begin(10)) {return;}  
 myFile = SD.open("Record.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(millis()+ 0.9);
    myFile.close();
  }
}

void loop() {
   pin1State = digitalRead(button);
  fsrReading=analogRead(fsr);
  
 if (pin1State == 1 && lastPin1State == 0 )
  {
    analogWrite(vibrating, 63);      
  lastPin1State = 1;
  
  // Text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Press the sensor");
  display.display();

  //Record the time and response in the micro SD
  myFile= SD.open("Record.txt", FILE_WRITE);
  if (myFile){
    myFile.println(millis()+ 0.1);
    myFile.close ();
  } 
  }
//  
 if ( fsrReading > 750){ 
     digitalWrite(vibrating, LOW);
      lastPin1State = 0;   
//Record the time and press to force sensor
      myFile= SD.open("Record.txt", FILE_WRITE);    
  if (myFile){  
    myFile.println(millis()+ 0.5);
    myFile.close ();
  } 
  display.clearDisplay();
   display.display();  
  }
delay(100); 
}
  

