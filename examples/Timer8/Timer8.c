/*****************************************************
 * 
 *            Noeww bare-metal Arduino :)
 *            
 *          8bit timer example in ATMega328
 * 
 ******************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

void setUpIO(void);

/***********************
* MAIN FUNCTION JJJJJJ *
***********************/
int main() {
  setUpIO();  // Set up all IO ports
  CLKPR =(0x80);
  CLKPR =(0x01);
  initTimerCTC();

  SREG |= (0x80); // Enable global interrupts 
  
  // Main loop, nothing here :)
  while(1){
  }
  
  return 0;
}

//
// Init timer at CTC mode
//
void initTimerCTC(void){
  TCCR0A |= (0X00); // set ctc mode and none about pwm

  // Configurar el preescalador en 1024
  TCCR0B |= (0x01);

  //OCR0A = ;  // time 
  TIMSK0 |= (0x01); // Enable interrupts for ovf comparator
}

//
// Configure IO ports
//
void setUpIO(void){
  //    Config Port D 
  //- PIN13 (output)
  DDRB |= (1 << DDB5);
}

//
// ISR handler for timer0 ovf pins
//
ISR(TIMER0_OVF_vect){
  PORTB ^= (1 << PORTB5);// Toggle pin 13
}
