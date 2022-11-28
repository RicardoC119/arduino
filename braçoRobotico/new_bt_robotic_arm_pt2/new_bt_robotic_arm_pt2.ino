      /*
  Controle de uma Esteira
  Para Funcionar Com O Braço
  Robotico

  criado 20 Nov 2022
  por Ricardo C. Aguiar, aluno de Engenharia de Sistemas Ciber-Fisicos.

  Este codigo foi criado para a Pontifícia Universidade Católica de São Paulo [PUC-SP].

  Este codigo pode ser utilizado para consulta, examinação, modificação e redistribuição.

  https://github.com/RicardoC119/arduino/tree/main/new_bt_robotic_arm_pt2
  
  *****************************************************
  *                     ATENÇÃO!!
  *****************************************************
  * Se não souber o que esta fazendo não se recomenda
  * modificar nada abaixo!
  */

#include <Stepper.h> // Biblioteca do motor de passo
#include <SoftwareSerial.h> // O SoftwareSerial permite trocar as posições de RX e TX

SoftwareSerial EST(2,3); // rx e tx

char recebido;  // variavel para armazenar as entradas seriais
String comando; // variavel para armazenar um comando

// O numero de passos por revolução varia para cada motor
// Este numero pode ser calculado utilizando a formula a seguir
// passos = 360/Angulo de cada passo
// OBS: O angulo de cada passo pode ser encontrado no Datasheet
//      do motor utilizado
#define passos 64

bool debug = true;

int ldr = 7; // Pino do sensor de luminosidade

int vel_min = 200;   // Velocidade minima em RPM
int vel_max = 350; // Velocidade maxima em RPM

int velocidade = 0;        // Variavel para armazenar a velocidade em RPM
int val = 0;               // Variavel para armazenar a posição do potenciometro
int count = 0;             // Variavel para armazenar a quantidade de objetos
int lastState = "parado";  // Variavel para detectar o ultimo estado

Stepper stepper(passos, 9, 11, 10, 12); // 

int pir = 4;
bool state = false;

bool emergency = false;

void setup() {
  Serial.begin(9600);
  EST.begin(9600); // Inicia a porta serial com velocidade de 9600
  pinMode(ldr, INPUT); // Define o ldr como entrada
  pinMode(pir, INPUT);
  stepper.setSpeed(350);
}

void loop() {
  delay(50); // Espera em milisegundos

  if (digitalRead(pir) == HIGH){
    if (state == false){
      EST.println(";stp;");
      Serial.println(";stp;");
      emergency == true;
      state = true;
    }
  }
  if (EST.available()){
    recebido = EST.read();
    comando += recebido;

    if (recebido == ';'){
      if (comando == ";rst;"){
        if (state == true){
          emergency == false;
          state = false;
        }
      }
    }
  }
  
  if (digitalRead(ldr) == LOW and emergency == false){ // Se o ldr estiver normal
    stepper.step(passos); // Anda uma revolução
    lastState = "andando";
  }
  else { // Se o ldr estiver obstruido
         // A verificação de ultimo estado é muito importante
         // já que como o codigo esta em um loop toda vez que
         // o loop recomeçar ele contará +1 e não estaria correto
    if (lastState == "andando"){
      EST.println(";cnt;");
    }
    lastState = "parado";
    

    if (debug == true){
      Serial.print("Objeto detectado! | Já passaram ");
      Serial.print(count);
      Serial.println(" objetos.");
      delay(100);
    }
  }
}
