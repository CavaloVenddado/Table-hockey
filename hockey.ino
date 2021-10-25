
//set physical pinout
#define buzzer_pin 10
byte segment_buffer[2] = {0, 0};
const PROGMEM byte seg_pins[7] = {0,0,0,0,0,0,0}; // order gfedcba
const PROGMEM byte disp_pins[2] = {0,0}; //least significant digit first.

//fonts, convert a digit to segments
const PROGMEM byte digits[] = {
  //gfedcba
  0b1000000,  // 0
  0b1111001,  // 1
  0b0100100,  // 2
  0b0110000,  // 3
  0b0011001,  // 4
  0b0010010,  // 5
  0b0000010,  // 6
  0b1011000,  // 7
  0b0000000,  // 8
  0b0010000   // 9
};

void write_segments(byte segments){
  /*
   * a byte stores 8 bits, in this code we set each bit with a specific segment, least significant = a
   * writes the byte to hardware.
   * 0b01010101
   *    |||||||
   *    gfedcba
   * 
   * example:
   *  HH 
   * L  L
   * L  L
   *  HH 
   * H  H
   * H  H
   *  LL 
   */
  for (int i = 0; i <= 6; i++) {
    digitalWrite(bitRead(segments, i), seg_pins[i]);
  }
}
void write_digits(byte n){
  //yu put da numba it go tru font and back to buffa!
  //black magic on the (n / 1U) % 10 no idea how it works.
  //this may be misnamed, as it does not actually write tothe display, but to the buffer.
  segment_buffer[0] = digits[(n / 1U) % 10];
  segment_buffer[1] = digits[(n / 10U) % 10];
}

void update_display(){
  //this code writes the buffer to the display, one digit at a time. must run repeatedly for persistance of vision to take effect
  for (int i = 0; i <= 1; i++) {
    //write every segment
    digitalWrite(disp_pins[i], LOW);
    write_segments(segment_buffer[i]);
    delay(1);
    digitalWrite(disp_pins[i], HIGH);
  }
  //turn off at last segment
  write_segments(0);
}

void setup() {
  // set pin modes
  pinMode(buzzer_pin, OUTPUT);
  for (int i = 0; i <= 1; i++) {
    pinMode(disp_pins[i], OUTPUT);
  }
  for (int i = 0; i <= 6; i++) {
    pinMode(seg_pins[i], OUTPUT);
  }
  // startup chime
  tone(buzzer_pin, 262);
  delay(200);
  tone(buzzer_pin, 329);
  delay(200);
  tone(buzzer_pin, 391, 200);
  write_digits(00);
}

void loop() {
  // put your main code here, to run repeatedly:
  update_display();
}
