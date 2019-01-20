/*
 * Софт для блока защиты от протечек
 * блок следит за датчиком влажности и закрывает кран (краны) если обнаружена протечка
 * кроме того, он использует светодиод для отображения состояния 
 * и может открыть/закрыть воду по нажатию кнопки
 * 
 * -----------------------------
 * в состоянии после_старта
 *    моргает редко один раз
 * в состоянии нормально_открыт
 *    моргает редко два раза
 * в состоянии нормально_закрыт
 *    моргает редко три раза
 * в состоянии аварийно_закрыт
 *    моргает часто
 *    пищит раз в 20 секунд
 *    
 *    
 * при нажатии кнопки
 ; в состоянии после_старта
 *    открываем кран
 *    переводим в состояние нормально_открыт
 *    
 * в состоянии нормально_открыт
 *    закрываем кран
 *    переводим в состояние нормально_закрыт
 *    
 * в состоянии нормально_закрыт
 *    открываем кран
 *    переводин в состояние нормально_закрыт
 *    
 * в состоянии аварийно_закрыт
 *    открываем кран
 *    переводин в состояние нормально_закрыт
 *    
 *    
 * при срабатывании датчика протечки
 * 
 *   в состоянии после_старта, нормально_открыт
 *    пищим   
 *    закрываем кран
 *    переводим в состояние аварийно_закрыт
 *    
 *    в состоянии нормально_закрыт
 *      диман предлагает ничего не делать, TODO
 *      
 *    в состоянии нормально_закрыт
 *      ничего не делать
 */

//#define LOGGING // когда определена, печатаем отладку в serial

 
#define BEEPER_PIN        A0   // к чему подключена гуделка
#define BUTTON_PIN        5    // к чему подключена кнопка
#define LED_PIN           4    // светодиод
#define RELAY_ON_PIN      11   // реле для питания
#define RELAY_DIR_PIN     12   // реле для направления (откр/закр)
#define WATER_SENSOR_PIN  A2   // датчик влажности

#define WATER_TRESHOLD 300     // порог влажности который считаем опасным

#define VALVE_OPEN  LOW
#define VALVE_CLOSE HIGH

#define STATE_JUST_STARTED 1 // после_старта
#define STATE_OPENED 2 // нормально_открыт
#define STATE_CLOSED 3 // нормально_закрыт
#define STATE_EMERG_CLOSED 4 // аварийно_закрыт

////
#define VALVE_TIME  4500 // сколько времени в мсек давать напряжение на вентиль чтобы его открыть или закрыть (с запасом! Cwx 15q отрабатывает примерно за 1 сек)
#define INTER_RELAY_GAP 100

#define LOOP_DELAY 50 // как долго спать в конце 
#define REPEATED_BLINK_DELAY 5000 // как часто в мсек моргать статусным мыргом
#define REPEATED_BEEP_DELAY 60000 // как часто в мсек моргать статусным мыргом


int current_state = STATE_JUST_STARTED;


byte state = 0;

void setup()
{
#ifdef LOGGING
  Serial.begin(115200);
#endif

  highBeep();

  pinMode(BEEPER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  pinMode(RELAY_ON_PIN, OUTPUT);
  pinMode(RELAY_DIR_PIN, OUTPUT);
  digitalWrite(RELAY_ON_PIN, LOW);
  digitalWrite(RELAY_DIR_PIN, LOW);

  SerialPrintf("Initialized; state %d\n", current_state);
}

void switchRelay()
{
  if (++state%2)
    valveOpen();
  else
    valveClose();
}


void loop()
{
  displayState();

  int btnPressed = !digitalRead(BUTTON_PIN);
  if (btnPressed) {
    handleButtonPressed();
  }

  int valueMoisture = analogRead(WATER_SENSOR_PIN);
  if (valueMoisture > WATER_TRESHOLD) {
      handleLeakageAlarm();  
  }
  
  delay(LOOP_DELAY);
}
