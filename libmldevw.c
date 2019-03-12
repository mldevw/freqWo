/*
  libmldevw - personal library with some useful functions
  mldevw for public audience
*/

#include "libmldevw.h"
#include <stdio.h>
#include <assert.h>

void printfCenterText(const char* strToCenter, const uint16_t desiredLength)
{

#ifdef DEBUG
  if (strlen(strToCenter)>desiredLength)
  printf("ERROR: libmldevw::printfCenterText: strlen(strToCenter)>desiredLength (%d>%d)",
        strlen(strToCenter),desiredLength);
#endif

  // check if string is longer then desired to avoid negative padding
  uint16_t spacesOnOneSide       = strlen(strToCenter)>desiredLength?0:
                                   (desiredLength-strlen(strToCenter))/2;
  uint8_t  spacesOnOneSideUneven = strlen(strToCenter)>desiredLength?0:
                                   (desiredLength-strlen(strToCenter))%2;

  printf("%*s%s%*s",
   spacesOnOneSide,"",
   strToCenter,
   spacesOnOneSide+spacesOnOneSideUneven, "");
}
