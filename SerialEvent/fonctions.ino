void serial_blink(int times, int delay_) {
  for (int i = 0; i < times; i++) {
    digitalWrite(13, HIGH);
    delay(delay_);
    digitalWrite(13, LOW);
    delay(delay_);
  }
}

void capture_data() {
  float value = sin(millis());
  Serial.print(value);
  Serial.print("/");
  Serial.println(millis());
}
