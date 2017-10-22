#include "MD_MAX72xx.h"
#include <string.h>

class LedDisplay
{
  //3.3V DC

  //must be in that order:
  #define MAX_DEVICES 1
  #define DIN 13 // SPI Bus MOSI //D7
  #define CS 15 // SPI Bus MISO  //D8
  #define CLK 14 // SPI Bus SS (CS) //D5
  MD_MAX72XX mx = MD_MAX72XX(DIN, CLK, CS, MAX_DEVICES);
  
  // Text parameters
  #define	CHAR_SPACING	1	// pixels between characters

  public:
    char* outTempTopic = "openhab/out/LedDisplay/state";
    char* inTempTopic = "openhab/in/LedDisplay/state";
    
    void setup()
    {
      mx.begin();
    }

    void loop(String msg)
    {
      printText(msg);
    }

    void printText(String msg)
    // Print the text string to the LED matrix modules specified.
    // Message area is padded with blank columns after printing.
    {
      char* pMsg = new char[msg.length()+1];
      strcpy(pMsg, msg.c_str());
      if (pMsg == NULL || pMsg == "")
      {
        pMsg = "";
      }

      uint8_t modStart, modEnd;
      modStart = 0;
      modEnd = MAX_DEVICES - 1;

      uint8_t   state = 0;
      uint8_t	  curLen;
      uint16_t  showLen;
      uint8_t	  cBuf[8];
      int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;
    
      mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    
      do     // finite state machine to print the characters in the space available
      {
        switch(state)
        {
          case 0:	// Load the next character from the font table
            // if we reached end of message, reset the message pointer
            if (*pMsg == '\0')
            {
              showLen = col - (modEnd * COL_SIZE);  // padding characters
              state = 2;
              break;
            }
    
            // retrieve the next character form the font file
            showLen = mx.getChar(*pMsg++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
            curLen = 0;
            state++;
            // !! deliberately fall through to next state to start displaying
    
          case 1:	// display the next part of the character
            mx.setColumn(col--, cBuf[curLen++]);
    
            // done with font character, now display the space between chars
            if (curLen == showLen)
            {
              showLen = CHAR_SPACING;
              state = 2;
            }
            break;
    
          case 2: // initialize state for displaying empty columns
            curLen = 0;
            state++;
            // fall through
    
          case 3:	// display inter-character spacing or end of message padding (blank columns)
            mx.setColumn(col--, 0);
            curLen++;
            if (curLen == showLen)
              state = 0;
            break;
    
          default:
            col = -1;   // this definitely ends the do loop
        }
      } while (col >= (modStart * COL_SIZE));
    
      mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    }
};