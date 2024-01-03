#include "mytft.h"

TFT_eSPI tft = TFT_eSPI();

void mytft_init() {
  
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Hello.\nIt's LambDa.\n");

  tft.setTextSize(1);
  tft.println("Based on the principle of an inverse compound pendulum, I am a dynamically stable system.\n");
  tft.println("Unlike traditional robots, I maintain my balance at all times.\n");
  tft.println("This capability allows me to move on various and uneven surfaces, even on slopes.\n");
  tft.println("I am particularly space-saving and lightweight.\n");
  tft.println("Whether it's flat ground or rugged terrain, I can handle it with ease.\n");
  tft.println("I hope you'll appreciate my unique features!\n");

}
