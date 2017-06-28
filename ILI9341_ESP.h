// https://github.com/PaulStoffregen/ILI9341_t3
// http://forum.pjrc.com/threads/26305-Highly-optimized-ILI9341-(320x240-TFT-color-display)-library

/***************************************************
This is our library for the Adafruit  ILI9341 Breakout and Shield
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

#ifndef _ILI9341_ESPH_
#define _ILI9341_ESPH_

#ifdef __cplusplus
#include "Arduino.h"
#endif

#include <SPI.h>

#define ILI9341_TFTWIDTH  240
#define ILI9341_TFTHEIGHT 320

#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0x04
#define ILI9341_RDDST   0x09

#define ILI9341_SLPIN   0x10
#define ILI9341_SLPOUT  0x11
#define ILI9341_PTLON   0x12
#define ILI9341_NORON   0x13

#define ILI9341_RDMODE  0x0A
#define ILI9341_RDMADCTL  0x0B
#define ILI9341_RDPIXFMT  0x0C
#define ILI9341_RDIMGFMT  0x0D
#define ILI9341_RDSELFDIAG  0x0F

#define ILI9341_INVOFF  0x20
#define ILI9341_INVON   0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON  0x29

#define ILI9341_CASET   0x2A
#define ILI9341_PASET   0x2B
#define ILI9341_RAMWR   0x2C
#define ILI9341_RAMRD   0x2E

#define ILI9341_PTLAR    0x30
#define ILI9341_VSCRDEF  0x33  
#define ILI9341_MADCTL   0x36
#define ILI9341_VSCRSADD 0x37
#define ILI9341_PIXFMT   0x3A

#define ILI9341_WRDISBV  0x51
#define ILI9341_RDDISBV  0x52
#define ILI9341_WRCTRLD  0x53
#define ILI9341_RDCTRLD  0x54
#define ILI9341_WRCABC   0x55
#define ILI9341_RDCABC   0x56

#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DFUNCTR 0xB6

#define ILI9341_PWCTR1  0xC0
#define ILI9341_PWCTR2  0xC1
#define ILI9341_PWCTR3  0xC2
#define ILI9341_PWCTR4  0xC3
#define ILI9341_PWCTR5  0xC4
#define ILI9341_VMCTR1  0xC5
#define ILI9341_VMCTR2  0xC7

#define ILI9341_RDID1   0xDA
#define ILI9341_RDID2   0xDB
#define ILI9341_RDID3   0xDC
#define ILI9341_RDID4   0xDD

#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1
/*
#define ILI9341_PWCTR6  0xFC

*/

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

#define CL(_r,_g,_b) ((((_r)&0xF8)<<8)|(((_g)&0xFC)<<3)|((_b)>>3))

typedef struct {
   const unsigned char *index;
   const unsigned char *unicode;
   const unsigned char *data;
   unsigned char version;
   unsigned char reserved;
   unsigned char index1_first;
   unsigned char index1_last;
   unsigned char index2_first;
   unsigned char index2_last;
   unsigned char bits_index;
   unsigned char bits_width;
   unsigned char bits_height;
   unsigned char bits_xoffset;
   unsigned char bits_yoffset;
   unsigned char bits_delta;
   unsigned char line_space;
   unsigned char cap_height;
} ILI9341_t3_font_t;

#ifdef __cplusplus

class label
{
public:
   enum ALIGN_STATE {
      ALIGN_LEFT,
      ALIGN_CENTER,
      ALIGN_RIGHT
   } align;
   
   label(uint32_t x, uint32_t y, size_t maxlength, uint16_t backgroundcolor, 
         uint16_t foregroundcolor, const ILI9341_t3_font_t &font )
      : x(x), y(y), maxlength(maxlength), backgroundcolor(backgroundcolor), 
         foregroundcolor(foregroundcolor), font(&font)
      { text = new char[maxlength+1];  format = NULL; align = ALIGN_LEFT; };
   label(uint32_t x, uint32_t y, size_t maxlength, uint16_t backgroundcolor, 
         uint16_t foregroundcolor, const ILI9341_t3_font_t &font, const ALIGN_STATE align)
      : x(x), y(y), maxlength(maxlength), backgroundcolor(backgroundcolor), 
         foregroundcolor(foregroundcolor), font(&font), align(align)
      { text = new char[maxlength+1];  format = NULL; };      
   label(uint32_t x, uint32_t y, size_t maxlength, uint16_t backgroundcolor, 
         uint16_t foregroundcolor, const ILI9341_t3_font_t &font, char* format )
      : x(x), y(y), maxlength(maxlength), backgroundcolor(backgroundcolor), 
         foregroundcolor(foregroundcolor), font(&font), format(format)
      { text = new char[maxlength+1]; align = ALIGN_LEFT; };         
         
