/*
  Controle de um Motor de Passo com
  um Sensor de Luminosidade e servo

  criado 19 Nov 2022
  por Ricardo C. Aguiar,
  aluno de Engenharia de Sistemas Ciber-Fisicos.

  Este codigo foi criado para a 
  Pontifícia Universidade Católica de São Paulo [PUC-SP].

  Este codigo pode ser utilizado para consulta,
  examinação, modificação e redistribuição.

  https://github.com/RicardoC119/arduino/tree/main/ldr_stepper_servo
  */

#include <Stepper.h>
#include <Servo.h>

Servo mot1;

int pos = 0;

// O numero de passos por revolução varia para cada motor
// Este numero pode ser calculado utilizando a formula a seguir
// passos = 360/Angulo de cada passo
// OBS: O angulo de cada passo pode ser encontrado no Datasheet
//      do motor utilizado
#define passos 64

bool debug = true;

int ldr = 7; // Pino do sensor de luminosidade
int pot = A0; // Pino do potenciometro

int vel_min = 200;   // Velocidade minima em RPM
int vel_max = 350; // Velocidade maxima em RPM

int velocidade = 0;               // Variavel para armazenar a velocidade em RPM
int val = 0;               // Variavel para armazenar a posição do potenciometro
int count = 0;             // Variavel para armazenar a quantidade de objetos
int perc = 0;
int lastState = "parado";  // Variavel para detectar o ultimo estado

Stepper stepper(passos, 9, 11, 10, 12); // 

void setup() {
  Serial.begin(9600); // Inicia a porta serial com velocidade de 9600
  pinMode(ldr, INPUT); // Define o ldr como entrada
  mot1.attach(3); // Define o pino do servo
  mot1.write(0); // Define a posição inicial
}

void loop() {
  delay(50); // Espera em milisegundos
  val = analogRead(pot); // Verificação da posição do potenciometro

  // Muda os valores do potenciometro para o maximo e minimo
  perc = map(val, 0, 1023, -8, 114);
  velocidade = map(val, 0, 1023, vel_min-7, vel_max);
  
  if (digitalRead(ldr) == LOW){ // Se o ldr estiver normal
    stepper.setSpeed(velocidade); // Define a velocidade em RPM
    stepper.step(-passos); // Anda uma revolução
    lastState = "andando";
    
    if (debug == true){
      Serial.print("Andando a ");
      Serial.print(velocidade);
      Serial.print(" RPM | Pot: ");
      Serial.print(perc);
      Serial.println("%");
    }
  }
  else { // Se o ldr estiver obstruido
    
    // A verificação de ultimo estado é muito importante
    // já que como o codigo esta em um loop toda vez que
    // o loop recomeçar ele contará +1 e não estaria correto
    if (lastState == "andando"){
      count++; // Adiciona um objeto
    }
    lastState = "parado";

    // O codigo abaixo simula um movimento
    // quando um objeto é detectado
    for (pos = 0; pos <= 180; pos += 1) { 
      mot1.write(pos);
      Serial.print("Ang Motor: ");
      Serial.println(pos);      
      delay(15);                      
    }
    for (pos = 180; pos >= 0; pos -= 1) {
      mot1.write(pos);
      Serial.print("Ang Motor: ");
      Serial.println(pos); 
      delay(15);
    }

    if (debug == true){
      Serial.print("Objeto detectado! | Já passaram ");
      Serial.print(count);
      Serial.println(" objetos.");
      delay(100);
    }
  }
}
