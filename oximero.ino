#include <Wire.h>                    //inclusão de biblioteca I2C
#include "MAX30100_PulseOximeter.h"  //inclusão da biblioteca do MAX30100

#define REPORTING_PERIOD_MS 1000  //define o intervalo em 1000ms ou 1s entre as medições


PulseOximeter pox;  //cria o objeto PulseOximeter

uint32_t tsLastReport = 0;  //variável criada para armazenar o tempo da medição

// função para quando o pulso é detectado
void onBeatDetected() {
  Serial.println("Beat!");  // Printa a mensagem "Beat!"
}

void setup()  //Laço de configuração
{
  Serial.begin(115200);  // define Baudrate para 115200

  Serial.print("Inicialização do sensor...");  //Printa a mensagem "Inicialização do sensor"

  // Inicializa ao sensor de pulso
  if (!pox.begin()) {          //possibilita a comunicação com o sensor
    Serial.println("Falhou");  //Printa a mensagem "Falhou"
    for (;;)
      ;
  } else {                      //do contrário
    Serial.println("Sucesso");  //Printa a mensagem "Sucesso"
  }


  pox.setIRLedCurrent(MAX30100_LED_CURR_50MA);


  // retorno para detecção do "beat"
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()  //laço de repetição
{


  // Os dados biométricos são coletados pelo sensor
  pox.update();

  //
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {  //os dados serão imprimidos a cada 1000us ou 1s
                                                        // Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());                   //prime o dado de frequência cardíaca
    Serial.print(" ");
    // Serial.print("bpm / SpO2:");
    Serial.println(pox.getSpO2());  //prime o dado de oxigenação
    Serial.print(" ");
    //  Serial.println("%");

    tsLastReport = millis();
  }













}