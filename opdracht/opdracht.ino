#include "functies.h"

void initUsart();
void writeString(char* s);
void initServo();
void initSensor();


int main() {
    initServo();
    initUsart();
    PORTB |= (1 << PB0) | (1 << PB1);
    writeString("Welkom bij het regeltechniek practicum.");
    sei();
    while(1){
    OCR1A = 2250;
    }
}
void initServo() 
{
    DDRB |= (1<<PB0) | (1<<PB1);
    TCCR1A |= (1 << WGM11) | ( 1 << COM1A1);
    TCCR1B |= (1 << WGM13) | (1 << CS11);
    ICR1 = 20000;
}

void initSensor() {
    ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE);
    
}
uint16_t leesSensorWaarde() {
  
}

ISR(ADC_Vector){
   
}
