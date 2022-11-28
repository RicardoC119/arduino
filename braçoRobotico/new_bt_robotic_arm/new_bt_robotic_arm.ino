      /*
  Controle de Servomotores por Bluetooth

  criado 11 Nov 2022
  por Ricardo C. Aguiar, aluno de Engenharia de Sistemas Ciber-Fisicos.

  Este codigo foi criado para a Pontifícia Universidade Católica de São Paulo [PUC-SP].

  Este codigo pode ser utilizado para consulta, examinação, modificação e redistribuição.

  https://github.com/RicardoC119/arduino/tree/main/new_bt_robotic_arm
  
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

// Troca o RX e TX para valores que não atrapalhem no carregamento do codigo
SoftwareSerial BT(bt_rx,bt_tx); // Pinos do Bluetooth
//SoftwareSerial ARD(ard_rx,ard_tx); // Pinos do Bluetooth

char recebido;  // variavel para armazenar as entradas seriais
String comando; // variavel para armazenar um comando

char recebido2;
String comando2;

bool emergency = false; // Variavel para o modo de emergencia
bool lastEmer = false;

// Variavel para armazenar o movimento dos servos
// [ 0 = parado || 1 = direita || 2 = esquerda ]
int state[tMot] = {
  0, 0, 0, 0, 0, 0
};

// Define os pinos dos servomotores
int MOT[tMot] = {
  MOT1, MOT2, MOT3, MOT4, MOT5, MOT6
};

Servo m[tMot]; // Array de servomotores

int vel = i_speed; // Velocidade inicial dos servos

int servo_keys_dir[tMot] = {
  m1_direita,m2_direita,
  m3_direita, m4_direita,
  m5_direita, m6_direita
};

int servo_keys_esq[tMot] = {
  m1_esquerda, m2_esquerda,
  m3_esquerda, m4_esquerda,
  m5_esquerda, m6_esquerda
};

int other_keys[otherKeysAmmount] = {
  aumentar_vel, diminuir_vel
};

int ini[tMot] = {
  ini_mot1, ini_mot2, ini_mot3, ini_mot4, ini_mot5, ini_mot6
};

int angulo[tMot] = {
  ini_mot1, ini_mot2, ini_mot3, ini_mot4, ini_mot5, ini_mot6
};

int servo_max[tMot] = {
  max_mot1, max_mot2, max_mot3, max_mot4, max_mot5, max_mot6
};

int servo_min[tMot] = {
  min_mot1, min_mot2, min_mot3, min_mot4, min_mot5, min_mot6
};

void setup() {
  Serial.begin(9600);
  if (debug == true){
    Serial.println("MODO TESTE ATIVADO!!");
  }
  BT.begin(9600); // Inicia o serial com uma velocidade de 9600
  //ARD.begin(9600);

  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);


  buzz(2,500);
  buzz(3,50);
  digitalWrite(relay, HIGH);
    
  // Ativa e posiciona os servomotores na posição inicial
  for (int f = 0; f < tMot; f++){
    m[f].attach(MOT[f]);
    m[f].write(angulo[f]);
    delay(1000);
  }
}

void loop(){
  delay(time_delay);

  if (emergency == true){
    if (lastEmer == false){
      for (int f = 0; f < tMot; f++){
        buzz(1,500);
        m[f].attach(MOT[f]);
        servoMove(f, angulo[f], ini[f], velocidade_min);
        delay(500);
        buzz(1,500);
        delay(500);
      }
      for (int f = 0; f < tMot; f++){
        m[f].detach();
      }
      digitalWrite(relay, HIGH); // desliga
      lastEmer = true;
    }
  }
  else if (emergency == false){
    if (lastEmer == true){
      buzz(2,500);
      buzz(1,1000);
      digitalWrite(relay, LOW); // liga
      for (int f = 0; f < tMot; f++){
        m[f].attach(MOT[f]);
      }
      lastEmer = false;
    }
  }

  if (state[0] == 1 or state[0] == 2){
    m[0].attach(MOT[0]);
  }
  else if(state[3] == 1 or state[3] == 2){
    m[3].attach(MOT[3]);
  }
  else{
    m[0].detach();
    m[3].detach();
  }
  
  for (int t = 0; t < tMot; t++){
      if (state[t] == 1){
        if (angulo[t] >= servo_max[t]){
          angulo[t] = servo_max[t];
          state[t] = 0;
        }
        else {
          angulo[t] += vel;
        }
        m[t].write(angulo[t]);
        if (debug == true){
          Serial.println(angulo[t]);
        }
      }
      else if (state[t] == 2){
        if (angulo[t] <= servo_min[t]){
          angulo[t] = servo_min[t];
          state[t] = 0;
        }
        else {
         angulo[t] -= vel; 
        }
        m[t].write(angulo[t]);
        if (debug == true){
          Serial.println(angulo[t]);
        }
      }
    }
    
  if (Serial.available() or BT.available() ){
    if (debug == true){
      recebido = Serial.read();
      comando += recebido;
      Serial.println(comando);
    }
    else{
      recebido = BT.read();
      comando += recebido;
      //recebido2 = ARD.read();
      //comando2 += recebido2;
    }

    /*if (recebido2 == ';'){
      if (comando2 == "cnt;"){
        BT.println("cnt;");
      }
      comando2 = "";
    }*/
    
    if (recebido == ';'){
      for (int i = 0; i < 6; i++){
        if (comando == servo_keys_dir[i]){
          if (state[i] == 0){
            state[i] = 2;
          }
          else if (state[i] == 2){
            state[i] = 0;
          }
        }
        else if (comando == servo_keys_esq[i]){
          if (state[i] == 0){
            state[i] = 1;
          }
          else if (state[i] == 1){
            state[i] = 0;
          }
        }
      }
      for (int f = 0; f < otherKeysAmmount; f++){
        if (comando == other_keys[f]){
          if (other_keys[f] == aumentar_vel){
            if (vel >= velocidade_max){
              vel = velocidade_max;
            }
            else {
              vel += 1;
            }
          }
          else if (other_keys[f] == diminuir_vel){
            if (vel <= velocidade_min){
              vel = velocidade_min;
            }
            else {
              vel -= 1;
            }
          }
        }
      }
      
      if (comando == emergencyStop and not emergency){
        emergency = true;
        BT.println(stoppedAlert);
      }
      else if (comando == systemRestart and emergency){
        emergency = false;
        BT.println(startedAlert);
      }
      
      String check = comando.substring(0,3);
      //Serial.println(check);
      if (check == "vel"){
        String cmd = comando.substring(4,comando.length()-1);
        int numbers = cmd.toInt();
        if (debug == true){
          Serial.print("Vel Mode | cmd: ");
          Serial.print(cmd);
          Serial.print(" | numbers: ");
          Serial.println(numbers);
        }

        if (numbers > velocidade_min || numbers < velocidade_max){
          vel = numbers;
        }
      }
      else if (check == "mot"){
        String cmd = comando.substring(3,4);
        String cmd2 = comando.substring(5,comando.length()-1);
        int motor = cmd.toInt();
        int ang = cmd2.toInt();

        if (debug == true){
          Serial.print("Ang Mode | cmd: ");
          Serial.print(cmd);
          Serial.print(" | cmd2: ");
          Serial.print(cmd2);
          Serial.print(" | Mot: ");
          Serial.print(motor);
          Serial.print(" | ang: ");
          Serial.println(ang);
        }

        if (ang >= servo_min[motor] || ang <= servo_max[motor]){
          int oldAng = angulo[motor];
          angulo[motor] = ang;
          servoMove(motor, oldAng, angulo[motor], vel);
        }
      }
      comando = "";
    }
  }
}

void servoMove(int mot, int oldAng, int newAng, int vel){
  if (mot == 0){
    m[0].attach(MOT[0]);
    m[3].attach(MOT[3]);
  }
  if ((oldAng - newAng)<0){
    for (int pos = oldAng; pos <= newAng; pos += vel) {
      m[mot].write(pos);
      delay(15);
    }
  }
  else{
    for (int pos = oldAng; pos >= newAng; pos -= vel) {
      m[mot].write(pos);
      delay(15);
    }
  }
  m[0].detach();
  m[3].detach();
}

void buzz(int ammount, int velocity){
  for (int i = 0; i < ammount; i++){
    digitalWrite(buzzer, HIGH);
    delay(velocity);
    digitalWrite(buzzer, LOW);
    delay(velocity);
  }
}
