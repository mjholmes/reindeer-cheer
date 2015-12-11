// Reindeer head cheerlights "nose" controller// Based on ThingSpeak Cheerlights example code// https://github.com/mathworks/thingspeak-particle// and AdaFruit Neopixel Library example#include "neopixel/neopixel.h"#include "ThingSpeak/ThingSpeak.h"SYSTEM_MODE(AUTOMATIC);// Using a single neopixel as the "nose"#define PIXEL_PIN D0#define PIXEL_COUNT 1#define PIXEL_TYPE WS2812BAdafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);TCPClient client;int $debug = 0;// Live cheerlightsunsigned long cheerlightsChannel = 1417;// Test channel//unsigned long cheerlightsChannel = 70432;int curR = 0, curG = 0, curB = 0;void setup() {  strip.begin();  strip.setBrightness(48);  strip.show(); // Initialize all pixels to 'off'  ThingSpeak.begin(client);}void loop() {  // The cheerlights ThignSpeak channel uses field1 for text string eg "red", "green" etc  // and field2 for HEX values, eg "#ff0000", "#00ff00"  // Using the colour string allows us to modify the actual RGB values locally for a better  // colour representation  String colourName = ThingSpeak.readStringField(cheerlightsChannel, 1);    // setColour(fade delay, fade steps, new colour)  // A larger value for delay or steps slows the fade speed.  setColour(10, 200, colourName);    // Only poll Thingspeak every 10 seconds.  delay(10000);}void setColour(uint8_t wait, int numSteps, String colour) {  uint16_t pixel;  int newR = 0xff, newG = 0xff, newB = 0xff;  int r = 0, g = 0, b = 0;  // Modify the RGB values to give the best colour mixing for your output LED.    if(colour == "red")       { newR = 0xff; newG = 0x00; newB = 0x00; }  if(colour == "pink")      { newR = 0xff; newG = 0xc0; newB = 0xcb; }  if(colour == "green")     { newR = 0x00; newG = 0xff; newB = 0x00; }  if(colour == "blue")      { newR = 0x00; newG = 0x00; newB = 0xff; }  if(colour == "cyan")      { newR = 0x00; newG = 0xff; newB = 0xff; }  if(colour == "white")     { newR = 0xff; newG = 0xff; newB = 0xff; }  if(colour == "warmwhite") { newR = 0xff; newG = 0xf5; newB = 0xe6; }  if(colour == "oldlace")   { newR = 0xfd; newG = 0xf5; newB = 0xe6; }  if(colour == "purple")    { newR = 0x80; newG = 0x00; newB = 0x80; }  if(colour == "magenta")   { newR = 0xff; newG = 0x00; newB = 0xff; }  if(colour == "yellow")    { newR = 0xff; newG = 0xff; newB = 0x00; }  if(colour == "orange")    { newR = 0xff; newG = 0xa5; newB = 0x00; }    // Fade rather than switch between colours  for(int i = 1; i <= numSteps; i++) {    r = curR + (newR - curR) * i / numSteps;    g = curG + (newG - curG) * i / numSteps;    b = curB + (newB - curB) * i / numSteps;    // Change all pixels. There is only one pixel in this design but    // It's handy to be able to re-use code.    for(pixel=0; pixel<strip.numPixels(); pixel++) {      strip.setPixelColor(pixel, r, g, b);    }        strip.show();    delay(wait);  }    curR = newR;  curG = newG;  curB = newB;    if ($debug) {    char publishString[20];    sprintf(publishString, "R %d, G %d, B %d", r, g, b);    Particle.publish("DEBUG", publishString);   }}