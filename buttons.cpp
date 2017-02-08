#include "buttons.h"

#define FIRST_REPEAT_PRESS_TIME 1000
#define NEXT_REPEAT_PRESS_TIME 200

BaseButton::BaseButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{ 
   redraw = true;
   visible = true;
   pressed = clicked = false;
   X = x;
   Y = y;
   Width = width;
   Height = height;  
   longPressEnabled = false;
   
   OnClick = NULL;
   secondAction = NULL;
}

void BaseButton::PerformClick() 
{ 
   clicked = true;
   
   if(OnClick!=NULL)
      (*OnClick)();
   
   pressed = clicked = false;
   redraw = true;
}

void BaseButton::PerformPress()
{ 
   if(pressed)
      return;   
   
   pressed = true;
   redraw = true;   
   repeatAction = false;
   pressTime = millis();   
}

void BaseButton::PerformRelease()
{ 
   if(!pressed)
      return;   
   
   pressed = false;
   redraw = true;     
}

bool BaseButton::ContainsCursor(uint32_t x, uint32_t y) 
{ 
   if(X>x || (X+Width) < x)
      return false;
   if(Y>y || (Y+Height) < y)
      return false;
   
   return true;
}

void BaseButton::LongPressProcess(void)
{
   if(!pressed)
      return;
   
   uint32_t now = millis();
   if((secondAction == NULL) && repeatAction && (now - repeatTime > NEXT_REPEAT_PRESS_TIME))
   {
      repeatTime = now;
      
      if(OnClick!=NULL)
         (*OnClick)();
   }
   else if(!repeatAction && (now - pressTime > FIRST_REPEAT_PRESS_TIME))
   {
      repeatAction = true;
      repeatTime = now;
      
      if(secondAction != NULL)
      {
         (*secondAction)();
      }else{      
         if(OnClick!=NULL)
            (*OnClick)();      
      }
   }   
}

void BaseButton::Draw(ILI9341_ESP &renderer) 
{ 
   LongPressProcess();
   
   if(!redraw || !visible) return;
   
   redraw = false;
   
   uint16_t fillcolor = pressed ? CL(0,85,175) : CL(100,100,100);
   uint16_t framecolor = pressed ? CL(127,135,225) : CL(165,165,165);
   
   renderer.fillRect(X,Y,Width,Height,fillcolor);
   renderer.drawRect(X,Y,Width,Height,framecolor);
}

void ImageButton::Draw(ILI9341_ESP &renderer) 
{ 
   LongPressProcess();
   
   if(!redraw || !visible) return;
   
   redraw = false;
   
   if(image)
      renderer.writeRect(X,Y,Width,Height,image);
   else if(path)
      renderer.drawRawBmp565(X,Y,Width,Height,path);
   
   uint16_t framecolor = pressed ? CL(127,135,225) : CL(165,165,165);   
   renderer.drawRect(X,Y,Width,Height,framecolor); 
}

#define BACKGROUND_COLOR ILI9341_BLACK
#define TEXT_COLOR ILI9341_WHITE

void TextButton::Draw(ILI9341_ESP &renderer) 
{ 
   LongPressProcess();
   
   if(!redraw || !visible) return;
   
   BaseButton::Draw(renderer);
   
   if(!firstDraw && textFont!=NULL)
   {
      firstDraw = true;
      
      textX = X+(Width-renderer.strPixelLen(buttonText))/2;
      textY = Y+(Height-textFont->line_space);
   }
   
   if(textFont!=NULL) 
      renderer.setCursor(textX,textY);
   else
      renderer.setCursor(X+6,Y+4);
   
   renderer.setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
   renderer.setFont(*textFont);
   renderer.print(buttonText);
}