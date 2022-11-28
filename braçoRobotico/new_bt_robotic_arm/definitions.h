/***************************************************
 *  TODAS AS VARIAVEIS ABAIXO PODEM SER MODIFICADAS
 *  DE ACORDO COM A PREFERENCIA DO USUARIO!
 ***************************************************/

// Modo teste
#define debug false // modo normal: debug = false

// Total de motores
#define tMot 6 

// Intervalo entre leituras em milisegundos
#define time_delay 50

// Incrementos iniciais em angulos
#define i_speed 1

// Velocidade maxima e minima
#define velocidade_max 5
#define velocidade_min 1

/*************************************************
 * Definições das Funções de Ativação
 *************************************************/
 
// Define os eventos que são recebidos pelo bluetooth
// EX: if (characterRecebido == "base_dir;")

#define m1_direita "bd;" // base direita
#define m1_esquerda "be;" // base esquerda

#define m2_direita "s1d;" // suporte 1 direita
#define m2_esquerda "s1e;" // suporte 1 esquerda

#define m3_direita "s2d;" // suporte 2 direita
#define m3_esquerda "s2e;"// suporte 2 esquerda

#define m4_direita "grd;" // garra rotação direita
#define m4_esquerda "gre;" // garra rotação esquerda

#define m5_direita "gic;"  // garra inclinação cima
#define m5_esquerda "gib;" // garra inclinação baixo

#define m6_direita "ga;"  // garra abrir
#define m6_esquerda "gf;" // garra fechar

// Quantidade de eventos que NÃO são dos servomotores
#define otherKeysAmmount 2 
// Se adicionar mais eventos mude "otherkeys" para o numero de eventos novos!

#define aumentar_vel "v+;" // Aumenta a velocidade
#define diminuir_vel "v-;" // Diminui a velocidade

// Para enviar uma velocidade especifica utilize "vel_N;" [ EX: "vel_10;" ]

/*************************************************
 * Definições das Funções do Outro Arduino
 *************************************************/

#define emergencyStop "stp;" // Parada de emergencia
#define systemRestart "rst;" // Reiniciar apos parada

// As funções abaixo enviam para o aplicativo no celular
#define count "cnt;" // Adicionar 1 objeto na contagem

#define stoppedAlert "ste;" // Alerta para quando o arduino entrar em modo de emergencia
#define startedAlert "sta;" // Alerta quando o arduino sair do modo de emergencia

/*************************************************
 * Definições Pinos Seriais
 *************************************************/

// Pinos RX e TX do Bluetooth
#define bt_rx 7
#define bt_tx 8

// Pinos RX e TX do outro arduino
#define ard_rx 2
#define ard_tx 4

/*************************************************
 * Definições Pinos dos Motores
 *************************************************/

// Servomotores MG995
#define MOT1 3  //pino do servomotor 1
#define MOT2 5  //pino do servomotor 2
#define MOT3 6  //pino do servomotor 3

// Servomotores SG92R
#define MOT4 9  //pino do servomotor 4
#define MOT5 10 //pino do servomotor 5
#define MOT6 11 //pino do servomotor 6

/*************************************************
 * Definições Pinos Extras
 *************************************************/

#define buzzer 13 // pino do buzzer para alertas
#define relay 12 // pino do rele

/*************************************************
 * Definições dos Angulos Iniciais
 *************************************************/

#define ini_mot1 90 // Base
#define ini_mot2 135 // Suporte 1
#define ini_mot3 180 // Suporte 2
#define ini_mot4 90 // Rotação da garra
#define ini_mot5 45 // Inclinação da garra
#define ini_mot6 0 // Abertura da garra [ 90 = Aberta || 0 = Fechada ]

/*************************************************
 * Definições dos Maximos e Minimos
 *************************************************/

// Base
#define max_mot1 180
#define min_mot1 0

// Suporte 1
#define max_mot2 180
#define min_mot2 0

// Suporte 2
#define max_mot3 180
#define min_mot3 0

// Rotação da garra
#define max_mot4 180
#define min_mot4 0

// Inclinação da garra
#define max_mot5 180
#define min_mot5 0

// Abertura da garra
#define max_mot6 90
#define min_mot6 0
