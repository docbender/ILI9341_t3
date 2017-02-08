
#ifndef DebugPrint_h
#define DebugPrint_h

#include <inttypes.h>
#include <stdio.h>

#include "WString.h"
#include "Printable.h"

#include <ILI9341_ESP.h>

#define RECORD_LENGTH 64

class DebugPrint : public Print
{
protected:
   size_t logsSize;
   char** logs;
   size_t* logsLength;
   uint32_t logStart = 0, logLast = 0, logPrinted = 0;
   int32_t logCursor;   
   
public:
   DebugPrint(size_t lines) : logsSize(lines) { 
         logs = new char*[lines];
         logsLength = new size_t[lines];
         for(size_t i=0;i<logsSize;i++){
            logs[i] = new char[RECORD_LENGTH];
            logs[i][0] = 0;
            logsLength[i] = 0;
         }
      }

   size_t write(uint8_t);
//   size_t write(const uint8_t *buffer, size_t size);

   void renderAll(ILI9341_ESP &renderer, int32_t x, int32_t y, int32_t width, int32_t height, int16_t backgroundcolor, int16_t textcolor );
   void renderRest(ILI9341_ESP &renderer, int32_t x, int32_t y, int32_t width, int32_t height, int16_t backgroundcolor, int16_t textcolor );
   void render(ILI9341_ESP &renderer, int32_t x, int32_t y, int32_t width, int32_t height, int16_t backgroundcolor, int16_t textcolor );   
};

#endif
   