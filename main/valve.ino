
void valveOpen()
{
  SerialPrintf("Valve open\n");

  digitalWrite(LED_PIN, HIGH);
  
  digitalWrite(RELAY_ON_PIN, LOW);
  digitalWrite(RELAY_DIR_PIN, VALVE_OPEN);
  delay(INTER_RELAY_GAP);
  digitalWrite(RELAY_ON_PIN, HIGH); // пошло электричество
  delay(VALVE_TIME);
  digitalWrite(RELAY_ON_PIN, LOW);
  delay(INTER_RELAY_GAP);
  digitalWrite(RELAY_DIR_PIN,LOW);

  digitalWrite(LED_PIN, LOW);
}

void valveClose()
{
  SerialPrintf("Valve close\n");

  digitalWrite(LED_PIN, HIGH);

  digitalWrite(RELAY_ON_PIN, LOW);
  digitalWrite(RELAY_DIR_PIN, VALVE_CLOSE);
  delay(INTER_RELAY_GAP);
  digitalWrite(RELAY_ON_PIN, HIGH);
  delay(VALVE_TIME);
  digitalWrite(RELAY_ON_PIN, LOW);
  delay(INTER_RELAY_GAP);
  digitalWrite(RELAY_DIR_PIN,LOW);

  digitalWrite(LED_PIN, LOW);

}
