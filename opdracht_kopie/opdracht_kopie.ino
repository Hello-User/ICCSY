
#include "functies.h"

void initUsart();
void writeString(char* s);
void initServo();
void initSensor();
int main() {
    initUsart();  
    writeString("Welkom bij het regeltechniek practicum.");
    PORTB |= (1 << PB0); //Zet de servo schakelaar aan
    initServo(); 
    OCR1A = 1; //zet de dutycycle
    _delay_ms(1000);
    OCR1A = 1300;
    _delay_ms(1000);
    OCR1A = 2340;
    _delay_ms(1000);
    while(1);
   return 0;
}
void initServo() {
  TCCR1A |= (1 << WGM11) | (1 << COM1A1); //Deel 1 van de mode select (PHASE CORRECT PWM met top op ICR1)
  TCCR1B |= (1 << WGM13) | (1 << CS11); //Deel 2 van de mode select en prescaler op 8, want 16000000/50 = 320000 > 65536, 16000000 / 8 = 2000000/50 = 40000 < 65536
  ICR1 = 20000; //ICR1 berekent met FPWM = FCLK / (2 * N * TOP), dus TOP = FCLK / FPWM * 2 * N, waar FCLK = 16000000, N = 8 (prescaler).
  DDRB |= (1 << PB1) | (1 << PB0);
}

void initSensor() {
  
}
uint16_t leesSensorWaarde() {
  
}
