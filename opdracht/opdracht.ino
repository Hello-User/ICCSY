#include "functies.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>

void initUsart();
void writeString(char* s);
void initServo();
void initSensor();

volatile double distance;

int main() {
    float Vin;
    float cm, e;
    float midden = 19;
    float P,I,D,PID;
    float time1 = 1,prevCm,v,prevTime;
    float set;
    P = 0;
    I = 0;
    D = 0;
    initServo();
    initUsart();
    initSensor();
    PORTB |= (1 << PB0) | (1 << PB1);
    ADCSRA |= (1<<ADSC);
    while(1){
      Vin = (distance*5.0)/1024.0; //Volt conversion. Geen phase shift.
      cm = 13.0*(1.0/Vin); //conversion to cm. Geen filters.
      e = (midden - cm);
      P = 25 * e;
      v = (cm - prevCm)/(time1*0.001 - prevTime*0.001);
      D = -10 * v;
      I = 0.02 * e * time1*0.0001;
      _delay_ms(50);
      PID = P + I + D;
      set = PID + 1350;
      //Serial.println(I);
      if (cm > (midden - 1) && cm < (midden + 1)){ 
        OCR1A = 1350;
      }
      else{
        OCR1A = set;
      }
      prevCm = cm;
      prevTime = time1;
      time1 += 50;
    }
}
void initServo() 
{
    DDRB |= (1<<PB0) | (1<<PB1);
    TCCR1A |= (1 << WGM11) | ( 1 << COM1A1);
    TCCR1B |= (1 << WGM13) | (1 << CS11);
    ICR1 = 20000;
    //OCR1A = 1700;
}
void initSensor() {
    ADMUX |= 0b01000000;
    ADCSRA = (1 << ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) | (1<<ADIE); //1024 scale factor
    sei();
}

ISR(ADC_vect){
   distance = ADC;
   ADCSRA |= (1<<ADSC);
}
