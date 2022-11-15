/***************************************************
 *  TODAS AS VARIAVEIS ABAIXO PODEM SER MODIFICADAS
 *  DE ACORDO COM A PREFERENCIA DO USUARIO!
 ***************************************************/

/*************************************************
 * Definições das Funções de Ativação
 *************************************************/
// Define os eventos que são recebidos pelo bluetooth
// EX: if (characterRecebido == "base_dir;")
#define motor1_direita "base_dir;"
#define motor1_esquerda "base_esq;"
#define motor2_direita "base_dir;"
#define motor2_esquerda "base_esq;"

/*************************************************
 * Definições Pinos Seriais
 *************************************************/

// Pinos RX e TX do Bluetooth
#define bt_rx 7
#define bt_tx 8

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
 * Definições dos Angulos Iniciais
 *************************************************/

#define ini_mot1 90 // Base
#define ini_mot2 90 // Suporte 1
#define ini_mot3 90 // Suporte 2
#define ini_mot4 90 // Rotação da garra
#define ini_mot5 90 // Inclinação da garra
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
#define max_mot6 180
#define min_mot6 0
