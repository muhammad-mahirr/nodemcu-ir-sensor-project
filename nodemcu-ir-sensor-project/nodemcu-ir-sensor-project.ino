// Pin definitions
#define IR_SENSOR_PIN D5     // IR sensor digital OUT pin
#define GREEN_LED_PIN D6     // Green LED (door closed)
#define RED_LED_PIN D7       // Red LED (door open)
#define BUZZER_PIN D8        // Buzzer (door open)

void setup() {
  Serial.begin(115200);

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Assume door is closed initially
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  int sensorState = digitalRead(IR_SENSOR_PIN);

  if (sensorState == LOW) {
    // Door closed
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("✅ Door Closed");
  } else {
    // Door opened
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("🚨 Door Opened - Alert!");
  }

  delay(200);
}
