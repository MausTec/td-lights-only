#include "config.h"
#include "ThermalLights.h"
#include "OneButton.h"

#define TD_IDLE       0
#define TD_STARTUP    1
#define TD_LOOP       2

OneButton Enable(ENABLE_SW_PIN, HIGH, false);

ThermalLights Lights;
volatile byte state = TD_STARTUP;

void setup() {
  Lights.init();

  if (digitalRead(ENABLE_SW_PIN) == HIGH) {
    Enable.attachClick(goLoop);
    Enable.attachLongPressStart(goStartup); 
  } else {
    goLoop();
  }
}

void loop() {
  Enable.tick();
  
  switch(state) {
    case TD_STARTUP:
      Lights.blinkSwitch(1000, 300);
      break;
      
    case TD_LOOP:
      Lights.blinkSwitch(250, 100);
      Lights.nextSequence(1000);
      break;
  }
}

static void goLoop() {
  Lights.off();
  
  if (state == TD_STARTUP) {
    state = TD_LOOP;
  } else {
    state = TD_STARTUP;
  }
}

static void goStartup() {
  Lights.off();
    
  if (state == TD_LOOP) {
    state = TD_STARTUP;
  } else {
    state = TD_IDLE;
  }
}
