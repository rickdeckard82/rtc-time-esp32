#include <Arduino.h>
#include <DS1302.h>  // Biblioteca que define a struct Time diretamente

#define DS1302_CLK  25
#define DS1302_DAT  26
#define DS1302_RST  27

DS1302 rtc(DS1302_RST, DS1302_DAT, DS1302_CLK);

// ⚠️ Mude para `true` apenas quando quiser reconfigurar o RTC
const bool ajustarHora = false;

void setup() {
  Serial.begin(115200);

  // ✅ Define a hora (ano, mês, dia, hora, minuto, segundo, dia da semana)
  Time t(2025, 6, 11, 21, 34, 0, Time::Day::kMonday);

  rtc.time(t);
  Serial.println("⏱ RTC ajustado!");
}

void loop() {
  Time now = rtc.time();

  Serial.printf("🕒 %04d-%02d-%02d %02d:%02d:%02d\n",
                now.yr, now.mon, now.date,
                now.hr, now.min, now.sec);

  delay(1000);
}
