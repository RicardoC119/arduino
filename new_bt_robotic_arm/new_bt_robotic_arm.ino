/*
  Controle de Servomotores por Bluetooth

  criado 11 Nov 2022
  por Ricardo C. Aguiar, aluno de Engenharia de Sistemas Ciber-Fisicos.

  Este codigo foi criado para a Pontifícia Universidade Católica de São Paulo [PUC-SP].

  Este codigo pode ser utilizado para consulta, examinação, modificação e redistribuição.
  
 *****************************************************
 *                     ATENÇÃO!!
 *****************************************************
 * Se não souber o que esta fazendo não se recomenda
 * modificar nada abaixo!
 * 
 * O arquivo "definitions.h" foi criado para facilitar
 * a alteração de variaveis pre-definidas.
 */
 
#include <Servo.h> // Esta biblioteca é responsavel pelo contole dos servomotores
#include <SoftwareSerial.h> // O SoftwareSerial permite trocar as posições de RX e TX
#include "definitions.h" // Esta é uma biblioteca local onde pode-se alterar algumas configurações

SoftwareSerial BT(bt_rx,bt_tx); // Troca o RX e TX para valores que não atrapalhem no carregamento do codigo

int i = 0;      // variavel para armazenar o incremento e decremento dos ângulos
char recebido;  // variavel para armazenar as entradas seriais
String comando; // variavel para armazenar um comando

// Variavel para armazenar o movimento dos servos
// [ 0 = parado || 1 = direita || 2 = esquerda ]
int state[6] = {
  0, 0, 0, 0, 0, 0
};

// Define os pinos dos servomotores
int MOT[6] = {
  MOT1, MOT2, MOT3, MOT4, MOT5, MOT6
};

Servo m[6];

int servo_key[12] = {
  
}

int angulo[6] = {
  ini_mot1, ini_mot2, ini_mot3, ini_mot4, ini_mot5, ini_mot6
};

int servo_max[] = {
  max_mot1, max_mot2, max_mot3, max_mot4, max_mot5, max_mot6
};

int servo_min[] = {
  min_mot1, min_mot2, min_mot3, min_mot4, min_mot5, min_mot6
};

void setup() { 
    Serial.begin(9600);
    Serial.println("Serial Started...");
    BT.begin(9600); // Inicia o serial com uma velocidade de 9600
    
    // Ativa e posiciona os servomotores na posição inicial
    for (int f = 0; f < 6; f++){
      m[f].attach(MOT[f]);
      m[f].write(angulo[f]);
    }
}

void loop(){
  delay(time_delay);
  
  for (int t = 0; t < 6; t++){
      if (state[t] == 1){
        if (angulo[t] >= servo_max[t]){
          angulo[t] = servo_max[t];
          state[t] = 0;
        }
        else {
          angulo[t] += 1;
        }
        m[t].write(angulo[t]);
        Serial.print("Aumentando: ");
        Serial.println(angulo[t]);
      }
      else if (state[t] == 2){
        if (angulo[t] <= servo_min[t]){
          angulo[t] = servo_min[t];
          state[t] = 0;
        }
        else {
         angulo[t] -= 1; 
        }
        m[t].write(angulo[t]);
        Serial.print("Diminuindo: ");
        Serial.println(angulo[t]);
      }
    }
    
  if (BT.available()){
    recebido = BT.read();
    comando += recebido;
    
    if (recebido == ';'){
        if (comando == "r_arrow;"){
          if (state[3] == 0){
            state[3] = 1;
            Serial.println("iniciar movimento");
          }
          else if (state[3] == 1){
            state[3] = 0;
            Serial.println("parar movimento");
          }
        }
        else if (comando == "l_arrow;"){
          if (state[3] == 0){
            state[3] = 2;
            Serial.println("iniciar movimento");
          }
          else if (state[3] == 2){
            state[3] = 0;
            Serial.println("parar movimento");
          }
        }
        comando = "";
      }
    }
  }
