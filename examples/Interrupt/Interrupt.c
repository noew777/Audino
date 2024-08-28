/*****************************************************
 * 
 *            Noeww bare-metal Arduino :)
 *            
 *          Interrupt example in ATMega328
 * 
 ******************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

void setUpInterrupts(void);
void setUpIO(void);

/***********************
* MAIN FUNCTION JJJJJJ *
***********************/
int main() {
  setUpInterrupts();  // Set up all interrupts
  setUpIO();  // Set up all IO ports

  SREG |= (0x80); // Enable global interrupts 
  
  // Main loop, nothing here :)
  while(1){
  }
  
  return 0;
}

//
// Configure P16-23 interrupts
//
void setUpInterrupts(void){
  //- PIN2 
  PCICR |= (0x04); // Enable interrupts for INT2
  PCMSK2 |= (0x04); // Select the mask
  
  //PCIFR |= (0x04);// Clear flags from INT2
}

//
// Configure IO ports
//
void setUpIO(void){
  //    Config Port D 
  //- PIN2 (input, pullup)
  DDRB |= (0x20); // 1output
  PORTD |= (0x04);  // 1pull-up
}

//
// ISR handler for P7-0 pins
//
ISR(PCINT2_vect){
  if(PIND & 0x04)
    PINB |= (0x20); // Toggles PB5(Pin 13)
  else
    PINB &= ~(0x20);
}
