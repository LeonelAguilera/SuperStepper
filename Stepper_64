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
