// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <Servo.h>

// const char* ssid = "LOLA";
// const char* password = "413873D34";

// ESP8266WebServer server(80);

// const int ledPin = 2; // Pin donde está conectado el LED
// Servo myservo;
// int servoPin = D1; // Pin D1 del ESP8266

// void setup() {
//   Serial.begin(115200);

//   myservo.attach(servoPin); // Adjunta el servo al pin correspondiente
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(ledPin, LOW);

//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
//   Serial.println("Connected to WiFi");

//   server.on("/encender", []() {
//     digitalWrite(LED_BUILTIN, LOW);
//     myservo.write(0);
//     delay(1000); // Esperar un segundo
//     server.send(200, "text/plain", "LED encendido");
//     Serial.println("Encendido");
//   });

//   server.on("/apagar", []() {
//     digitalWrite(LED_BUILTIN, HIGH);
//     myservo.write(180);
//     delay(1000); // Esperar un segundo
//     server.send(200, "text/plain", "LED apagado");
//     Serial.println("Apagado");
//   });

//   server.begin();
//   Serial.println("HTTP server started");
// }

// void loop() {
//   server.handleClient();
// }


////////////luis///////////////////////////////////////////////////////////sddasdasdadsadsa

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// const char* ssid = "MAGNA";
// const char* password = "M@gnA-218";

// const char* ssid = "LOLA";
// const char* password = "413873D34";
const int leftForward = D1;
const int leftBackward = D2;
const int sensorPin1 = A0;
//const int sensorPin1 = D3;  // Conecta el pin D3 a la primera fotoresistencia
//const int sensorPin2 = A0; 
const char* ssid = "WlanItesca";
const char* password = "";
bool motorEncendido = false;
bool abrir = false;
bool cerrar = false;
bool abierto = false;
bool cerrado = true;

const int ledPin = LED_BUILTIN; // Utiliza el LED_BUILTIN integrado del ESP8266

ESP8266WebServer server(80);


////////////////////////////////////////////////
void girar(int velocidad) {
  if (velocidad > 0) {
    analogWrite(leftForward, velocidad);
    digitalWrite(leftBackward, LOW);
  } else if (velocidad < 0) {
    digitalWrite(leftForward, LOW);
    analogWrite(leftBackward, -velocidad);
  } else {
    detener();
  }
}

void detener() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
}

/////////////////////

void actualizarEstado() {
  if (abierto) {
    server.send(200, "text/html", "<html><body><h1>Estado: Abierto</h1></body></html>");
  } else {
    server.send(200, "text/html", "<html><body><h1>Estado: Cerrado</h1></body></html>");
  }
}
/////////////////////



void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Apagar el LED al inicio

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi. Please check your credentials.");
  } else {
    Serial.println("\nConnected to WiFi");
  }

  int valorFotorresistencia1 = analogRead(sensorPin1); ///////////
  Serial.print("Valor de la Fotorresistencia 1: ");
  Serial.println(valorFotorresistencia1);


  server.on("/encender", []() {
    int valorFotorresistencia1 = analogRead(sensorPin1);
    digitalWrite(ledPin, LOW); // cierra la cortina
    server.send(200, "text/plain", "LED encendido");
    ////
    motorEncendido = true;
    abrir = true;
    girar(-100);
    Serial.println("LED encendido");
    actualizarEstado();
    ////////////////////////////////////
    if (valorFotorresistencia1 > 60 && abrir) { // abre la cortina y se detiene cuando la fr superior detecta luz          && comando == '2'
    motorEncendido = false; 
    abrir = false;
    abierto = true;
    detener();
  }

  /////////////

  });

  server.on("/apagar", []() {
    digitalWrite(ledPin, HIGH); // baja la cortina
    server.send(200, "text/plain", "LED apagado");
    //
    motorEncendido = true;
    abrir = true;
    girar(100);
    Serial.println("LED encendido");
  });
  ////////
    server.on("/apagarMotor", []() {
    digitalWrite(ledPin, HIGH); // Apagar el motor
    server.send(200, "text/plain", "LED apagado");
    //
    motorEncendido = false;
    detener();
    Serial.println("LED apagado");
  });

  server.begin();
  Serial.println("HTTP server started");
}

