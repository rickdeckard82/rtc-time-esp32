#include <Arduino.h>
#include <Ds1302.h>

#define PIN_ENA 27
#define PIN_CLK 25
#define PIN_DAT 26

Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);

const static char* WeekDays[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"
};

void setup() {
  Serial.begin(115200);
  rtc.init();

  // ⚠️ Força a atualização SEM verificar se já está rodando
  Ds1302::DateTime dt = {
    .year = 25,
    .month = Ds1302::MONTH_JUN,
    .day = 9,
    .hour = 16,
    .minute = 30,
    .second = 0,
    .dow = Ds1302::DOW_SUN
  };

  rtc.setDateTime(&dt);  // ✅ Define o relógio sempre
  Serial.println("RTC atualizado.");
}


void loop() {
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  static uint8_t last_second = 0;
  if (last_second != now.second) {
    last_second = now.second;

    Serial.printf("20%02d-%02d-%02d %s %02d:%02d:%02d\n",
                  now.year, now.month, now.day,
                  WeekDays[now.dow - 1],
                  now.hour, now.minute, now.second);
  }

  delay(100);
}