   uint32_t x;
   uint32_t y;
   size_t maxlength;
   char *text, *format;
   uint16_t backgroundcolor;
   uint16_t foregroundcolor;
   const ILI9341_t3_font_t *font;
   

   
protected:

   
};

class ILI9341_ESP : public Print
{
public:
   ILI9341_ESP(uint8_t _CS, uint8_t _DC, uint8_t _RST = 255);
   void begin(void);
   void beginTransaction(void);
   void sleep(bool enable);		
   void displayOff();
   void displayOn();
   void normalMode();
   void pushColor(uint16_t color);
   void fillScreen(uint16_t color);
   void drawPixel(int16_t x, int16_t y, uint16_t color);
   void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
   void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
   void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
   void fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2);
   void fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2);
   void fillScreenVGradient(uint16_t color1, uint16_t color2);
   void fillScreenHGradient(uint16_t color1, uint16_t color2);  
   void setRotation(uint8_t r);
   // defines vertical scroll area
   void setupScroll(int16_t topArea, int16_t scrollArea, int16_t bottomArea);
   // set scroll offset that scrollarea is moved
   void setScroll(int16_t offset);
   void invertDisplay(boolean i);
   void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
   // Pass 8-bit (each) R,G,B, get back 16-bit packed color
   static uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
      return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
   }
	//color565toRGB		- converts 565 format 16 bit color to RGB
	static void color565toRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
		r = (color>>8)&0x00F8;
		g = (color>>3)&0x00FC;
		b = (color<<3)&0x00F8;
	}	
	//color565toRGB14		- converts 16 bit 565 format color to 14 bit RGB (2 bits clear for math and sign)
	//returns 00rrrrr000000000,00gggggg00000000,00bbbbb000000000
	//thus not overloading sign, and allowing up to double for additions for fixed point delta
	static void color565toRGB14(uint16_t color, int16_t &r, int16_t &g, int16_t &b) {
		r = (color>>2)&0x3E00;
		g = (color<<3)&0x3F00;
		b = (color<<9)&0x3E00;
	}	
	//RGB14tocolor565		- converts 14 bit RGB back to 16 bit 565 format color
	static uint16_t RGB14tocolor565(int16_t r, int16_t g, int16_t b)
	{
		return (((r & 0x3E00) << 2) | ((g & 0x3F00) >>3) | ((b & 0x3E00) >> 9));
	}
   //uint8_t readdata(void);
   uint8_t readcommand8(uint8_t reg, uint8_t index = 0);
   // Added functions to read pixel data...
   uint16_t readPixel(int16_t x, int16_t y);
   void readRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors);
   void writeRect(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *pcolors);

   // from Adafruit_GFX.h
   void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
   void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
   void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
   void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
   void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
   void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
   void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
   void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
   void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
   void setCursor(int32_t x, int32_t y);
   void getCursor(int32_t *x, int32_t *y);  
   void setTextColor(uint16_t c);
   void setTextColor(uint16_t c, uint16_t bg);
   void setTextSize(uint8_t s);
   uint8_t getTextSize();
   void setTextWrap(boolean w);
   boolean getTextWrap();
   virtual size_t write(uint8_t);
   int32_t width(void)  { return _width; }
   int32_t height(void) { return _height; }
   uint8_t getRotation(void);
   void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
   void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
   int32_t getCursorX(void) const { return cursor_x; }
   int32_t getCursorY(void) const { return cursor_y; }
   void setFont(const ILI9341_t3_font_t &f) { font = &f; }
   void setFontAdafruit(void) { font = NULL; }
   void drawFontChar(unsigned int c);
   size_t strPixelLen(const char * str);
   // clear sprint
   void sprintc(label &object);
   // save sprint with prepared object(string is in text property)
   void sprints(label &object);
   // clear and save sprint with c_string
   void sprintcs(label &object, const char *s);
   // draw label
   void printLabel(label &object, bool force, ...);      
   // draw raw 565 bitmap stored in Flash filesystem
   int32_t drawRawBmp565(int16_t x, int16_t y, int16_t w, int16_t h,	char* path);
   // draw raw 565 bitmap stored in Flash filesystem
   int32_t drawRawBmp565BlackWhite(int16_t x, int16_t y, int16_t w, int16_t h,	char* path);   
   // set display brightness (0-255) - LED controller is not be implemented on every display
   void setBrightness(uint8_t brightness);   
   // create printscreen and save it into bitmap
   void printscreen(int32_t x, int32_t y, int32_t w, int32_t h, const char *fileName);

