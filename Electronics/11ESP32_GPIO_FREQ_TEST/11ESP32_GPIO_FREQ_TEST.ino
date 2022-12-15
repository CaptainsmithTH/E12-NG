
uint8_t DATA[256];
uint8_t dutyCycle = 200;

void setup() {
  pinMode(15,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(2,OUTPUT);
  digitalWrite(15,HIGH);
  for(uint16_t i = 0 ;i<256;i++){
    if(i<=dutyCycle){
      DATA[i] = 0;
    }
    else{
      DATA[i] = 255;
    }
  }
}


void writeReg(uint8_t j){
  GPIO.out_w1tc = (1<<15);
  for(uint8_t i = 0;i<8;i++){
    GPIO.out_w1tc = (1<<2);
    digitalWrite(4,(DATA[j] >> i) & 1);
    GPIO.out_w1ts = (1<<2);
  }
  GPIO.out_w1ts = (1<<15);
}

void loop() {
  for(uint16_t i = 0 ;i<256;i++){
    writeReg(i);
  }
}
