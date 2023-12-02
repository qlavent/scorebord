#include <FastLED.h>

// make some variables to control the LEDs
#define NUM_LEDS 320
#define LED_PIN 2
#define MAX_POWER_MILLIAMPS 8000
CRGB leds[NUM_LEDS];
SPARTA_color = {12, 126,64};
TIME_color = {255,0,0};
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
const unsigned long period = 1;  // tick every second
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
  FastLED.setBrightness(255);

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
  if (set_up){
    for(int i = 0; i<320;i++){
      leds[i-1] = CRGB::Black;
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(10);
    }
    
    for(int i = 318; i>-1;i--){
      leds[i+1] = CRGB::Black;
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(10);
    }
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
          if (own_score < 19) {
            own_score += 1;
          }
          Serial.write("ou");
          Serial.println();
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
          if (own_score > 0) {
            own_score -= 1;
          }
          
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
          if (paused == true && time_counter != 90) {
            paused = false;
            startSeconds = seconds16();
          }
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
          time_counter = 0;
          paused = true;

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
          if (opponent_score < 19) {
            opponent_score += 1;
          }
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
          if (opponent_score > 0) {
            opponent_score -= 1;
          }
        }
      }
    }

    currentSeconds = seconds16();                            //get the current "time" (actually the number of milliseconds since the program started)
    if (currentSeconds - startSeconds >= period && !paused)  //test whether the period has elapsed
    {
      if (time_counter == 44) {
        paused = true;
      } else if (time_counter == 89) {
        paused = true;
      }
      time_counter += 1;

      //printing the scorebord to the screen
      /*Serial.print(own_score);
      Serial.write("      ");
      Serial.print(time_counter);
      Serial.write("      ");
      Serial.print(opponent_score);
      Serial.println();

      Serial.print(own_score/10);
      Serial.print(own_score%10);
      Serial.write("      ");
      Serial.print(time_counter/10);
      Serial.print(time_counter%10);
      Serial.write("      ");
      Serial.print(opponent_score/10);
      Serial.print(opponent_score%10);
      Serial.println();*/

      startSeconds = currentSeconds;  //IMPORTANT to save the start time of the current LED state.
    }
    
    // code for eventually showing the numbers on the led display
    // control the single one
    for (int i = 0; i < 20; i++) {

      if (own_score>9) {
        if (own_score > 9 || opponent_score > 9) {
          leds[i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
          //leds[i] = CRGB::Blue;
        } else {
          leds[i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
          //leds[i] = CRGB::Red;
        }
      } else {
        leds[i] = CRGB::Black;
      }
    }
    // control own_score
    for (int i = 0; i < 70; i++) {
      if (numbers_full[own_score % 10][i/10]) {
        if (own_score > 9 || opponent_score > 9) {
          leds[20+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
          //leds[20 + i] = CRGB::Blue;
        } else {
          leds[20+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
          //leds[20 + i] = CRGB::Red;
        }
      } else {
        leds[20 + i] = CRGB::Black;
      }
    }
    // control first digit time
    for (int i = 0; i < 70; i++) {
      if (numbers_full[time_counter / 10][i/10] == 1) {
        leds[90 + i].setRGB(TIME_color[0], TIME_color[1], TIME_color[2]);
        //leds[90+i] = CRGB::Red;
      } else {
        leds[90 + i] = CRGB::Black;
      }
    }
    // control second digit time
    for (int i = 0; i < 70; i++) {
      if (numbers_full[time_counter % 10][i/10] == 1) {
        leds[160 + i].setRGB(TIME_color[0], TIME_color[1], TIME_color[2]);
        //leds[160 + i] = CRGB::Red;
      } else {
        leds[160 + i] = CRGB::Black;
      }
    }
    // control one of opponent score
    for (int i = 0; i < 20; i++) {
      if (opponent_score>9) {
        if (own_score > 9 || opponent_score > 9) {
          leds[230+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
          //leds[230 + i] = CRGB::Blue;
        } else {
          leds[230+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
          //leds[230 + i] = CRGB::Red;
        }
      } else {
        leds[230 + i] = CRGB::Black;
      }
    }
    // control opponent_score
    for (int i = 0; i < 70; i++) {
      if (numbers_full[opponent_score % 10][i/10] == 1) {
        if (own_score > 9 || opponent_score > 9) {
          leds[250+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
          //leds[250 + i] = CRGB::Blue;
        } else {
          leds[250+i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
          //leds[250 + i] = CRGB::Red;
        }
      } else {
        leds[250 + i] = CRGB::Black;
      }
    }
    
    //delay(50);

    lastButtonState_own_score_down = reading_own_score_down;
    lastButtonState_own_score_up = reading_own_score_up;
    lastButtonState_pause_time = reading_pause_time;
    lastButtonState_reset_time = reading_reset_time;
    lastButtonState_opponent_score_down = reading_opponent_score_down;
    lastButtonState_opponent_score_up = reading_opponent_score_up;

    FastLED.show();
  }
}
