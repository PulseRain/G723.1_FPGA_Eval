//==================================================================================================
// PulseRain Technology, LLC
//
// Demonstration for Lattice MACHXO3D Breakout Board
// 
// Using Ctrl-U to compile and upload this sketch,
// then use Ctrl-Shift-M to open Serial Monitor
//
// Adjust DIP-SW 1 and 2 for LED pattern.
// Adjust DIP-SW 3 and 4 for LED refreshing rate.
//==================================================================================================

#include "PulseRainUARTConsole.h"


volatile uint8_t* const REG_ROTARY_DATA = (uint8_t*) 0x20000030;

int run (int argc, char* argv[])
{
    uint8_t c;
    uint8_t out_vol = 16;
    uint8_t in_vol = 16;
    uint8_t sel = 0;
    uint8_t prev_sel = 0;

    *REG_ROTARY_DATA = out_vol;
    GPIO_P1 = out_vol;
    GPIO_P0 = in_vol;
    
    do {
        c = 0;
        
        if (Serial.available()) {
            c = Serial.read();    
        }

        delay (200);

        prev_sel = sel;
        sel = GPIO_P0 & 1;

        if ((!prev_sel) && sel) {
            Serial.print ("================> Set Out Volume: ");
            Serial.println(out_vol);
            *REG_ROTARY_DATA = out_vol;
        } else if ((prev_sel) && (!sel)) {
            Serial.print ("================> Set In Volume: ");
            Serial.println(in_vol);
            *REG_ROTARY_DATA = in_vol;    
        }
       
        if (sel) {
            Serial.print("====== Output Volume: ");
            out_vol = *REG_ROTARY_DATA;
            GPIO_P1 = out_vol;
           
            Serial.println(out_vol);
        } else {
            Serial.print("====== Input Volume: ");
            in_vol = *REG_ROTARY_DATA;
           
            GPIO_P0 = in_vol;
            Serial.println(in_vol);
        }
  
   } while ((c != 'q') &&  (c != 'Q'));
    
    return 0;
}


void setup() {
    uint32_t i;
    uint32_t *p;

    GPIO_P0 = 0x00;
    delay (2000);
    Serial.println ("==================================================================");
    Serial.println (" PulseRain Technology, G723.1 Demo, Ver 1.0\n");
    Serial.println (" Usage: Type \"run\" in your PulseRain Console.");
    Serial.println ("        ");
    Serial.println ("        Adjust Rotary Encoder for Volume.");
    Serial.println ("        Connect the Blue one to the line out of your computer.");
    Serial.println ("        Connect the Green one to a speaker.");
    Serial.println ("        ");
    Serial.println ("        Play something on your computer. The audio will go through");
    Serial.println ("        G723.1 encoder, then decoder, to play back.");
    Serial.println ("==================================================================");
    
    *REG_ROTARY_DATA = 0;

    PULSERAIN_UART_CONSOLE.add_cmd ({"run","run ", run});
    PULSERAIN_UART_CONSOLE.run();
}

uint8_t rotate (uint8_t led)
{
    return (((led >> 1) & 0x7F) | ((led & 1) << 7));
}

void loop() {

  uint32_t i, j;
  static uint32_t t = GPIO_P0;
  static uint32_t n = 0;
  
  static uint8_t led = 1;
  uint8_t led_proxy;

  uint32_t k;
  
  k = t;
  t = GPIO_P0;



  led_proxy = led;
  
  for (i = 0; i < (t & 3); ++i) {
      k = led;
      for (j = 0; j < (i + 1); ++j) {
          k = rotate (k);
      } // for j

      led_proxy |= k;
      
  } // for i

  led = rotate (led);
   
  
  Serial.print (n++);
  Serial.print (", SW = 0x");
  Serial.println (t, HEX);

  delay (200 * ((t >> 2) & 3) + 200);

//  GPIO_P0 = ~led_proxy;

  
  uint8_t r = *REG_ROTARY_DATA;

  
  Serial.print("====== R: ");
  Serial.println(r);
  GPIO_P0 = r;

}
