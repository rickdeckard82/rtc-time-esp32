#include <DS1302.h>

// Pinos: RST (CE), DAT (I/O), CLK
DS1302 rtc(27, 26, 25);

void setup() {
  Serial.begin(115200);

  rtc.halt(false);
  rtc.writeProtect(false);

  // ✅ Ajuste de data/hora (use apenas uma vez)
  Time t;
  t.sec = 0;
  t.min = 17;
  t.hr  = 14;
  t.date = 25;
  t.mon  = 5;
  t.yr   = 2025;

  rtc.time(t);  // ✅ Ajusta o RTC com a hora definida

  Serial.println("Hora ajustada com sucesso!");
}

void loop() {
  Time now = rtc.time();  // ✅ Lê a hora atual

  Serial.print(now.date); Serial.print('/');
  Serial.print(now.mon); Serial.print('/');
  Serial.print(now.yr); Serial.print(" ");
  Serial.print(now.hr); Serial.print(':');
  Serial.print(now.min); Serial.print(':');
  Serial.println(now.sec);

  delay(1000);
}
