#include <FastLED.h>

// make some variables to control the LEDs
#define NUM_LEDS 192
#define LED_PIN 2
#define MAX_POWER_MILLIAMPS 8000
CRGB leds[NUM_LEDS];
int SPARTA_color[] = {255,0,0};
int TIME_color[] = {0,255,255};
bool numbers_full[][7] = 
{
  {true, true, true, false, true, true, true},
  {false,false,true, false, false,false,true},
  {true, true, false, true, false, true, true},
  { false, true, true,true, false, true, true},
  {false, false, true, true, true,false,true},
  {false, true, true, true, true, true, false},
  {true,true,true,true,true,true,false},
  {false, false, true, false, false,true, true},
  {true,true,true,true,true,true,true,},
  {false,true,true,true,true,true,true,}
};

bool numbers_full_time[][7] = 
{
  {true, true, true, false, true, true, true},
  {false,false,true, false, false,false,true},
  {false, true, true, true, true, true, false},
  { false, true, true,true, false, true, true},
  {true, false, true, true, false,false,true},
  {true, true, false, true, false, true, true},
  {true,true,false,true,true,true,true},
  {false, true, true, false, false,false, true},
  {true,true,true,true,true,true,true,},
  {true,true,true,true,false,true,true,}
};
// variables to control the own score
int own_score;

// variables to control the time
unsigned long startSeconds;  //some global variables available anywhere in the program
unsigned long currentSeconds;
const unsigned long period = 60000;  // tick every second
int time_counter;
bool paused;

// variables to control the opponents score
int opponent_score;

// initialization of the buttons and debounce variables
int switchstate_own_score_down = 0;
int switchstate_own_score_up = 0;
int switchstate_pause_time = 0;
int switchstate_reset_time = 0;
int switchstate_opponent_score_down = 0;
int switchstate_opponent_score_up = 0;

int lastButtonState_own_score_down = LOW;
int lastButtonState_own_score_up = LOW;
int lastButtonState_pause_time = LOW;
int lastButtonState_reset_time = LOW;
int lastButtonState_opponent_score_down = LOW;
int lastButtonState_opponent_score_up = LOW;

unsigned long lastDebounceTime_own_score_down = 0;
unsigned long lastDebounceTime_own_score_up = 0;
unsigned long lastDebounceTime_pause_time = 0;
unsigned long lastDebounceTime_reset_time = 0;
unsigned long lastDebounceTime_opponent_score_down = 0;
unsigned long lastDebounceTime_opponent_score_up = 0;

unsigned long debounceDelay = 20;

bool buttons_pressed[6] = {false,false,false,false,false,false};

