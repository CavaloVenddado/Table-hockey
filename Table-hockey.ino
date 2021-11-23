#include <Servo.h>

//set physical pinout
#define btn_pin 2
#define buzzer_pin 10
#define esc1_pin 0
#define esc2_pin 0
byte segment_buffer[2] = {0,0};
const byte seg_pins[7] = {11,12,3,7,4,9,8}; // order gfedcba
const byte disp_pins[2] = {5,6}; //least significant digit first.
unsigned long current_milis;
unsigned long press_milis;
unsigned long release_milis;
bool last_button_state;
bool current_button_state;
Servo esc1;
Servo esc2;
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
  //this code writes the buffer to the display, one digit at a time. must run repeatedly for persistance of vision to take effect.
  for (int i = 0; i <= 1; i++) {
    //write every segment
    digitalWrite(disp_pins[i], HIGH);
    write_segments(segment_buffer[i]);
    delay(10);//not good prectice. use millis instead.
    digitalWrite(disp_pins[i], LOW);
  }
  //turn off at last segment
  write_segments(0);
}

void setup() {
  // set pin modes
  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
  for (int i = 0; i <= 1; i++) {
    pinMode(disp_pins[i], OUTPUT);
  }
  for (int i = 0; i <= 6; i++) {
    pinMode(seg_pins[i], OUTPUT);
  }

  esc1.attach(esc1_pin);
  esc2.attach(esc2_pin);
  
  // startup chime
  tone(buzzer_pin, 262);
  delay(200);
  tone(buzzer_pin, 329);
  delay(200);
  tone(buzzer_pin, 391, 200);
}

void on_press(){
  
}
void on_long_press(){
  
}

void loop() {
  update_display(); //locks the processor. Could be better.
  //TODO: detect OnPress event for buttons and for puck detection
  //get current time and input states.
  current_milis = millis();
  current_button_state = !digitalRead(btn_pin);
  //detect onPress
  if(current_button_state != last_button_state and current_button_state == true){
    pressed_time = current_milis;
  }
  last_button_state = current_button_state;
}
