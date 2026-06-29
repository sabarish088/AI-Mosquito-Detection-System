#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <arduinoFFT.h>
#include <driver/i2s.h>

#define SERVO_PIN 18
#define LED_PIN 25
#define LCD_ADDRESS 0x27
#define I2S_WS_PIN 15
#define I2S_SCK_PIN 14
#define I2S_SD_PIN 32
#define I2S_PORT I2S_NUM_0
#define I2S_SAMPLE_RATE 16000
#define I2S_SAMPLE_BITS I2S_BITS_PER_SAMPLE_32BIT
#define I2S_CHANNELS 1
#define I2S_BUFFER_SIZE 256

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
Servo sprayServo;

void configureI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_SAMPLE_BITS,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = I2S_BUFFER_SIZE,
    .use_apll = false
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK_PIN,
    .ws_io_num = I2S_WS_PIN,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD_PIN,
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_set_clk(I2S_PORT, I2S_SAMPLE_RATE, I2S_SAMPLE_BITS, I2S_CHANNEL_MONO);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mosquito Detect");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  sprayServo.attach(SERVO_PIN);
  sprayServo.write(0);

  configureI2S();

  Serial.println("System initialized");
}

void loop() {
  static uint32_t lastUpdate = 0;

  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status: Ready");
    lcd.setCursor(0, 1);
    lcd.print("Peak: -- Hz");

    Serial.println("Monitoring acoustic input...");
  }
}
