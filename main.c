#define F_CPU 8000000UL // Define software reference clock for delay duration

/*************************
	 attiny85

 PB5 |------| V
 PB3 |      | PB2
 PB4 |      | PB1
 GND |------| PB0

PB1 connected to PIN Changer
PB0 output LED

****************************/

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void system_sleep();

// From http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
void system_sleep() {
  cbi(ADCSRA,ADEN); // Switch Analog to Digital converter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode
  sleep_mode(); // System sleeps here
  sbi(ADCSRA,ADEN);  // Switch Analog to Digital converter ON
}

ISR(PCINT0_vect) {
}
  
int main(void)
{

	DDRB |= (1<<PB0);//set led OUTPUT
        DDRB &=~(1<<PB1);//set led INPUT

  	sbi(GIMSK,PCIE); // Turn on Pin Change interrupt
  	sbi(PCMSK,PCINT1); // Which pins are affected by the interrupt

	while (1 == 1)
	{
			PORTB |=(1<<PB0);
  			_delay_ms(3);

			PORTB &=~(1<<PB0);
 			system_sleep();
		}
   return 1;
}
 
 

 
