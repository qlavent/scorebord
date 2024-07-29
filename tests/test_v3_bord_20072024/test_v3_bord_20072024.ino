#include <FastLED.h>

// make some variables to control the LEDs
#define NUM_LEDS 192
#define LED_PIN 2
#define MAX_POWER_MILLIAMPS 500
CRGB leds[NUM_LEDS];
int SPARTA_color[] = {255,0,0};
int TIME_color[] = {255,0,0};
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

// variables to control the own score
int own_score;

// variables to control the time
unsigned long startSeconds;  //some global variables available anywhere in the program
unsigned long currentSeconds;
const unsigned long period = 60;  // tick every second
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
  startSeconds = seconds16();
  paused = true;
  opponent_score = 0;

}
void loop() {
  for(int i = 0; i<192;i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(4000);
  for(int i = 0; i<32;i++){
    for (int j = 0;j<6;j++){
      leds[i*6+j] = CRGB::White;
    }
    FastLED.show();
    delay(500);
    for (int j = 0;j<6;j++){
      leds[i*6+j] = CRGB::Black;
    }
    FastLED.show();
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
  }

}
