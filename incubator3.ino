#include <liquidcrystal.h>
#include <servo.h>
#include <dht.h>
#define DHT11                                                    \
  A0 const int ok = A1;                                          \
  const int UP = A2;                                             \
  const int DOWN = A3;                                           \
  const int bulb = A4;                                           \
  const int vap = A5;                                            \
  const int rs = 12;                                             \
  const int en = 11;                                             \
  const int d4 = 5;                                              \
  const int d5 = 4;                                              \
  const int d6 = 3;                                              \
  const int d7 = 2;                                              \
  int ack = 0;                                                   \
  int pos = 0;                                                   \
  int sec = 0;                                                   \
  int Min = 0;                                                   \
  int hrs = 0;                                                   \
  int T_threshold = 25;                                          \
  int H_threshold = 35;                                          \
  int SET = 0;                                                   \
  int Direction = 0;                                             \
  boolean T_condition = true;                                    \
  boolean H_condition = true;                                    \
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                     \
  Servo motor;                                                   \
  dht DHT;                                                       \
  void setup()                                                   \
  {                                                              \
    pinMode(ok, INPUT);                                          \
    pinMode(UP, INPUT);                                          \
    pinMode(DOWN, INPUT);                                        \
    pinMode(bulb, OUTPUT);                                       \
    pinMode(vap, OUTPUT);                                        \
    digitalWrite(bulb, LOW);                                     \
    digitalWrite(vap, LOW);                                      \
    digitalWrite(ok, HIGH);                                      \
    digitalWrite(UP, HIGH);                                      \
    digitalWrite(DOWN, HIGH);                                    \
    motor.attach(7);                                             \
    motor.write(pos);                                            \
    lcd.begin(16, 2);                                            \
    Serial.begin(9600);                                          \
    lcd.setCursor(5, 0);                                         \
    lcd.print("Digital");                                        \
    lcd.setCursor(4, 1);                                         \
    lcd.print("Incubator");                                      \
    delay(1500);                                                 \
  }                                                              \
  void loop()                                                    \
  {                                                              \
    if (SET == 0)                                                \
    {                                                            \
      lcd.clear();                                               \
      lcd.setCursor(0, 0);                                       \
      lcd.print("Set Temperature:");                             \
      lcd.setCursor(0, 1);                                       \
      lcd.print(T_threshold);                                    \
      lcd.print(" *C");                                          \
      while (T_condition)                                        \
      {                                                          \
        if (digitalRead(UP) == LOW)                              \
        {                                                        \
          T_threshold = T_threshold + 1;                         \
          lcd.setCursor(0, 1);                                   \
          lcd.print(T_threshold);                                \
          lcd.print(" *C");                                      \
          delay(200);                                            \
        }                                                        \
        if (digitalRead(DOWN) == LOW)                            \
        {                                                        \
          T_threshold = T_threshold - 1;                         \
          lcd.setCursor(0, 1);                                   \
          lcd.print(T_threshold);                                \
          lcd.print(" *C");                                      \
          delay(200);                                            \
        }                                                        \
        if (digitalRead(ok) == LOW)                              \
        {                                                        \
          delay(200);                                            \
          T_condition = false;                                   \
        }                                                        \
      }                                                          \
      lcd.clear();                                               \
      lcd.setCursor(0, 0);                                       \
      lcd.print("Set Humidity:");                                \
      lcd.setCursor(0, 1);                                       \
      lcd.print(H_threshold);                                    \
      lcd.print("%");                                            \
      delay(100);                                                \
      while (H_condition)                                        \
      {                                                          \
        if (digitalRead(UP) == LOW)                              \
        {                                                        \
          H_threshold = H_threshold + 1;                         \
          lcd.setCursor(0, 1);                                   \
          lcd.print(H_threshold);                                \
          lcd.print("%");                                        \
          delay(100);                                            \
        }                                                        \
        if (digitalRead(DOWN) == LOW)                            \
        {                                                        \
          H_threshold = H_threshold - 1;                         \
          lcd.setCursor(0, 1);                                   \
          lcd.print(H_threshold);                                \
          lcd.print("%");                                        \
          delay(200);                                            \
        }                                                        \
        if (digitalRead(ok) == LOW)                              \
        {                                                        \
          delay(100);                                            \
          H_condition = false;                                   \
        }                                                        \
      }                                                          \
      SET = 1;                                                   \
    }                                                            \
    ack = 0;                                                     \
    int chk = DHT.read11(DHT11);                                 \
    switch (chk)                                                 \
    {                                                            \
    case DHTLIB_ERROR_CONNECT:                                   \
      ack = 1;                                                   \
      break;                                                     \
    }                                                            \
    if (ack == 0)                                                \
    {                                                            \
      lcd.clear();                                               \
      lcd.setCursor(0, 0);                                       \
      lcd.print("Temp:");                                        \
      lcd.print(DHT.temperature);                                \
      lcd.setCursor(0, 1);                                       \
      lcd.print("Humidity:");                                    \
      lcd.print(DHT.humidity);                                   \
      if (DHT.temperature &gt; = T_threshold)                    \
      {                                                          \
        delay(3000);                                             \
        if (DHT.temperature &gt; = T_threshold)                  \
        {                                                        \
          digitalWrite(bulb, LOW);                               \
        }                                                        \
      }                                                          \
      if (DHT.humidity &gt; = H_threshold)                       \
      {                                                          \
        delay(3000);                                             \
        if (DHT.humidity &gt; = H_threshold)                     \
        {                                                        \
          digitalWrite(vap, LOW);                                \
        }                                                        \
      }                                                          \
      if (DHT.temperature & lt; T_threshold)                     \
      {                                                          \
        delay(3000);                                             \
        if (DHT.temperature & lt; T_threshold)                   \
        {                                                        \
          digitalWrite(bulb, HIGH);                              \
        }                                                        \
      }                                                          \
      if (DHT.humidity & lt; H_threshold)                        \
      {                                                          \
        delay(3000);                                             \
        if (DHT.humidity & lt; H_threshold)                      \
        {                                                        \
          digitalWrite(vap, HIGH);                               \
        }                                                        \
      }                                                          \
      sec = sec + 1;                                             \
      if (sec == 60)                                             \
      {                                                          \
        sec = 0;                                                 \
        Min = Min + 1;                                           \
      }                                                          \
      if (Min == 60)                                             \
      {                                                          \
        Min = 0;                                                 \
        hrs = hrs + 1;                                           \
      }                                                          \
      if (hrs == 8 & amp; &amp; Min == 0 & amp; &amp; sec == 0)  \
      {                                                          \
        for (pos = 0; pos &lt; = 180; pos += 1)                  \
        {                                                        \
          motor.write(pos);                                      \
          delay(25);                                             \
        }                                                        \
      }                                                          \
      if (hrs == 16 & amp; &amp; Min == 0 & amp; &amp; sec == 0) \
      {                                                          \
        hrs = 0;                                                 \
        for (pos = 180; pos &gt; = 0; pos -= 1)                  \
        {                                                        \
          motor.write(pos);                                      \
          delay(25);                                             \
        }                                                        \
      }                                                          \
    }                                                            \
    if (ack == 1)                                                \
    {                                                            \
      lcd.clear();                                               \
      lcd.setCursor(0, 0);                                       \
      lcd.print("No Sensor data.");                              \
      lcd.setCursor(0, 1);                                       \
      lcd.print("System Halted.");                               \
      digitalWrite(bulb, LOW);                                   \
      digitalWrite(vap, LOW);                                    \
    }                                                            \
    delay(1000);                                                 \
  }

//  How to operate the Circuit:· With completed hardware and apparatus setup, power the circuit ON.READ MORE&nbsp;
//  Temperature Controller Circuit for Reptile Racks· The display shows “set temperature” press up or down button to
//  get the desire temperature and press “set button”.· Now the display shows “set Humidity” press up or down buttons
//  to get desire humidity and press “set button”.·
//  It begins the functioning of the incubator.&nbsp;Please refer internet or get advice from a professional for
//  temperature and humidity level for the eggs.If you have any specific question regarding this Arduino automatic
//  incubator temperature and humidity control circuit, feel free to express in the comment section.