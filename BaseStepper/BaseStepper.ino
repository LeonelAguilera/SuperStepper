/*Control de motor paso a paso bipolar sin drivers (Solo Arduino UNO y puente H) sin micropasos y con micropasos de 1/2
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

byte IN1 = 10;
byte IN2 = 11;
byte IN3 = 12;
byte IN4 = 13;

byte i = 0;

bool pasos[4][4] = {
  {1, 0, 1, 0},
  {0, 1, 1, 0},
  {0, 1, 0, 1},
  {1, 0, 0, 1}
}

bool micropasos[8][4] = {
  {1, 0, 0, 0},
  {1, 0, 1, 0},
  {0, 0, 1, 0},
  {0, 1, 1, 0},
  {0, 1, 0, 0},
  {0, 1, 0, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
}

int T = 500;

void setup() {
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
}

void loop() {
  digitalWrite(A1, micropasos[i%8][0]);
  digitalWrite(A2, micropasos[i%8][1]);
  digitalWrite(B1, micropasos[i%8][2]);
  digitalWrite(B2, micropasos[i%8][3]);

  i++;
  delayMicroseconds(T);
}
