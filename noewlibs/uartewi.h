/*****************************************************
 * 
 *            Noeww bare-metal Arduino :)
 *            
 *             UART example in ATMega328
 * 
 ******************************************************/

// Configura la UART con la velocidad de baudios deseada
void uart_init(unsigned long baudrate) { 
    unsigned int ubrr = (F_CPU / 16 / baudrate) - 1;    // Calcular el valor del baud rate register
    
    UBRR0H = (unsigned char)(ubrr >> 8); 
    UBRR0L = (unsigned char)ubrr; 
     
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);   // Habilitar tx y rx
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Formato de datos x defecto 8n1
}

// 
// Send a single byte
//
void uartSendByte(unsigned char data) {
    // Wait till the tx buffer get empty
    while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = data;    // Send the data
}

//
// Send a complete string
//
void uartSendStr(const char *str) {
    while (*str) 
        uartSendByte(*str++);
}