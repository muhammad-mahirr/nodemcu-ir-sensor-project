#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
#define IR_SENSOR_PIN D5     // IR sensor digital OUT pin
#define GREEN_LED_PIN D6     // Green LED (door closed)
#define RED_LED_PIN D7       // Red LED (door open)
#define BUZZER_PIN D8        // Buzzer (door open)

void setup() {
  Serial.begin(115200);

  // Initialize I2C and OLED display
  Wire.begin(D2, D1);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("❌ SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("System Ready");
  display.display();
  delay(1000);

  // Set pin modes
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial state
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  int sensorState = digitalRead(IR_SENSOR_PIN);

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);

  if (sensorState == LOW) {
    // Door closed
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("✅ Door Closed");

    // Two-line message: "Gate" and "Closed"
    String line1 = "Door";
    String line2 = "Closed";

    int16_t x1, y1;
    uint16_t w1, h1, w2, h2;

    display.getTextBounds(line1, 0, 0, &x1, &y1, &w1, &h1);
    display.getTextBounds(line2, 0, 0, &x1, &y1, &w2, &h2);

    int y = (SCREEN_HEIGHT - (h1 + h2)) / 2;

    display.setCursor((SCREEN_WIDTH - w1) / 2, y);
    display.println(line1);
    display.setCursor((SCREEN_WIDTH - w2) / 2, y + h1 + 4);
    display.println(line2);
    display.display();

  } else {
    // Door opened
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("🚨 Someone Enters");

    // Two-line message: "Someone" and "Enters!"
    String line1 = "Someone";
    String line2 = "Enters!";

    int16_t x1, y1;
    uint16_t w1, h1, w2, h2;

    display.getTextBounds(line1, 0, 0, &x1, &y1, &w1, &h1);
    display.getTextBounds(line2, 0, 0, &x1, &y1, &w2, &h2);

    int y = (SCREEN_HEIGHT - (h1 + h2)) / 2;

    display.setCursor((SCREEN_WIDTH - w1) / 2, y);
    display.println(line1);
    display.setCursor((SCREEN_WIDTH - w2) / 2, y + h1 + 4);
    display.println(line2);
    display.display();
  }

  delay(200);
}


