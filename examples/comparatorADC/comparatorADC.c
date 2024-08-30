/*****************************************************
 * 
 *            Noeww bre-metal Arduino :)
 *            
 *            ADC example in ATMega328
 * 
 ******************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/noewiLib/uartewi.h>

char msg[5];

void setUpIO(void);
void setUpTimer0CTC(void);
void setUpADC0(void);

/***********************
* MAIN FUNCTION JJJJJJ *
***********************/
int main() {
  setUpIO();  // Set up all IO ports
  uart_init(9600);

  CLKPR =(0x80);
  CLKPR =(0x01);
  //setUpTimer0CTC();
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
  ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE); // Active all configs of ADC, ADEN to 0 for cmp
  ADCSRB |= (1 << ACME) | (1 << ADTS1); // Active analog comparator mode
  ACSR |= (1 << ACIS1) | (1 << ACIE); //Falling edge
}

//
// ISR handler for ADC
//
ISR(ANALOG_COMP_vect){
  //if (adcValue < 128) 
  PORTB ^= (1 << PORTB5);// Toggle pin 13
  msg[1] = ADCH;
  msg[2] = '\n';
  const char *message = "Hola puta\n";
  uartSendStr(message);
}