protected:
   enum UTF8_STATE {
      UTF8_VALID,
      UTF8_END,
      UTF8_INVALID
   };
 
   int32_t _width, _height; // Display w/h as modified by current rotation
   int32_t  cursor_x, cursor_y;
   uint16_t textcolor, textbgcolor;
   uint8_t textsize, rotation;
   boolean wrap; // If set, 'wrap' text at right edge of display
   const ILI9341_t3_font_t *font;

   uint8_t  _rst;
   uint8_t _cs, _dc;

   uint32_t _utf8_buffer;
   UTF8_STATE _utf8_state;
   uint8_t _utf8_byte_count;   

/*   void waittransfercompleted()__attribute__((always_inline))
   {
      while(SPI1CMD & SPIBUSY) {}
   }*/    
   
   void initializedatatransfer(void)__attribute__((always_inline))
   {
      //waittransfercompleted();
      
      digitalWrite(_dc, HIGH);
      //digitalWrite(_cs, LOW);
   }  
   
 /*  void startbuffertransfer(uint16_t bytescount)__attribute__((always_inline))
   {
      SPI.setDataBits(bytescount*8);
      SPI1CMD |= SPIBUSY;
   } */    

   void finishtransfer(void)__attribute__((always_inline))
   {
      //waittransfercompleted();
      digitalWrite(_cs, HIGH);
   }    
    
   void setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
   __attribute__((always_inline)) {
      // Column addr set
      digitalWrite(_dc, LOW);
      digitalWrite(_cs, LOW);
      SPI.write(ILI9341_CASET);
      // X 
      digitalWrite(_dc, HIGH);      
      uint8_t buffer[] = { (uint8_t) (x0 >> 8), (uint8_t) x0, (uint8_t) (x1 >> 8), (uint8_t) x1 };
      SPI.writeBytes(buffer, 4);
      // Row addr set
      digitalWrite(_dc, LOW);
      SPI.write(ILI9341_PASET);
      // Y 
      digitalWrite(_dc, HIGH);      
      buffer[0] = (uint8_t) (y0 >> 8);
      buffer[1] = (uint8_t) y0; 
      buffer[2] = (uint8_t) (y1 >> 8);
      buffer[3] = (uint8_t) y1;
      SPI.writeBytes(buffer, 4);
      //digitalWrite(_cs, HIGH);
   }   
   
   //write command
   void writecommand_cont(uint8_t c) __attribute__((always_inline)) {
      //waittransfercompleted();     
      
      digitalWrite(_dc, LOW);
      digitalWrite(_cs, LOW);
      
      SPI.write(c);
   }
   
   //write data byte
   void writedata8_cont(uint8_t c) __attribute__((always_inline)) {
      //waittransfercompleted();
      
      digitalWrite(_dc, HIGH);
      //digitalWrite(_cs, LOW);      
      
      SPI.write(c);
   }
   
   //write data word
   void writedata16_cont(uint16_t d) __attribute__((always_inline)) {
      //waittransfercompleted();
      
      digitalWrite(_dc, HIGH);
      //digitalWrite(_cs, LOW);      
      
      SPI.write16(d);
   }

   void writecommand_last(uint8_t c) __attribute__((always_inline)) {
      writecommand_cont(c);
      
      finishtransfer();  
   }
   void writedata8_last(uint8_t c) __attribute__((always_inline)) {
      writedata8_cont(c);
      
      finishtransfer();   
   }
   void writedata16_last(uint16_t d) __attribute__((always_inline)) {
      writedata16_cont(d);
      
      finishtransfer();   
   }
   
   void fillPreparedArea(uint32_t length, uint16_t color) __attribute__((always_inline)) {   
      initializedatatransfer();
      uint32_t pixels = length;
      uint8_t swapColor[] = { (uint8_t)(color >> 8), (uint8_t)color };
      SPI.writePattern(swapColor,2,pixels);
   }
   
   void HLine(int16_t x, int16_t y, int16_t w, uint16_t color)
   __attribute__((always_inline)) {
      setAddr(x, y, x+w-1, y);
      writecommand_cont(ILI9341_RAMWR);      
      fillPreparedArea((uint32_t)w, color);
   }
   void VLine(int16_t x, int16_t y, int16_t h, uint16_t color)
   __attribute__((always_inline)) {
      setAddr(x, y, x, y+h-1);
      writecommand_cont(ILI9341_RAMWR);
      fillPreparedArea((uint32_t)h, color);
   }
   void Pixel(int16_t x, int16_t y, uint16_t color)
   __attribute__((always_inline)) {
      setAddr(x, y, x, y);
      writecommand_cont(ILI9341_RAMWR);
      writedata16_cont(color);
   }
   void drawFontBits(uint32_t bits, uint32_t numbits, uint32_t x, uint32_t y, uint32_t repeat);
   
   uint32_t binarySearch(const uint8_t* data, const uint32_t length, const uint32_t value);
   void nextUTF8State(const uint8_t c);
};


#ifndef swap
#define swap(a, b) { int16_t t = a; a = b; b = t; }
#endif


#endif // __cplusplus


#endif
