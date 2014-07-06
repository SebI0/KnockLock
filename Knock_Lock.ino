// include the library code:
#include <LiquidCrystal.h>
#include <EEPROM.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int TIME = 0;

void timeInit()
{
  TIME = millis();
}

int time()
{
  return millis()-TIME;
}

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  
}


int dec_bin(int dec)
{
  int binaires[] = {1,2,4,8,16,32,64,128};
  int bin[7];
  int i;
  
  for(i=0;i<8;i++)
  {
    if (dec>=binaires[7-i])
    {
      bin[i] = 1;
      dec = dec - binaires[7-i];
    }
    else
      bin[i] = 0;
  }  
  
  for (i=0;i<8;i++)
    Serial.print(bin[i]);
    Serial.println();
}
bool debut = false;
int pos = 0; //Position de la sonnerie

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Lock Knock");
  delay(500);
  dec_bin(154);
}

void loop() {
  lcd_key = read_LCD_buttons();  // read the buttons
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT: //Sensor sonore
    {
      if (!debut) //Si c'est la première sonnerie
      {
        //ecouter(0); LOL
        debut = false;
      }
      else
      {
        //ecouter(1);
      }
      break;
    }
  }

}
