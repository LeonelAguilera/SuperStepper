/*Control de motor paso a paso bipolar sin drivers (Solo Arduino UNO y puente H) con micropasos de 1/256
    Copyright (C) 2022  Leonel Alejandro Aguilera Correia

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see https://www.gnu.org/licenses/gpl-3.0.html.
 */

#define PI 3.14159265359

unsigned int i = 0;

int sinList[512]; //Lista con los valores que toma la función seno para mayor velocidad de ejecución

void setup() {
  DDRB |= 0b00000110; //Pines 9 y 10 como OUTPUTS para ENA y ENB
  DDRD |= 0b00111100; //Pines 2, 3, 4 y 5 como OUTPUTS para IN1-4
  sinList_Init();
  TCCR1A &= 0b00001100; //Se limpia el registro A de control del Timer/Counter 1
  TCCR1B &= 0b00100000; //Se limpia el registro B de control del Timer/Counter 1
  TCCR1A |= 0b10100011; //Se definen los valores deseados en el registro A de control del Timer/Counter 1:
    //Reset salidas 0 y 1 del contador al hacer match y Set al reinicio de contador (Comportamiento normal de PWM
    //Modo de generación de onda puesto a "PWM de fase centrada de 10bits" (paso previo a "PWM rápido de 10bits")
  TCCR1B |= 0b00001001; //Se definen los valores deseados en el registro B de control del Timer/Counter 1:
    //Modo de generación de onda puesto a "PWM rápido de 10bits"
    //Preescalador de reloj puesto a 1 (no-preescalador)
}

void loop() {
  dar_paso();
  delayMicroseconds(4);
  i++; //Aumentar i para dar paso en un sentido, reducirlo para dar paso en el otro
}

inline void dar_paso(){
  PORTD &= ((bool)(i&0x0200)?0b11100011:0b11010011)|(((bool)((i+0x0100)&0x0200))?0b11001011:0b11000111); //Esto se encarga de escribir todos los IN del puente H según el punto del ciclo en el que se encuentre haciendo dos ondas cuadradas con desfase de 90º
  PORTD |= ((bool)(i&0x0200)?0b00100000:0b00010000)|(((bool)((i+0x0100)&0x0200))?0b00001000:0b00000100);
  OCR1AH = sinList[i&0x01FF]>>8; OCR1AL = sinList[i&0x01FF]&0x00FF; //Escritura de la salida analógica de ENA
  OCR1BH = sinList[(i+0x0100)&0x01FF]>>8; OCR1BL = sinList[(i+0x0100)&0x01FF]&0x00FF; //Escritura de la salida analógica de ENA
}

void sinList_Init(){
  for(int ListIndex = 0; ListIndex < 512; ListIndex++){
    sinList[ListIndex] = (int)round(1023*abs(sin(((float)ListIndex)*PI/512)));
  }
}
