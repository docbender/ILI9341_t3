#ifndef BUTTONS_H
#define BUTTONS_H

#include "ILI9341_ESP.h"

class BaseButton
{
public:
   BaseButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
   
   uint32_t X,Y,Width,Height;   
   // draw graphics
   virtual void Draw(ILI9341_ESP &renderer);
   // perform click
   void PerformClick();
   // perform press button
   void PerformPress();   
   // perform release button
   void PerformRelease();   
   // pointer to execution function on click
   void (*OnClick)();   
   // check if coordinates inside graphic
   bool ContainsCursor(uint32_t x, uint32_t y);

protected:
   bool redraw;
   bool clicked;
   bool pressed;
};

class BitmapButton : BaseButton
{
public:
   BitmapButton(uint32_t x, uint32_t y);

protected:
  
};

class TextButton : public BaseButton
{
public:
   TextButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const char *text, const ILI9341_t3_font_t &font)
      : BaseButton(x, y, width, height),firstDraw(0){ buttonText = text; textFont = &font; };
   
   // draw graphics
   void Draw(ILI9341_ESP &renderer);
protected:
   const char *buttonText;
   const ILI9341_t3_font_t *textFont;   
   uint32_t textX, textY; 
   bool firstDraw;
};


#endif
