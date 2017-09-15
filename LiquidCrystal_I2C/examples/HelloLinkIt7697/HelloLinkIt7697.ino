#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// set the I2C address of the LCD controller
//    0x3F for PCF8574A
//    0x27 for PCF8574
LiquidCrystal_I2C lcd(0x3F);

// define the custom bitmaps
// up to 8 bitmaps are supported
const uint8_t my_bitmap[][8] =
{
  // chequer
  {0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x00},
  // up arrow
  {0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x00, 0x00},
  // down arrow
  {0x00, 0x00, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04},
  // rectangle
  {0x00, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00},
  // up-left arrow
  {0x1F, 0x1E, 0x1C, 0x1A, 0x11, 0x00, 0x00, 0x00},
  // up-right arrow
  {0x1F, 0x0F, 0x07, 0x0B, 0x11, 0x00, 0x00, 0x00},
  // down-left arrow
  {0x00, 0x00, 0x00, 0x11, 0x1A, 0x1C, 0x1E, 0x1F},
  // down-right arrow
  {0x00, 0x00, 0x00, 0x11, 0x0B, 0x07, 0x0F, 0x1F},
};

#define LONG_DELAY()  delay(1000)
#define SHORT_DELAY() delay(500)
#define ANIM_DELAY()  delay(400)

void setup()
{
  int i;
  int bitmap_size = sizeof(my_bitmap) / sizeof(my_bitmap[0]);

  // init the 1602 (2 rows / 16 columns) LCD
  lcd.begin(16, 2);

  // register the custom bitmaps
  for (i = 0; i < bitmap_size; i++ )
  {
    lcd.createChar(i, (uint8_t *)my_bitmap[i]);
  }

  // move the cursor to 0
  lcd.home();
  lcd.print("          Hello!");
  
  // scroll left for 5 positions
  for (int i = 0; i < 5; i++)
  {
    lcd.scrollDisplayLeft();
    
    ANIM_DELAY();
  }

  // clear the LCD contents and the scrolling offset
  lcd.clear();

  // turn off the backlight
  lcd.noBacklight();
  
  LONG_DELAY();

  // turn on the backlight
  lcd.backlight();
  
  lcd.print("     Hello!     ");
  // change to the starting position of the next line
  lcd.setCursor ( 0, 1 );
  lcd.print("  LinkIt 7697   ");

  // blinks the texts
  for (i = 0; i < 2; i++)
  {
    ANIM_DELAY();
    lcd.noDisplay();
    
    ANIM_DELAY();
    lcd.display();
  }
  
  LONG_DELAY();
  LONG_DELAY();

  // clear all LCD contents and settings
  lcd.clear();
  
  SHORT_DELAY();
}

void loop()
{
  int i, ch_map;

  // clear the LCD and set the string direction to left-to-right
  lcd.clear();
  lcd.leftToRight();  
  lcd.print("    LeftToR");
  
  LONG_DELAY();

  lcd.setCursor(4, 0);
  lcd.print("12345678");
  
  SHORT_DELAY();
  
  lcd.setCursor(4, 0);

  // display the custom characters. randomly select a character bitmap
  for (i = 0; i < 8; i++ )
  {
    ch_map = random(8);
    
    lcd.print(char(ch_map));

    ANIM_DELAY();
  }

  lcd.setCursor(0, 1);
  lcd.print("    RightToL");
  LONG_DELAY();

  // set the string direction to right-to-left
  lcd.rightToLeft();
  lcd.setCursor(11, 1);
  lcd.print("12345678");
  SHORT_DELAY();
  
  lcd.setCursor(11, 1);

  // display the custom characters. randomly select a character bitmap
  for (i = 0; i < 8; i++ )
  {
    ch_map = random(8);

    lcd.print(char(ch_map));

    ANIM_DELAY();
  }
}
