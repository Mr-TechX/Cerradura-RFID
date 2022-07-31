//  /$$   /$$ /$$ /$$                                /$$$$$$                                              /$$                
// | $$  | $$| $$|__/                               /$$__  $$                                            | $$                
// | $$  | $$| $$ /$$  /$$$$$$$  /$$$$$$   /$$$$$$$| $$  \__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$   /$$$$$$$| $$$$$$$   /$$$$$$ 
// | $$  | $$| $$| $$ /$$_____/ /$$__  $$ /$$_____/| $$       |____  $$| $$_  $$_  $$ |____  $$ /$$_____/| $$__  $$ /$$__  $$
// | $$  | $$| $$| $$|  $$$$$$ | $$$$$$$$|  $$$$$$ | $$        /$$$$$$$| $$ \ $$ \ $$  /$$$$$$$| $$      | $$  \ $$| $$  \ $$
// | $$  | $$| $$| $$ \____  $$| $$_____/ \____  $$| $$    $$ /$$__  $$| $$ | $$ | $$ /$$__  $$| $$      | $$  | $$| $$  | $$
// |  $$$$$$/| $$| $$ /$$$$$$$/|  $$$$$$$ /$$$$$$$/|  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$|  $$$$$$$| $$  | $$|  $$$$$$/
//  \______/ |__/|__/|_______/  \_______/|_______/  \______/  \_______/|__/ |__/ |__/ \_______/ \_______/|__/  |__/ \______/ 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  AUTHOR : Ulises Camacho - TecnoProjects Security
//  PROJECT : Control de accesoa puertas con RC522 y arduino nano
//  VERSION : 1.0.0
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <SPI.h>     // Incluir biblioteca externa SPI.h
#include <MFRC522.h> // Incluir biblioteca externa MFRC522.h
 
#define SS_PIN 10                 // Definiendo el pin del SS
#define RST_PIN 9                 // Definiendo el pin del Reset
#define RELAY 6                   // Definiendo el pin del Relay
MFRC522 mfrc522(SS_PIN, RST_PIN); // Crea la instancia MFRC522
 
void setup() // Codigo de configuracion de una sola ejecucion
{
  Serial.begin(9600);                                    // Inicializa la comunicacion serial
  SPI.begin();                                           // Inicializa el bus SPI
  mfrc522.PCD_Init();                                    // Inicializa el MFRC522
  pinMode(RELAY, OUTPUT);                                // Establece el pin de Relé como salida
  digitalWrite(RELAY, LOW);                              // Desactiva el pin Relé dandole una condicion logica de 0v
  Serial.println("Ponga su Tarjeta para la lectura..."); // Muestra el mensaje "Ponga su Tarjeta para la lectura..." en el puerto serial
  Serial.println();                                      // Escribe caracteres en codigo ASCII en el puerto serial

}

void loop() // Codigo de ejecucion continua o en bucle
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) // Verificando si hay nuevas tarjetas presentes
  {
    return; // Detener
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) // Seleccionar tarjeta presente
  {
    return; // Detener
  }
  // Muestra el UID sobre el Monitor Serial
  Serial.print("UID :");                  // Mostrar mensaje "UID tag :" en el puerto serial
  String content= "";                         // Variable String sin contenido de texto
//byte letter;                                // Declaracion de la variable letter con Byte
  for (byte i = 0; i < mfrc522.uid.size; i++) // inicia un bucle en el que la variable "i" es igual a cero, i es menor a mfrc522...., y a "i" se le suma un digito (i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");            // Imprimir si mfrc522.uid.... es menor a 0x10 (un dígito) anteponer en blanco Y 0, de lo contrario en blanco
     Serial.print(mfrc522.uid.uidByte[i], HEX);                           // Mostrar el numero en hexadecimal en el puerto serial
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  // Imprimir si mfrc522.uid.... es menor a 0x10 (un dígito) anteponer en blanco Y 0, de lo contrario en blanco (para una variable string concatenando un numero a la vez)
     content.concat(String(mfrc522.uid.uidByte[i], HEX));                 // Mostrar el numero en hexadecimal en el puerto serial (para una variable string concatenando un numero a la vez)
  }
  Serial.println();                          // Escribe caracteres en codigo ASCII en el puerto serial
  Serial.print("Message : ");                // Muestra el mensaje "Message : " en el puerto serial
  content.toUpperCase();                     // Tomar la cadena de Texto y delvolver una hecha a base de puras letras MAYUSCUlAS

//-----------------------------[ Bloque de codigo para dar acceso al llavero 1 ]-----------------------------

  if (content.substring(1) == "AE B0 24 D9") // [Cambiar UID con acceso] Si el UID de la tarjeta observada es igual a "UID" Ejecutar:
  {
    Serial.println("Acceso Autorizado"); // Mostrar mensaje "Acceso autorizado" en el puerto serial
  digitalWrite(RELAY, HIGH);             // Activar el pin digital del relé
  delay(1000);                           // Demora de 1000
  digitalWrite(RELAY,LOW);               // Desactiva el pin Relé dandole una condicion logica de 0v
  }

//-----------------------------[ Bloque de codigo para dar acceso a la tarjeta 1 ]-----------------------------

  if (content.substring(1) == "30 86 55 A8") // [Cambiar UID con acceso] Si el UID de la tarjeta observada es igual a "UID" Ejecutar:
  {
    Serial.println("Acceso Autorizado"); // Mostrar mensaje "Acceso autorizado" en el puerto serial
  digitalWrite(RELAY, HIGH);             // Activar el pin digital del relé
  delay(1000);                           // Demora de 1000
  digitalWrite(RELAY,LOW);               // Desactiva el pin Relé dandole una condicion logica de 0v
  }
  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Explicacion del proyecto:
//
// Proyecto de sistema de apertura de puertas con arduino y lector RFID
// el sistema funciona cuando el lector recibe un codigo UID de una tarjeta [llave]
// si el UID de la tarjeta presentada esta autorizado previamente en el codig a abrir la cerradura
// se abrira la cerradura por un tiempo para poder abrir la puerta y posteriormente se cerrara automaticamente
// una vez cerrada nuevamente la cerradura solo podra abrirse cuando el modulo RC522 reciba un UID autorizado
//++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Diseño de pin típico utilizado:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+           +  MFRC522     +  Arduino      +  Arduino +  Arduino  +  Arduino        +  Arduino   +
//+           +  Reader/PCD  +  Uno/101      +  Mega    +  Nano v3  +  Leonardo/Micro +  Pro Micro +
//+ Signal    +  Pin         +  Pin          +  Pin     +  Pin      +  Pin            +  Pin       +
//+ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+ RST/Reset +  RST         +  9            +  5       +  D9       +  RESET/ICSP-5   +  RST       +
//+ SPI SS    +  SDA(SS)     +  10           +  53      +  D10      +  10             +  10        +
//+ SPI MOSI  +  MOSI        +  11 / ICSP-4  +  51      +  D11      +  ICSP-4         +  16        +
//+ SPI MISO  +  MISO        +  12 / ICSP-1  +  50      +  D12      +  ICSP-1         +  14        +
//+ SPI SCK   +  SCK         +  13 / ICSP-3  +  52      +  D13      +  ICSP-3         +  15        +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++
//+                     COPYRIGHT                     +
//+   © 2022 UlisesCamacho - TecnoProjects Security   +
//+     https://portafolio.ulisescamacho.repl.co      +
//+                Derechos reservados                +
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
