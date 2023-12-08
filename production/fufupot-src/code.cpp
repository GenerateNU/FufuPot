#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
//Declaring pins for red LED and button. Also declaring some info
//for turning LEDs on and off
int pinButton = 8;
int LED = 2;
int blueLED = 7;
int buzzer = 12;
int stateLED = LOW;
int stateButton;
int previous = LOW;
long time = 0;
long debounce = 350;
bool LEDtimer = false;
long timeFunctStarted;
//Pin that is connected to NeoPixel
#define LED_PIN 5
//Number of NeoPixels attached to arduino
#define LED_COUNT 8
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
void setup() {
  //Setup for red LED, blue LED, and button
  pinMode(pinButton, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(9,OUTPUT);
  //Setup for LED strip
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(9600);
  //long millisTime;
}
void loop() {
  //FOR REFRENCE ONLY
  //strip.Color(255,   0,   0) = Green
  //strip.Color(0,   255,   0) = Red
  //strip.Color(0,   0,   255) = Blue
  stateButton = digitalRead(pinButton);
  if(stateButton == HIGH && previous == LOW && millis() - time > debounce) {
    //LEDtimer = true;
    if(stateLED == HIGH){
      stateLED = LOW;
    } else {
      timeFunctStarted = millis();
      stateLED = HIGH;
      LEDtimer = true;
      //timefunction started stores total millis elapsed at the point that you turn the LED on (LED timer = true)
      //This is when the while loop starts because when LEDtimer=true, we enter the while loop
    }
    time = millis();
  }
  digitalWrite(LED, stateLED);
  digitalWrite(blueLED, stateLED);
  previous == stateButton;
  while (LEDtimer == true){
        if ((millis()- timeFunctStarted) > 2000 && millis()- timeFunctStarted < 4000){
          lightPair(0, 1);
          motorOn20();
          Serial.println("first loop");
        }
        if ((millis()- timeFunctStarted) > 4000 && millis()- timeFunctStarted < 6000){
          lightPair(2, 3);
          motorOn40();
          Serial.println("second loop");
        }
        if ((millis()- timeFunctStarted) > 6000 && millis()- timeFunctStarted < 8000){
          lightPair(4, 5);
          motorOn20();
          Serial.println("third loop");
        }
        if ((millis()- timeFunctStarted) > 8000 && millis()- timeFunctStarted < 8500){
          lightPair(6, 7);
          tone(12, 261);
          motorOn10();
          Serial.println("fourth loop");
          delay(500);
        }
        if ((millis()- timeFunctStarted) > 8500){
          noTone(12);
          motorOff();
          delay(500);
          Serial.println("motor on loop");
        }
        if ((millis()- timeFunctStarted)> 12000){
          colorWipe(strip.Color(0,0,0), 1);
          Serial.print("Total Time Elapsed during function: ");
          Serial.println(millis()-timeFunctStarted);
          LEDtimer = false;
        }
      }
}
//Function that will change two LEDs at a time in the strip to red
//FOR REFRENCE ONLY
//strip.Color(255,   0,   0) = Green
//strip.Color(0,   255,   0) = Red
//strip.Color(0,   0,   255) = Blue
void lightPair(int LED1, int LED2) {
  strip.setPixelColor(LED1, strip.Color(255,   255,   255));
  strip.setPixelColor(LED2, strip.Color(255,   255,   255));
  strip.show();
}
void motorOn20() {
  analogWrite(9,20);
}
void motorOn40() {
  analogWrite(9,40);
}
void motorOn10() {
  analogWrite(9,10);
}
void motorOff(){
  analogWrite(9,0);
}
// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
