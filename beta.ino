//**********************************25/10/2022
int MOT_DER_A = 10;
int MOT_DER_B = 11;
int MOT_IZQ_A = 5;
int MOT_IZQ_B = 6;

int InfraD = 12;//Sensor Infrarojo derecha
//int LecturaR =0;
int InfraI = 9;//Sensor Infrarojo Izquierdo
//int LecturaL =0;

int trigPin1 = 7;
int echoPin1 = 8;

int trigPin2 = 3;
int echoPin2 = 4;

long duracion, distancia1, distancia2;

void setup() {

  Serial.begin(9600);
  delay (100);
  pinMode (MOT_DER_A, OUTPUT);
  pinMode (MOT_DER_B, OUTPUT);
  pinMode (MOT_IZQ_A, OUTPUT);
  pinMode (MOT_IZQ_B, OUTPUT);

  pinMode (InfraD, INPUT);
  pinMode (InfraI, INPUT);

  pinMode (echoPin1, INPUT);
  pinMode (trigPin1, OUTPUT);

  pinMode (echoPin2, INPUT);
  pinMode (trigPin2, OUTPUT);
  delay(5000);
}
int ping1(int trigPin1, int echoPin1) {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  float duration1 = pulseIn(echoPin1, HIGH);
  int distancia1 = duration1 * 0.034 / 2; // Cálculo de la distancia en cm
  return (distancia1);
}
int ping2(int trigPin2, int echoPin2) {
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);    // Deja en LOW 2 microsegundos para "resetar" el sensor
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);   // Ponemos el trig a HIGH durante 10 microsegundos, el sensor enviará luego 8 pulsos
  digitalWrite(trigPin2, LOW);
  float duration2 = pulseIn(echoPin2, HIGH); // Capta el tiempo que pasa hasta que retornan los pulsos.
  int distancia2 = duration2 * 0.034 / 2; // Cálculo de la distancia en cm
  return (distancia2);
}

void loop() {
  /* LecturaR=digitalRead(InfraD);
    LecturaL=digitalRead(InfraI);
    Serial.print("Sensor Derecho: ");
    Serial.print(LecturaR);
    Serial.print("Sensor Izquierdo: ");
    Serial.println(LecturaL);
    delay(100);
    }*/
  distancia2 = ping2(trigPin2, echoPin2);
  if (distancia2 <= 8 && distancia2 >= 1) {
    //para retroceder
    Stop();
    Retroceder();
    //girar a la derecha
    ImpulsoDerecha();
    GiroDerecha();
    //delay(300);
  }

  distancia1 = ping1(trigPin1, echoPin1);
  if (distancia1 <= 8 && distancia1 >= 1) {
    // Codigo para retroceder
    Stop();
    Retroceder();
    // Codigo para girar a la izquierda
    ImpulsoIzquierda();
    GiroIzquierda();
    //delay(300);
  }

  //El etado del infrarojo D e I es 1-1 cambia a 0-0 por el signo "!" en el Centro de la linea negra avanza de Frente
  //distancia1 = ping1(trigPin1,echoPin1);
  //distancia2 = ping2(trigPin2,echoPin2);
  if (distancia1 <= 5 && distancia1 >= 2 && distancia2 <= 5 && distancia2 >= 2 ) {
    // Codigo para retroceder
    Stop();
    Retroceder();
    // Codigo para girar a la derecha
    GiroIzquierda();
  }
  if (!digitalRead(InfraD) && !digitalRead(InfraI) && distancia1 >= 5 && distancia2 >= 5) {//En el Centro de la linea negra avanza de Frente
    Avanzar();
  }
  else if (digitalRead(InfraD) && !digitalRead(InfraI)) {// InfraD en linea negra girar a la Derecha
    ImpulsoIzquierda();
    GiroIzquierda();
  }
  else if (!digitalRead(InfraD) && digitalRead(InfraI)) {// InfraI en linea negra girar a la Izquierda
    ImpulsoDerecha();
    GiroDerecha();
  }
  else if (digitalRead(InfraD) && digitalRead(InfraI) && distancia1 >= 5 && distancia2 >= 5) { // InfraD-InfraI ambos en la linea negra se detiene
    Stop();
    Retroceder();
    GiroDerecha();
  }






}
void Avanzar() {// Avanza de frente
  digitalWrite(MOT_DER_A, 1);
  digitalWrite(MOT_DER_B, 0);
  digitalWrite(MOT_IZQ_A, 1);
  digitalWrite(MOT_IZQ_B, 0);
}
void Retroceder() {// Avanza de frente
  digitalWrite(MOT_DER_A, 0);
  digitalWrite(MOT_DER_B, 1);
  digitalWrite(MOT_IZQ_A, 0);
  digitalWrite(MOT_IZQ_B, 1);
  delay(800);
}
void ImpulsoDerecha() {//Gira a la derecha hasta posicionarse
  digitalWrite(MOT_DER_A, 0);
  digitalWrite(MOT_DER_B, 0);
  digitalWrite(MOT_IZQ_A, 1);
  digitalWrite(MOT_IZQ_B, 0);
  delay(200);
}
void ImpulsoIzquierda() {// Gira a la izquierda hasta posicionarse
  digitalWrite(MOT_DER_A, 1);
  digitalWrite(MOT_DER_B, 0);
  digitalWrite(MOT_IZQ_A, 0);
  digitalWrite(MOT_IZQ_B, 0);
  delay(200);
}
void Stop() {// Se detienen los motores
  digitalWrite(MOT_DER_A, 0);
  digitalWrite(MOT_DER_B, 0);
  digitalWrite(MOT_IZQ_A, 0);
  digitalWrite(MOT_IZQ_B, 0);
  delay(250);
}
void GiroIzquierda() {//Gira a la derecha hasta posicionarse
  digitalWrite(MOT_DER_A, 1);
  digitalWrite(MOT_DER_B, 0);
  digitalWrite(MOT_IZQ_A, 0);
  digitalWrite(MOT_IZQ_B, 1);
  delay(300);
}
void GiroDerecha() {//Gira a la derecha hasta posicionarse
  digitalWrite(MOT_DER_A, 0);
  digitalWrite(MOT_DER_B, 1);
  digitalWrite(MOT_IZQ_A, 1);
  digitalWrite(MOT_IZQ_B, 0);
  delay(300);
}
