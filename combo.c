#include <LPC23xx.h>
#include <stdio.h>

#define _BV(x) (1<<(x))

#define LED_0 _BV(0)
#define LED_1 _BV(1)
#define LED_2 _BV(2)
#define LED_3 _BV(3)
#define LED_4 _BV(4)
#define LED_5 _BV(5)
#define LED_6 _BV(6)
#define LED_7 _BV(7)

#define LED_MASKA (LED_0 | LED_1 | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7)

#define LineLen 16
#define NumLines 2

#define PIN_E	   0xC0000000
#define PIN_RW 	   0x20000000
#define PIN_RS     0x10000000
#define PINS_CTRL  0xF0000000
#define PINS_DATA  0x0F000000

#define LCD_E(x) ((x)?(IOSET1=PIN_E):(IOCLR1=PIN_E));

#define LCD_RW(x) ((x)?(IOSET1=PIN_RW):(IOCLR1=PIN_RW));

#define LCD_RS(x) ((x)?(IOSET1=PIN_RS):(IOCLR1=PIN_RS));

#define LCD_DATA_IN ((IOPIN1>>24)&0xF);

#define LCD_DATA_OUT(x) IOCLR1=PINS_DATA;IOSET1=(x&0xF)<<24;

#define LCD_ALL_DIR_OUT IODIR1|=PINS_CTRL|PINS_DATA;

#define LCD_DATA_DIR_IN IODIR1&=~PINS_DATA;

#define LCD_DATA_DIR_OUT IODIR1|=PINS_DATA;

void LED_init(void) {
PINSEL10=0;
FIO2DIR|LED_MASKA;
FIO2MASK=0x00000000;
}

int main(void) {

}
									 
