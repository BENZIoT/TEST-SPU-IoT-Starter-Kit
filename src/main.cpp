#include <SPI.h>
#include <SHT31.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../Adafruit_BusIO-master/Adafruit_I2CDevice.h"
#include "../screen/logo.h"
#include "../screen/cpe.h"
#include "../screen/RGB.h"
#include "../screen/relay.h"
#include "../screen/button.h"
#include "../screen/adc.h"
#include "../screen/temp.h"
#include "../screen/buzzer.h"
#include <WiFi.h>

#define SHT31_ADDRESS 0x44
SHT31 sht;

#define R1 32
#define R2 14
#define RED 25
#define GREEN 26
#define BLUE 27

#define Button1 0
#define Button2 4

#define ADC 36

const int TONE_OUTPUT_PIN = 33;
bool test_buzzer_loop = false;

const int TONE_PWM_CHANNEL = 0;

void testLED();
void testSHT31();
void testBuzzer();
void testRelay();
void scanWiFi();
void testButton();
void testADC();

void setup()
{
  Serial.begin(9600);
  sht.begin(SHT31_ADDRESS);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  pinMode(ADC, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, HIGH);

  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println("SSD1306 allocation failed");
  }
  else
  {
    Serial.println("OLED Start Work !!!");
  }
  // display.clearDisplay();
  // display.setTextColor(WHITE, BLACK);
  // display.drawBitmap(0, 0, SPU_LOGO, 128, 64, WHITE);
  // display.display();
  // delay(2000);
  // scanWiFi();
  // delay(1000);
  // testLED();
  // testRelay();
  // testButton();
  // delay(500);
  // digitalWrite(GREEN, LOW);
  // delay(50);
  // digitalWrite(GREEN, HIGH);
  // testADC();
  // digitalWrite(GREEN, LOW);
  // delay(50);
  // digitalWrite(GREEN, HIGH);
  // delay(500);
  // testBuzzer();

}

void loop()
{
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  display.drawBitmap(0, 0, SPU_LOGO, 128, 64, WHITE);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  display.drawBitmap(0, 0, CPE, 128, 64, WHITE);
  display.display();
  delay(1000);
  scanWiFi();
  delay(500);
  testLED();
  testRelay();
  testButton();
  testADC();
  delay(500);
  testBuzzer();
  testSHT31();
  delay(5000);
}

void testLED()
{
  display.clearDisplay();
  display.drawBitmap(0, 0, RGB_RED, 128, 64, WHITE);
  display.display();
  digitalWrite(RED, LOW);
  Serial.println("LED_RED : ON");
  delay(300);
  digitalWrite(RED, HIGH);
  Serial.println("LED_RED : OFF");
  delay(300);
  display.clearDisplay();
  display.drawBitmap(0, 0, RGB_GREEN, 128, 64, WHITE);
  display.display();
  digitalWrite(GREEN, LOW);
  Serial.println("LED_GREEN : ON");
  delay(300);
  digitalWrite(GREEN, HIGH);
  Serial.println("LED_GREEN : OFF");
  delay(300);
  display.clearDisplay();
  display.drawBitmap(0, 0, RGB_BLUE, 128, 64, WHITE);
  display.display();
  digitalWrite(BLUE, LOW);
  Serial.println("LED_BULE : ON");
  delay(300);
  digitalWrite(BLUE, HIGH);
  Serial.println("LED_BLUE : OFF");
  delay(300);
  display.clearDisplay();
  display.drawBitmap(0, 0, RGB_WHITE, 128, 64, WHITE);
  display.display();
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  delay(500);
  display.clearDisplay();
  display.drawBitmap(0, 0, RGB_OFF, 128, 64, WHITE);
  display.display();
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  delay(1000);
}

void testBuzzer()
{
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 4);
  Serial.println("NOTE_C");
  animateBuzzer(2);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 4);
  Serial.println("NOTE_D");
  animateBuzzer(2);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 4);
  Serial.println("NOTE_E");
  animateBuzzer(2);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  Serial.println("NOTE_F");
  animateBuzzer(2);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_G, 4);
  Serial.println("NOTE_G");
  animateBuzzer(2);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  Serial.println("NOTE_A");
  animateBuzzer(2);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  Serial.println("NOTE_B");
  animateBuzzer(2);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 5);
  Serial.println("NOTE_C");
  animateBuzzer(2);
  ledcDetachPin(33);
}

void testSHT31()
{
  sht.read(); // default = true/fast       slow = false
  Serial.println("TEMP -> " + String(sht.getTemperature(), 2));
  Serial.println("HUMI -> " + String(sht.getHumidity(), 2) + "\n");
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(25, 35);
  display.println(String(sht.getTemperature(), 2) + "       " + String(sht.getHumidity(), 2));
  display.drawBitmap(0, 0, temperature, 128, 64, WHITE);
  display.display();
}

