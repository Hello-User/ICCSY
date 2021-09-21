#include "functies.h"

void initUsart();
void writeString(char* s);
void initServo();
void initSensor();

uint16_t distance;

int main() {
    initServo();
    initUsart();
    initSensor();
    PORTB |= (1 << PB0) | (1 << PB1);
    writeString("Welkom bij het regeltechniek practicum.");
    sei();
    while(1){
    OCR1A = 1500;
    writeInt(distance);
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
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2) | (1 << ADSC);  //moet nog op 128 bits
}
uint16_t leesSensorWaarde() {
  
}

ISR(ADC_Vector){
   distance = ADC;
}
