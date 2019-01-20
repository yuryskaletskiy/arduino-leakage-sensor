/*
 * Файл логики, который по сути state machine.
 * описание смотри в main
 */


void changeState(int newState) {

  switch(newState) {
  
    case STATE_OPENED: {
      valveOpen();
    }; break;

    case STATE_CLOSED: {
      valveClose();
    }; break;

    case STATE_EMERG_CLOSED: {
      valveClose();
      lowBeep(); lowBeep(); lowBeep();
    }; break;
  }

  
  SerialPrintf("switched to state %d\n", newState);
  current_state = newState;
}

void displayState() {
  switch(current_state) {
    case STATE_JUST_STARTED: {
      blinkTimesForLoop(3); 
    }; break;

    case STATE_OPENED: {
      blinkTimesForLoop(1);  
    }; break;

    case STATE_CLOSED: {
      blinkTimesForLoop(2);  
    }; break;

    case STATE_EMERG_CLOSED: {
      blinkTimesForLoop(10); 
      beepTimesForLoop(3); 
    }; break;
    
  }
}

void handleButtonPressed() {
  highBeep();
  
  switch(current_state) {
    case STATE_JUST_STARTED: {
      changeState(STATE_OPENED);
    }; break;

    case STATE_OPENED: {
      changeState(STATE_CLOSED);
    }; break;

    case STATE_CLOSED: {
      changeState(STATE_OPENED);
    }; break;

    case STATE_EMERG_CLOSED: {
      changeState(STATE_OPENED);
    }; break;
    
  }
}

void handleLeakageAlarm() {
  if (current_state == STATE_CLOSED || current_state == STATE_EMERG_CLOSED)
    return;

  changeState(STATE_EMERG_CLOSED); 
}
