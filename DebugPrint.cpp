
#include "arial.h"
#include "DebugPrint.h"

//-------------------------------------------------------------------------------------------------
// overrided write function
size_t DebugPrint::write(uint8_t c)
{
   if(c == '\n')
   {
      ++logLast;
      if(logLast>=logsSize)
         logLast=0;
      if(logLast==logStart)
         logStart++;   
      if(logStart>=logsSize)
         logStart=0;      
      logsLength[logLast] = 0;
      logs[logLast][0] = 0;
      return 0;
   }  
   
   size_t p = logsLength[logLast];
   
   if(p>=RECORD_LENGTH-1)
      return 0;

   logs[logLast][p++] = c;
   logs[logLast][p] = 0;
   
   logsLength[logLast] = p;
  
   return 1;   
}

//-------------------------------------------------------------------------------------------------
// render all saved records from begin
void DebugPrint::renderAll(ILI9341_ESP &renderer, int32_t x, int32_t y, int32_t width, int32_t height, int16_t backgroundcolor, int16_t textcolor )
{
   renderer.setFont(arial_12);
   renderer.setTextColor(textcolor);
   renderer.setCursor(0,y+5);
   
   logPrinted = logStart;
   
   render(renderer, x, y, width, height, backgroundcolor, textcolor );
}

//-------------------------------------------------------------------------------------------------
// render non printed records from saved position
void DebugPrint::renderRest(ILI9341_ESP &renderer, int32_t x, int32_t y, int32_t width, int32_t height, int16_t backgroundcolor, int16_t textcolor )
{
   renderer.setFont(arial_12);
   renderer.setTextColor(textcolor);   
   renderer.setCursor(0,logCursor);
   
   render(renderer, x, y, width, height, backgroundcolor, textcolor );
}

//-------------------------------------------------------------------------------------------------
// render into defined area
void DebugPrint::render(ILI9341_ESP &renderer, int32_t x, int32_t y, int32_t width, int32_t height, int16_t backgroundcolor, int16_t textcolor )
{  
   while(logPrinted!=logLast)
   {
      if(logPrinted>logLast)
      {
         while(logPrinted<logsSize)
         {
            if(y+height - renderer.getCursorY() < arial_12.line_space + 1)
            {
               renderer.setCursor(0,y+5);
               renderer.fillRect(0,y,width,height,backgroundcolor);
               
               if(++logStart==logsSize)
               {
                  logStart=0;
                  break;
               }
               logPrinted = logStart;
            }
            
            renderer.println(logs[logPrinted++]);
         }
         logPrinted = 0;
      }
      
      if(logPrinted<logLast)
      {
         while(logPrinted<logLast)
         {
            if(y+height - renderer.getCursorY() < arial_12.line_space + 1)
            {
               renderer.setCursor(0,y+5);
               renderer.fillRect(0,y,width,height,backgroundcolor);
               if(++logStart==logsSize)
               {
                  logPrinted = logStart=0;
                  break;
               }
               logPrinted = logStart;
            }
            
            renderer.println(logs[logPrinted++]);
         }
      }
   }
   logCursor = renderer.getCursorY();   
}