bool set_up = true;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_POWER_MILLIAMPS);
  //FastLED.setBrightness(255);

  Serial.begin(9600);

  // declare the switch pin as an input
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

  own_score = 0;
  time_counter = 0;
  startSeconds = millis();
  paused = true;
  opponent_score = 0;
}
void loop() {
  if (set_up){
    
    for(int i = 0; i<192;i++){
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(300);
    for(int i = 0; i<32;i++){
      for (int j = 0;j<6;j++){
        leds[i*6+j] = CRGB::Red;
      }
      FastLED.show();
      delay(500);
      for (int j = 0;j<6;j++){
        leds[i*6+j] = CRGB::Black;
      }
      FastLED.show();
      delay(100);
    }
    for(int i = 0; i<32;i++){
      for (int j = 0;j<6;j++){
        leds[i*6+j] = CRGB::Cyan;
      }
      FastLED.show();
      delay(500);
      for (int j = 0;j<6;j++){
        leds[i*6+j] = CRGB::Black;
      }
      FastLED.show();
      delay(100);
    }
    for(int i = 0; i<192;i++){
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(300);
    set_up = false;
  }

  else{

    // actions of the button for own score up
    int reading_own_score_up = digitalRead(3);

    if (reading_own_score_up != lastButtonState_own_score_up) {
      // reset the debouncing timer
      lastDebounceTime_own_score_up = millis();
    }
    if ((millis() - lastDebounceTime_own_score_up) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading_own_score_up != switchstate_own_score_up) {
        switchstate_own_score_up = reading_own_score_up;

        // only toggle the LED if the new button state is HIGH
        if (switchstate_own_score_up == HIGH) {
          buttons_pressed[0]= true;
        }
      }
    }

    int reading_own_score_down = digitalRead(4);

    if (reading_own_score_down != lastButtonState_own_score_down) {
      // reset the debouncing timer
      lastDebounceTime_own_score_down = millis();
    }
    if ((millis() - lastDebounceTime_own_score_down) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:
      // if the button state has changed:
      if (reading_own_score_down != switchstate_own_score_down) {
        switchstate_own_score_down = reading_own_score_down;
        // only toggle the LED if the new button state is HIGH
        if (switchstate_own_score_down == HIGH) {
          buttons_pressed[1]= true;        
        }
      }
    }

    // actions of the button for starting the time
    int reading_pause_time = digitalRead(5);

    if (reading_pause_time != lastButtonState_pause_time) {
      // reset the debouncing timer
      lastDebounceTime_pause_time = millis();
    }
    if ((millis() - lastDebounceTime_pause_time) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading_pause_time != switchstate_pause_time) {
        switchstate_pause_time = reading_pause_time;

        // only toggle the LED if the new button state is HIGH
        if (switchstate_pause_time == HIGH) {
          buttons_pressed[2]= true;
        }
      }
    }

    // actions of the button for resetting the time
    int reading_reset_time = digitalRead(6);

    if (reading_reset_time != lastButtonState_reset_time) {
      // reset the debouncing timer
      lastDebounceTime_reset_time = millis();
    }
    if ((millis() - lastDebounceTime_reset_time) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading_reset_time != switchstate_reset_time) {
        switchstate_reset_time = reading_reset_time;

        // only toggle the LED if the new button state is HIGH
        if (switchstate_reset_time == HIGH) {
          buttons_pressed[3]= true;
        }
      }
    }

    // actions of the button for own score down
    int reading_opponent_score_up = digitalRead(7);

    if (reading_opponent_score_up != lastButtonState_opponent_score_up) {
      // reset the debouncing timer
      lastDebounceTime_opponent_score_up = millis();
    }
    if ((millis() - lastDebounceTime_opponent_score_up) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading_opponent_score_up != switchstate_opponent_score_up) {
        switchstate_opponent_score_up = reading_opponent_score_up;

        // only toggle the LED if the new button state is HIGH
        if (switchstate_opponent_score_up == HIGH) {
          buttons_pressed[4]= true;
        }
      }
    }

    // actions of the button for own score down
    int reading_opponent_score_down = digitalRead(8);

    if (reading_opponent_score_down != lastButtonState_opponent_score_down) {
      // reset the debouncing timer
      lastDebounceTime_opponent_score_down = millis();
    }
    if ((millis() - lastDebounceTime_opponent_score_down) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading_opponent_score_down != switchstate_opponent_score_down) {
        switchstate_opponent_score_down = reading_opponent_score_down;

        // only toggle the LED if the new button state is HIGH
        if (switchstate_opponent_score_down == HIGH) {
          buttons_pressed[5]= true;
        }
      }
    }

    bool changed = false;
    if (!paused && (millis() - startSeconds >= period)) {
      startSeconds = millis();
      time_counter++;
      changed = true;

      if (time_counter == 45 || time_counter == 90) {
        paused = true;
      }
    }

    if (buttons_pressed[0] == true){
      if (own_score < 19) {
        own_score += 1;
        changed = true;
      }
    }
    if (buttons_pressed[1] == true){
      if (own_score > 0) {
        own_score -= 1;
        changed = true;
      }
    }
    if (buttons_pressed[2] == true){
      if (paused == true && time_counter != 90) {
        paused = false;
        startSeconds = millis();
      }
    }
    if (buttons_pressed[3] == true){
      time_counter = 0;
      paused = true;
      changed = true;
    }
    if (buttons_pressed[4] == true){
      if (opponent_score < 19) {
        opponent_score += 1;
        changed = true;
      }
    }
    if (buttons_pressed[5] == true){
      if (opponent_score > 0) {
        opponent_score -= 1;
        changed = true;
      }
    }

    buttons_pressed[0] = false;
    buttons_pressed[1] = false;
    buttons_pressed[2] = false;
    buttons_pressed[3] = false;
    buttons_pressed[4] = false;
    buttons_pressed[5] = false;

    if (changed){
      // code for eventually showing the numbers on the led display
      // control the single one
      for (int i = 0; i < 12; i++) {
        if (own_score>9) {
          leds[i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
        } else {
          leds[i] = CRGB::Black;
        }
      }
      // control own_score
      for (int i = 0; i < 42; i++) {
        if (numbers_full[own_score % 10][i/6]) {
          leds[12+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
        } else {
          leds[12 + i] = CRGB::Black;
        }
      }
      // control first digit time
      for (int i = 0; i < 42; i++) {
        if (numbers_full_time[time_counter / 10][i/6] == 1) {
          leds[54 + i].setRGB(TIME_color[0], TIME_color[1], TIME_color[2]);
          //leds[90+i] = CRGB::Red;
        } else {
          leds[54 + i] = CRGB::Black;
        }
      }
      // control second digit time
      for (int i = 0; i < 42; i++) {
        if (numbers_full[time_counter % 10][i/6] == 1) {
          leds[96 + i].setRGB(TIME_color[0], TIME_color[1], TIME_color[2]);
          //leds[160 + i] = CRGB::Red;
        } else {
          leds[96 + i] = CRGB::Black;
        }
      }
      // control one of opponent score
      for (int i = 0; i < 12; i++) {
        if (opponent_score>9) {
          leds[138+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
        } else {
          leds[138 + i] = CRGB::Black;
        }
      }
      // control opponent_score
      for (int i = 0; i < 42; i++) {
        if (numbers_full[opponent_score % 10][i/6] == 1) {
          leds[150+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
        } else {
          leds[150 + i] = CRGB::Black;
        }
      }
      FastLED.show();
    }
    
    //delay(50);

    lastButtonState_own_score_down = reading_own_score_down;
    lastButtonState_own_score_up = reading_own_score_up;
    lastButtonState_pause_time = reading_pause_time;
    lastButtonState_reset_time = reading_reset_time;
    lastButtonState_opponent_score_down = reading_opponent_score_down;
    lastButtonState_opponent_score_up = reading_opponent_score_up;
  }
}
