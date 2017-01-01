#include "buttons.h"

BaseButton::BaseButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{ 
   redraw = true;
   pressed = clicked = false;
   X = x;
   Y = y;
   Width = width;
   Height = height;  
   
   OnClick = NULL;
}

void BaseButton::Draw(ILI9341_ESP &renderer) 
{ 
   if(!redraw) return;
   
   redraw = false;
   
   uint16_t fillcolor = pressed ? CL(0,85,175) : CL(100,100,100);
   uint16_t framecolor = pressed ? CL(127,135,225) : CL(165,165,165);
   
   renderer.fillRect(X,Y,Width,Height,fillcolor);
   renderer.drawRect(X,Y,Width,Height,framecolor);
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

#define BACKGROUND_COLOR ILI9341_BLACK
#define TEXT_COLOR ILI9341_WHITE

void TextButton::Draw(ILI9341_ESP &renderer) 
{ 
   if(!redraw) return;
   
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