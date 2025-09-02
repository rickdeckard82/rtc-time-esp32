#include <Arduino.h>
#include <DS1302.h>  // Biblioteca compatível com struct Time

// 🧩 Definições dos pinos conectados ao módulo RTC
#define DS1302_CLK  15
#define DS1302_DAT  16
#define DS1302_RST  17

// 🕒 Instância do RTC
DS1302 rtc(DS1302_RST, DS1302_DAT, DS1302_CLK);

// ✅ Mude para true só quando quiser ajustar manualmente
const bool ajustarHora = false;

void setup() {
  Serial.begin(115200);
  delay(500); // Estabilização

  // ✅ Ajusta hora apenas se a flag estiver ativada
  if (ajustarHora) {
    Serial.println("🔧 Ajustando hora manualmente...");

    // (ano, mês, dia, hora, minuto, segundo, dia da semana)
    Time t(20245, 6, 11, 21, 52, 0, Time::Day::kSunday);

    rtc.writeProtect(false);  // Desbloqueia escrita
    rtc.halt(false);          // Garante que o RTC conte
    rtc.time(t);              // Atualiza o horário
  }

  // ✅ Mostra a hora atual no monitor
  Time now = rtc.time();
  Serial.printf("🕒 Inicial: %04d-%02d-%02d %02d:%02d:%02d\n",
                now.yr, now.mon, now.date,
                now.hr, now.min, now.sec);
}

void loop() {
  Time now = rtc.time();

  Serial.printf("🕒 %04d-%02d-%02d %02d:%02d:%02d\n",
                now.yr, now.mon, now.date,
                now.hr, now.min, now.sec);

  delay(1000);
}
