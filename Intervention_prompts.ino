//Dowload and include the Pro Trinket Board from Adafruit, in tools -> Board -> Board Manager -> [BOARD]. For more information consult www.adafruit.com
//Dowload and include the next libraries 
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#define SSD1306_128_32
#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);
//#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

File myFile;
const int  buttonPin1 = 6;    // the pin that the pushbutton is attached to
const int ledPin1 = 3;       // the pin that the LED is attached to
const int  buttonPin2 = A1;// the pin that the pushbutton is attached to
//const int microSD = 10; 
int fsrReading;
int fsrState;
int ledState=1;
int flag =0;
int lastPin1State,lastPin2State;
int pin1State;

void setup() {
pinMode(buttonPin1, INPUT);
 pinMode(ledPin1, OUTPUT);
 pinMode(buttonPin2,INPUT);
pinMode (10, OUTPUT); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
  display.display();

  if (!SD.begin(10)) {  
    return;
  }
 
 myFile = SD.open("Record.txt", FILE_WRITE);
  
  if (myFile) {
    myFile.println(millis()+ 0.9);
    myFile.close();  
  }
}

void loop() { 
   pin1State = digitalRead(buttonPin1);
 if (pin1State == 1 && lastPin1State == 0 )
  {     
    lastPin1State = 1;
    myFile= SD.open("Record.txt", FILE_WRITE);
  if (myFile){
    myFile.println(millis()+ 0.5);
    myFile.close ();
  }
    

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Press hands 60s");
  display.display();
 analogWrite(ledPin1, 63);
  delay(57000);
  digitalWrite(ledPin1,LOW);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(50,1);
  display.println(":D");
  display.display();
  delay(500);
  display.clearDisplay();
  display.display();
  }
  
  
 lastPin1State = 0; 
 
}
  