///////////////////////////////////////////////////////





void loop() {
  server.handleClient();
    int valorFotorresistencia1 = analogRead(sensorPin1);
 // int valorFotorresistencia2 = analogRead(sensorPin2);

    Serial.print("Valor de la Fotorresistencia 1: ");
    Serial.println(valorFotorresistencia1);
  // Tu código puede ejecutar otras operaciones aquí si es necesario

  ///////////////////////////////////////// ififififf
  // int valorFotorresistencia1 = analogRead(sensorPin1);

  //   if (valorFotorresistencia1 > 60 && abrir) { // abre la cortina y se detiene cuando la fr superior detecta luz          && comando == '2'
  //   motorEncendido = false; 
  //   abrir = false;
  //   abierto = true;
  //   detener();
  // }

  // if (valorFotorresistencia1 < 38 && cerrar) { // cierra la cortina y se detiene cuando la fr inferior no detecta luz       && comando == '1'
  //   delay(1500);
  //   motorEncendido = false;
  //   cerrar = false;
  //   cerrado = true;
  //   detener();
  // }
  ///ASDASDASDAD
  //HOLA
}

//////////////////////// luis 11:18 funcionando sin if //////////////////////////////////




//./././././././././//l/l//l/l/





////////////////////////// luis con ifs ////////////////////////////

// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>

// const int leftForward = D1;
// const int leftBackward = D2;
// const int sensorPin1 = A0;
// const char* ssid = "WlanItesca";
// const char* password = "";
// bool motorEncendido = false;
// bool abrir = false;
// bool cerrar = false;
// bool abierto = false;
// bool cerrado = true;

// const int ledPin = LED_BUILTIN;

// ESP8266WebServer server(80);

// void girar(int velocidad) {
//   if (velocidad > 0) {
//     analogWrite(leftForward, velocidad);
//     digitalWrite(leftBackward, LOW);
//   } else if (velocidad < 0) {
//     digitalWrite(leftForward, LOW);
//     analogWrite(leftBackward, -velocidad);
//   } else {
//     detener();
//   }
// }

// void detener() {
//   digitalWrite(leftForward, LOW);
//   digitalWrite(leftBackward, LOW);
// }

// void setup() {
//   Serial.begin(9600);

//   pinMode(ledPin, OUTPUT);
//   digitalWrite(ledPin, HIGH);

//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi");

//   int attempts = 0;
//   while (WiFi.status() != WL_CONNECTED && attempts < 20) {
//     delay(1000);
//     Serial.print(".");
//     attempts++;
//   }

//   if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("\nFailed to connect to WiFi. Please check your credentials.");
//   } else {
//     Serial.println("\nConnected to WiFi");
//   }

//   server.on("/encender", []() {
//     digitalWrite(ledPin, LOW);
//     server.send(200, "text/plain", "LED encendido");
//     motorEncendido = true;
//     abrir = true;
//     girar(-100);
//     Serial.println("LED encendido");
//   });

//   server.on("/apagar", []() {
//     digitalWrite(ledPin, HIGH);
//     server.send(200, "text/plain", "LED apagado");
//     motorEncendido = true;
//     cerrar = true;
//     girar(100);
//     Serial.println("LED apagado");
//   });

//   server.on("/apagarMotor", []() {
//     digitalWrite(ledPin, HIGH);
//     server.send(200, "text/plain", "LED apagado");
//     motorEncendido = false;
//     detener();
//     Serial.println("LED apagado");
//   });

//   server.begin();
//   Serial.println("HTTP server started");
// }

// void loop() {
//   server.handleClient();

//   int valorFotorresistencia1 = analogRead(sensorPin1);

//   if (valorFotorresistencia1 > 60 && abrir) {
//     motorEncendido = false;
//     abrir = false;
//     abierto = true;
//     detener();
//   }

//   if (valorFotorresistencia1 < 38 && cerrar) {
//     delay(1500);
//     motorEncendido = false;
//     cerrar = false;
//     cerrado = true;
//     detener();
//   }
// }

