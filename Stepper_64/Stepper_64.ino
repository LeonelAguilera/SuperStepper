/*Control de motor paso a paso bipolar sin drivers (Solo Arduino UNO y puente H) con micropasos de 1/64
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

byte i = 0;

unsigned int count = 0;

byte o_A1 = 10;
byte o_A2 = 11;
byte o_B1 = 12;
byte o_B2 = 13;

byte ENA = 5;
byte ENB = 6;

bool flag;

byte ENAV[256];
byte ENBV[256];

void setup(){
  pinMode(o_A1, OUTPUT);
  pinMode(o_A2, OUTPUT);
  pinMode(o_B1, OUTPUT);
  pinMode(o_B2, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(2000000);
  Serial.println("Iniciando inicialización");

  for(int j = 0; j < 256; j++){
    ENAV[j] = (byte)255*abs(sin((float)j/40.74));
    Serial.print(ENAV[j]);
    Serial.print(", ");
    ENBV[j] = (byte)255*abs(sin((float)(j+64)/40.74));
  }
  Serial.println("Inicialización terminada");
}

void loop(){
  digitalWrite(o_A1, i > 127);
  digitalWrite(o_A2, i < 127);
  digitalWrite(o_B1, (i+64)%255 > 127);
  digitalWrite(o_B2, (i+64)%255 < 127);
  analogWrite(ENA, ENAV[i%256]);
  analogWrite(ENB, ENBV[i%256]);
  //delayMicroseconds(10);
  //delayMicroseconds(analogRead(A0)*5);
  i++;
  count++;
  //flag = !flag;
  //digitalWrite(8,flag);
  if(count > 12800){
    delay(10000);
  }
}
