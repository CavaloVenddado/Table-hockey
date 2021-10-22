
#define buzzer_pin 10
byte segment_buffer[2] = {0, 0};
const PROGMEM byte seg_pins[7] = {0,0,0,0,0,0,0};
const PROGMEM byte disp_pins[2] = {0,0};

void write_segments(byte segments){
  for (int i = 0; i <= 6; i++) {
    digitalWrite(bitRead(segments, i), seg_pins[i]);
  }
}

void update_display(){
  for (int i = 0; i <= 1; i++) {
    digitalWrite(disp_pins[i], LOW);
    write_segments(segment_buffer[i]);
    delay(1);
    digitalWrite(disp_pins[i], HIGH);
  }
  write_segments(0);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer_pin, OUTPUT);
  for (int i = 0; i <= 1; i++) {
    pinMode(disp_pins[i], OUTPUT);
  }
  for (int i = 0; i <= 6; i++) {
    pinMode(seg_pins[i], OUTPUT);
  }
  tone(10, 262);
  delay(200);
  tone(10, 329);
  delay(200);
  tone(10, 391, 200);
}

void loop() {
  // put your main code here, to run repeatedly:
  update_display();
}
