/*****************************************************
 * 
 *            Noeww bre-metal Arduino :)
 *            
 *            ADC example in ATMega328
 * 
 ******************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

void setUpIO(void);
void setUpTimer0CTC(void);
void setUpADC0(void);

/***********************
* MAIN FUNCTION JJJJJJ *
***********************/
int main() {
  setUpIO();  // Set up all IO ports
  CLKPR =(0x80);
  CLKPR =(0x01);
  setUpTimer0CTC();
  setUpADC0();

  SREG |= (0x80); // Enable global interrupts 
  
  // Main loop, nothing here :)
  while(1){
  }
  
  return 0;
}

//
// Init timer at CTC mode
//
void setUpTimer0CTC(void){
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
// Configure ADC 
//
void setUpADC0(void){
  ADMUX |= (1 << ADLAR);  // Read just 8bits (just one register)
  ADCSRA |= 0xE8; // Active all configs of ADC...
  ADCSRB |= 0x04; // Active the interrupt for Timer0 overflow interrupt
}

//
// ISR handler for ADC
//
ISR(ADC_vect){
  if (ADCH < 128) 
    PORTB ^= (1 << PORTB5);// Toggle pin 13
}