void testRelay()
{
  display.clearDisplay();
  display.drawBitmap(0, 0, RELAY_OFF, 128, 64, WHITE);
  display.display();
  delay(500);
  digitalWrite(R1, LOW);
  display.clearDisplay();
  display.drawBitmap(0, 0, RELAY_Y1ON, 128, 64, WHITE);
  display.display();
  Serial.println("Relay1 : ON");
  delay(500);
  display.clearDisplay();
  display.drawBitmap(0, 0, RELAY_ON, 128, 64, WHITE);
  display.display();
  digitalWrite(R2, LOW);
  Serial.println("Relay2 : ON");
  delay(500);
  display.clearDisplay();
  display.drawBitmap(0, 0, RELAY_OFF, 128, 64, WHITE);
  display.display();
  digitalWrite(R1, HIGH);
  Serial.println("Relay1 : OFF");
  digitalWrite(R2, HIGH);
  Serial.println("Relay2 : OFF");
  delay(500);
}

void scanWiFi()
{
  int n = WiFi.scanNetworks();
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("Scan WiFi");
  display.display();
  delay(500);
  if (n == 0)
  {
    Serial.println("no networks found");
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("no networks found");
    display.display();
  }
  else
  {
    display.clearDisplay();
    display.setTextSize(1.5);
    display.setCursor(0, 0);
    display.println(String(n) + " networks found");
    display.display();
    display.setTextSize(0.5);

    for (int i = 0; i < n; ++i)
    {
      display.setCursor(0, i * 10 + 10);
      display.println(String(i + 1) + " " + String(WiFi.SSID(i)) + " " + String(WiFi.RSSI(i)) + " " + String((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*"));
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(50);
      display.display();
    }
  }
}

void testButton()
{
  int i = 0;
  do
  {
    if (!digitalRead(Button1))
      i |= 0x01;
    if (!digitalRead(Button2))
      i |= 0x02;

    switch (i)
    {
    case 0:
      display.clearDisplay();
      display.drawBitmap(0, 0, BUTTON_NP, 128, 64, WHITE);
      display.display();
      break;

    case 1:
      display.clearDisplay();
      display.drawBitmap(0, 0, BUTTON_AP, 128, 64, WHITE);
      display.display();
      break;

    case 2:
      display.clearDisplay();
      display.drawBitmap(0, 0, BUTTON_BP, 128, 64, WHITE);
      display.display();
      break;

    default:
      display.clearDisplay();
      display.drawBitmap(0, 0, BUTTON_PASS, 128, 64, WHITE);
      display.display();
      break;
    }
  } while (i != 3);
}

void drawPercentbar(int x, int y, int width, int height, int progress)
{
  progress = progress > 100 ? 100 : progress;
  progress = progress < 0 ? 0 : progress;
  float bar = ((float)(width - 4) / 100) * progress;
  display.drawRect(x, y, width, height, WHITE);
  display.fillRect(x + 2, y + 2, bar, height - 4, WHITE);
  if (height >= 15)
  {
    display.setCursor((width / 2) - 3, y + 5);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    if (progress >= 50)
      display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.print(progress);
    display.print("%");
  }
}

void testADC()
{
  int i = 0;
  display.clearDisplay();
  display.drawBitmap(0, 0, ADC_L, 128, 64, WHITE);
  drawPercentbar(10, 35, 110, 20, map(analogRead(ADC), 0, 4095, 0, 100));
  display.display();

  do
  {
    display.clearDisplay();
    display.drawBitmap(0, 0, ADC_L, 128, 64, WHITE);
    drawPercentbar(10, 35, 110, 20, map(analogRead(ADC), 0, 4095, 0, 100));
    display.display();
    if (analogRead(ADC) == 0)
    {
      i = 1;
    }
  } while (analogRead(ADC) >= 0 && i == 0);

  do
  {
    display.clearDisplay();
    display.drawBitmap(0, 0, ADC_R, 128, 64, WHITE);
    drawPercentbar(10, 35, 110, 20, map(analogRead(ADC), 0, 4095, 0, 100));
    display.display();
    if (analogRead(ADC) == 4095)
    {
      display.clearDisplay();
      display.drawBitmap(0, 0, ADC_R, 128, 64, WHITE);
      drawPercentbar(10, 35, 110, 20, map(analogRead(ADC), 0, 4095, 0, 100));
      display.display();
      i = 2;
      delay(500);
    }
  } while (analogRead(ADC) >= 0 && i == 1);
}
