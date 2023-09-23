#include <Arduino.h>

#define FASTLED_INTERNAL
#include <FastLED.h>

//#define NUM_LEDS 210
#define NUM_LEDS 75
#define MARKS 1

uint8_t brightness = 0;
uint8_t hue = 0;
uint8_t d_hue = 10;

//uint32_t d_time = 15;
unsigned long d_time = 150;
unsigned long t_e;

uint32_t elapsed[NUM_LEDS];

CRGB leds[NUM_LEDS];

CRGB src_led_colors[NUM_LEDS];
CRGB tar_led_colors[NUM_LEDS];

uint8_t brightness_arr[NUM_LEDS];
uint8_t hue_arr[NUM_LEDS];

int cur_led[MARKS];
unsigned long move_t;

int b_count = 0;


void setup() { 
  FastLED.addLeds<NEOPIXEL, 22>(leds, NUM_LEDS);
  /*
  for(int i = 0; i < MARKS; i++){
    cur_led[i] = int (i*NUM_LEDS / MARKS);
    leds[cur_led[i]].setHSV(hue, 255, 150);
  }
  move_t = millis();
  */
  fill_rainbow_circular(leds, NUM_LEDS, hue);
  fill_rainbow_circular(src_led_colors, NUM_LEDS, hue);
  hue+=d_hue;
  fill_rainbow_circular(tar_led_colors, NUM_LEDS, hue);
  FastLED.show();
  delay(1);
}

void loop() {
  /*
  t_e = millis() - move_t;
  if(t_e > d_time){
    for(int mark = 0; mark < MARKS; mark++){
      //for(int i = 0; i < NUM_LEDS; i++){ 
      //  brightness_arr[i] = uint8_t (brightness_arr[i] / 1.001);
      //}
      
      hue+=d_hue;
      cur_led[mark]++;
      if (cur_led[mark] >= NUM_LEDS){
        cur_led[mark] = 0;
      }
      hue_arr[cur_led[mark]] = hue;
      brightness_arr[cur_led[mark]] = 150;
    }
  }

  for(int i = 0; i < NUM_LEDS; i++){
    CHSV color_HSV = CHSV(hue_arr[i], 255, brightness_arr[i]);
    CRGB color_RGB;
    hsv2rgb_rainbow(color_HSV, color_RGB);
    tar_led_colors[i] = color_RGB;
  }

  for(int i = 0; i < NUM_LEDS; i++){
    if(elapsed[i] < 1792){
      fract8 frac = elapsed[i]/2048;
      leds[i] = blend(src_led_colors[i], tar_led_colors[i], frac);
    }else{
      leds[i] = tar_led_colors[i];
    }
  }
  */
  if(b_count >= d_time){
    b_count = 0;
    hue += d_hue;
    //for(int i = 0; i < NUM_LEDS; i++){
      //src_led_colors[i] = tar_led_colors[i];
    //}
    fill_rainbow_circular(tar_led_colors, NUM_LEDS, hue);
  }

  nblend(leds, tar_led_colors, NUM_LEDS, b_count*(256/d_time));
  
  FastLED.show(); 
  b_count++;
  delay(1);
}

