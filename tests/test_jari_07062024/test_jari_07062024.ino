#include <FastLED.h>

// make some variables to control the LEDs
#define NUM_LEDS 40
#define LED_PIN 2
#define MAX_POWER_MILLIAMPS 400
CRGB leds[NUM_LEDS];
int SPARTA_color[] = {255,0,0};

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_POWER_MILLIAMPS);
  //FastLED.setBrightness(255);

  Serial.begin(9600);

}
void loop() {
  while(true){
    //sequentially put on the leds in strips of 4 for 5 seconds
    for(int i =0; i<NUM_LEDS/4; i++){
      for(int j =0; j<4;j++){
        leds[4*i+j].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
      }
      FastLED.show();
      delay(5000);
      for(int j =0; j<4;j++){
        leds[4*i+j] = CRGB::Black;
      }
      FastLED.show();
    }
    // turn all lights on for 5 seconds
    for(int i = 0;i<NUM_LEDS; i++){
      leds[i].setRGB(SPARTA_color[0], SPARTA_color[1], SPARTA_color[2]);
    }
    FastLED.show();
    delay(5000);

    for(int i = 0;i<NUM_LEDS; i++){
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(5000);
    
  }
}
