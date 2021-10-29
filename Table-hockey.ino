
//set physical pinout
#define buzzer_pin 10
byte segment_buffer[2] = {255, 255};
const byte seg_pins[7] = {11,12,3,7,4,9,8}; // order gfedcba
const byte disp_pins[2] = {5,6}; //least significant digit first.
/*
 * pin - char
 * 4 - e
 * 7 - d
 * 8 - g
 * 9 - f
 * 11 - a
 * 12 - b
 * 3 - c
 */
//fonts, convert a digit to segments
const PROGMEM byte digits[] = {
  //gfedcba
  0b0111111,  // 0
  0b0000110,  // 1
  0b1011011,  // 2
  0b1001111,  // 3
  0b1100110,  // 4
  0b1101101,  // 5
  0b1111101,  // 6
  0b0100111,  // 7
  0b1111111,  // 8
  0b1101111   // 9
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
    digitalWrite(seg_pins[i], bitRead(segments, i));
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
    delay(1000);
    digitalWrite(disp_pins[i], HIGH);
  }
  //turn off at last segment
  write_segments(0);
}

void setup() {
  Serial.begin(9600);
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
  //write_digits(00);
  digitalWrite(disp_pins[0], 1);
  digitalWrite(disp_pins[1], 1);
  //write_digits(69);
}

void loop() {
  // put your main code here, to run repeatedly:
  update_display();
}
