byte IN1 = 10;
byte IN2 = 11;
byte IN3 = 12;
byte IN4 = 13;

byte i = 0;

bool pasos[4][4] = {
  {1, 0, 0, 0},
  {0, 0, 1, 0},
  {0, 1, 0, 0},
  {0, 0, 0, 1}
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
