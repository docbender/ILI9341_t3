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
   // force redraw
   void ForceRedraw(void) { redraw = true; };
   // visible set
   void SetVisible(bool isVisible) { visible = isVisible; };
   // visible get
   bool GetVisible(void) { return visible; };
   // long press enable for reapeat onclick
   void EnableLongPress(bool enable) { longPressEnabled = enable; };   
   // long press enable for secondary action
   void EnableLongPress(bool enable, void secondaryAction()) { longPressEnabled = enable; secondAction = secondaryAction; };   
   // check if press is last long
   void LongPressProcess(void);
   // grayed button
   void SetGrayed();   
   // grayed button
   void SetGrayed(bool enable);
   
protected:
   bool redraw;
   bool clicked;
   bool pressed;
   bool visible;
   bool grayed;
   bool longPressEnabled;
   uint32_t pressTime,repeatTime;
   bool repeatAction;
   void (*secondAction)();
};

class ImageButton : public BaseButton
{
public:
   ImageButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
      : BaseButton(x, y, width, height),image(NULL),path(NULL){  };
      
   ImageButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const uint16_t *imageData)
      : BaseButton(x, y, width, height),image(imageData),path(NULL){  };
      
   ImageButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height, char *imagePath)
      : BaseButton(x, y, width, height),image(NULL),path(imagePath){  };      
   
   // draw graphics
   void Draw(ILI9341_ESP &renderer); 
   void SetImage(const uint16_t *imageData) { image = imageData; redraw = true; };
   void SetImage(char *imagePath) { path = imagePath; redraw = true; };
protected:
   const uint16_t *image;  
   char *path;  
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
