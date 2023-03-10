
/*!
 * @file LCDDisplayHeartrate.ino
 * @brief  Waves of blood oxygen saturation and heart rate value is displayed on the LCD
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [linfeng](Musk.lin@dfrobot.com)
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-04-26
 * @url  https://github.com/DFRobot/DFRobot_Heartrate
 */

#define heartratePin A1
#include "DFRobot_Heartrate.h"
#include "Lcd12864Shield.h"

uint16_t heartrateValue=0,heartrateValueLast=0;
uint8_t count;

Lcd12864Shield lcddisplay(10,9,8,13,11);
DFRobot_Heartrate heartrate(DIGITAL_MODE); ///< ANALOG_MODE or DIGITAL_MODE

char wordDisplay[]=  ///< word
{
0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,
0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,
0x00,0x00,0xC0,0xE0,0xE0,0xE0,0xC0,0x80,
0xC0,0xE0,0xE0,0xE0,0xC0,0x00,0x00,0x00,///< ♥
};
char letterDisplay[]= ///< character
{
  
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,///< 0
0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,
0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,///< 1
0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,
0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,///< 2
0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,
0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,///< 3
0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,
0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,///< 4
0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,
0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,///< 5
0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,
0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,///< 6
0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,
0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,///< 7
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,
0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,///< 8
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,///< 9
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,///< =
};



void lcdBegin(void)
{
  lcddisplay.initialLcd(); ///< Enable LCD
  lcddisplay.clearScreen(); ///< Clear LCD
  lcddisplay.drawXLine(48); ///< Draw a horizontal line
  lcddisplay.drawYLine(7); ///< Draw a vertical line
  lcddisplay.drawWord(7,10,0,wordDisplay); ///< Displays a word
  lcddisplay.drawLetter(7,30,10,letterDisplay); ///< Displays a character
}

void setup() {
  Serial.begin(115200);
  lcdBegin();
}

void loop() {
  unsigned char rateValue;  
  heartrateValueLast = heartrateValue;
  heartrateValue = heartrate.getValue(heartratePin);  ///< A1 foot sampled values
  count = heartrate.getCnt();
  if(count)
  {
    lcddisplay.drawYLine(count+8,heartrateValue/24,heartrateValueLast/24); ///< Draw a vertical line,Step 24
  }
  else
  {
    lcddisplay.drawYLine(count+8,heartrateValue/24,heartrateValueLast/24);
  }
 
  rateValue = heartrate.getRate(); ///< Get heart rate value   
  if(rateValue)
  {
    lcddisplay.drawLetter(7,50,3,rateValue,letterDisplay);  ///< Display values
    Serial.println(rateValue);
  }  
  delay(20);  
}
