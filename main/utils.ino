#include <stdarg.h>

void SerialPrintf(const char *fmt, ... ) { // resulting string limited to 128 chars// resulting string limited to 128 chars
#ifdef LOGGING
   char buf[128]; 
   va_list args; 
   va_start (args, fmt ); 
   vsnprintf(buf, 128, fmt, args); 
   va_end (args);
   Serial.print(buf);
#endif
}

// 3 килогерца, 250 миллисекунд
void highBeep() {
  tone(BEEPER_PIN, 3000, 250); 
  delay(250);
  noTone(BEEPER_PIN);
}

// 1 килогерц, 250 миллисекунд
void lowBeep() {
  tone(BEEPER_PIN, 1000, 250); 
  delay(250);
  noTone(BEEPER_PIN);
}


int blink_counter = REPEATED_BLINK_DELAY/LOOP_DELAY;

void blinkTimesForLoop(int nTimes) {
  if (--blink_counter > 0) return;
  blink_counter = REPEATED_BLINK_DELAY/LOOP_DELAY;
  
  for (int n = 0; n<nTimes; n++) {
      digitalWrite(LED_PIN, HIGH);
      delay(50);
      digitalWrite(LED_PIN, LOW);
      delay(50);
  }
}


int beep_counter = REPEATED_BEEP_DELAY/LOOP_DELAY;

void beepTimesForLoop(int nTimes) {
  if (--beep_counter > 0) return;
  beep_counter = REPEATED_BEEP_DELAY/LOOP_DELAY;
  
  for (int n = 0; n<nTimes; n++) {
      highBeep();
  }
}
