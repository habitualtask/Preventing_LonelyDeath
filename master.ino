int piezoPin = 3;
unsigned long time_prev, time_previous, time_current;
int minutes=0,seconds=20;

byte patterns[]{
  0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE4,0xFE,0xE6
};
int digit_select_pin[]= {53,51,49,47};   
int segment_pin[]={45,43,41,39,37,35,33,31};
int SEGMENT_DELAY=5;

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++){
    pinMode(digit_select_pin[i],OUTPUT);
  }for(int i=0;i<8;i++){
    pinMode(segment_pin[i],OUTPUT);
  }
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(piezoPin, OUTPUT);
  time_previous=millis();
  time_prev = millis();
}

void show_digit(int pos,int number){
  for(int i=0;i<4;i++){
    if(i+1==pos)
      digitalWrite(digit_select_pin[i],LOW);
    else
      digitalWrite(digit_select_pin[i],HIGH);
  }
  for(int i=0;i<8;i++){
    boolean on_off=bitRead(patterns[number],7-i);
    digitalWrite(segment_pin[i],on_off);
  }
  
}

void show_4_digit(int number){

  number=number%10000;
  int thousands=number/1000;
  number=number%1000;
  int hundreads=number/100;
  number=number%100;
  int tens=number/10;
  int ones=number%10;

  show_digit(1,thousands);
  delay(SEGMENT_DELAY);
  show_digit(2,hundreads);
  delay(SEGMENT_DELAY);
  show_digit(3,tens);
  delay(SEGMENT_DELAY);
  show_digit(4,ones);
  delay(SEGMENT_DELAY);
}

void loop() {
  if(Serial1.available() > 0){
    char c = Serial1.read();
    if(c == 'O') {
      Serial.println(c);

      time_current = millis();
      time_prev = time_current;

      minutes=0;
      seconds=20;
    }
  }
  time_current = millis();

  if (time_current - time_prev >= 20000) {
    for(int freq = 150; freq <=1800; freq = freq + 2) {
      tone(piezoPin, freq, 10);
    }
    for(int freq = 1800; freq <=150; freq = freq - 2) {
      tone(piezoPin, freq, 10);
    }
  }
  // put your main code here, to run repeatedly:
  
  time_current=millis();
  if(time_current-time_previous>=1000){
    time_previous=time_current;
    seconds--;
    if(seconds==0){
      //seconds=0;
      minutes--;
    }
    if(minutes==60) minutes=0;
  }
  show_4_digit(minutes*100+seconds);
}
