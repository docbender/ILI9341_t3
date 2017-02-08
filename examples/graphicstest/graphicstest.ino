/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include <ESP8266WiFi.h>
#include <ArduinoOTA.h> 
#include "SPI.h"
#include "ILI9341_ESP.h"
#include "Arduino.h"

#define WIFI_SSID "WLAN"
#define WIFI_PWD  "heslonawifi"
#define OTA_HOST "ILI-ESP"
#define OTA_PASS "xxxxx"

#define LCD_DC  4
#define LCD_CS  5

ILI9341_ESP tft = ILI9341_ESP(LCD_CS, LCD_DC);			// ESP: create LCD object

void WiFiEvent(WiFiEvent_t event) {

}

void setup() {
// delete old config
  WiFi.disconnect(true);
  delay(1000);
   
  WiFi.onEvent(WiFiEvent);

  WiFi.begin(WIFI_SSID, WIFI_PWD);

  ArduinoOTA.setHostname(OTA_HOST);
  ArduinoOTA.setPassword(OTA_PASS);
  ArduinoOTA.onStart([]() {

  });

  ArduinoOTA.onEnd([]() { 
  });

  ArduinoOTA.onError([](ota_error_t error) { ESP.restart(); });
  /* setup the OTA server */
  ArduinoOTA.begin(); 
   
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.println("Waiting for Arduino Serial Monitor...");

  Serial.begin(115200);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("ILI9341 Test!"); 
  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);  
  
}

uint32_t testId = 0, finishTime;
uint32_t tFill,tText,tLines,tHVLines,tCircF,tRectO,tRectF,tCircO,tTriO,tTriF,tRRectO,tRRectF;

void loop(void) {
  ArduinoOTA.handle();
  
  if(testId<13)
    runTest(testId++);
  else if(testId++==13){
     printResults();
     finishTime = millis();
  }else{
     if(millis()-finishTime>60000)
       testId=0;
  }
  
/*  
  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(1000);
  }
*/  
}

void runTest(uint32_t testId){
   if(testId==0){
      Serial.println(F("Benchmark                Time (microseconds)"));
     
      Serial.print(F("Screen fill              "));
      tFill = testFillScreen();
      Serial.println(tFill);
      delay(20);
      return;
   }

   if(testId==1){
      Serial.print(F("Text                     "));
      tText = testText();
      Serial.println(tText);
      delay(20);
      return;
   }  

   if(testId==2){  
      Serial.print(F("Lines                    "));
      tLines = testLines(ILI9341_CYAN);
      Serial.println(tLines);
      delay(20);
      return;
   }  

   if(testId==3){  
      Serial.print(F("Horiz/Vert Lines         "));
      tHVLines = testFastLines(ILI9341_RED, ILI9341_BLUE);
      Serial.println(tHVLines);
      delay(20);
      return;
   }  

   if(testId==4){  
      Serial.print(F("Rectangles (outline)     "));
      tRectO = testRects(ILI9341_GREEN);
      Serial.println(tRectO);
      delay(20);
      return;
   }  

   if(testId==5){
      Serial.print(F("Rectangles (filled)      "));
      tRectF = testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA);
      Serial.println(tRectF);
      delay(20);
      return;
   }  

   if(testId==6){
      Serial.print(F("Circles (filled)         "));
      tCircF = testFilledCircles(10, ILI9341_MAGENTA);
      Serial.println(tCircF);
      delay(20);
      return;
   }  

   if(testId==7){  
      Serial.print(F("Circles (outline)        "));
      tCircO = testCircles(10, ILI9341_WHITE);
      Serial.println(tCircO);
      delay(20);
      return;
   }  

   if(testId==8){
      Serial.print(F("Triangles (outline)      "));
      tTriO = testTriangles();
      Serial.println(tTriO);
      delay(20);
      return;
   }  

   if(testId==9){  
      Serial.print(F("Triangles (filled)       "));
      tTriF = testFilledTriangles();
      Serial.println(tTriF);
      delay(20);
      return;
   }  

   if(testId==10){  
      Serial.print(F("Rounded rects (outline)  "));
      tRRectO = testRoundRects();
      Serial.println(tRRectO);
      delay(20);
      return;
   }      

   if(testId==11){  
      Serial.print(F("Rounded rects (filled)   "));
      tRRectF = testFilledRoundRects();
      Serial.println(tRRectF);
      delay(20);
      return;
   }      

   if(testId==12){  
      Serial.println(F("Done!"));   
      return;
   }
}

void printResults(){
   tft.fillScreen(ILI9341_BLACK);
   tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
   tft.setCursor(0, 50);
  
   tft.println(F("Benchmark                Time (us)"));     
   tft.print(F("Screen fill              "));
   tft.println(tFill);

   tft.print(F("Text                     "));
   tft.println(tText);

   tft.print(F("Lines                    "));
   tft.println(tLines);

   tft.print(F("Horiz/Vert Lines         "));
   tft.println(tHVLines); 

   tft.print(F("Rectangles (outline)     "));
   tft.println(tRectO);

   tft.print(F("Rectangles (filled)      "));
   tft.println(tRectF);

   tft.print(F("Circles (filled)         "));
   tft.println(tCircF);

   tft.print(F("Circles (outline)        "));
   tft.println(tCircO); 

   tft.print(F("Triangles (outline)      "));
   tft.println(tTriO);

   tft.print(F("Triangles (filled)       "));
   tft.println(tTriF);

   tft.print(F("Rounded rects (outline)  "));
   tft.println(tRRectO);     

   tft.print(F("Rounded rects (filled)   "));
   tft.println(tRRectF);
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_BLACK);
  tft.fillScreen(ILI9341_RED);
  tft.fillScreen(ILI9341_GREEN);
  tft.fillScreen(ILI9341_BLUE);
  tft.fillScreen(ILI9341_BLACK);
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

uint32_t testLines(uint16_t color) {
  uint32_t start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ILI9341_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  if(t>1000000)
     delay(1);  
  
  tft.fillScreen(ILI9341_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  if(t>1000000)
     delay(1);
  
  tft.fillScreen(ILI9341_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(ILI9341_BLACK);
  
  if(t>1000000)
     delay(1);  

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  return t + micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
  }

  return micros() - start;
}
