#include <TimeLib.h>
#include <Time.h>

//Positivo (+) a pin A0
//Negativo (-) a GND

#define R_LOAD        2.29 // Resistencia que se usa para medir corriente indirectamente
#define FINAL_VOLTAGE 0.0 // Valor definido por el fabricante, LiPo 3.0V/cell
#define V_DROP        0.0 // VDS MOSFET 0.116 para VG 5V & 0.308 para VG 3.3V

float voltaje = 0;
float corriente = 0;
float capacidad = 0;
unsigned long t = 0;

unsigned long counter = 1;

bool startButton = false;
bool testComplete = false;
bool emergencyStop = false;

void setup() {
  Serial.begin(9600);
  //analogReference(DEFAULT);
  pinMode(3, INPUT);
  time_t t = now();
  // print labels

  Serial.print("No");
  Serial.print("\t");

  Serial.print("V (V)");
  Serial.print("\t");

  Serial.print("I (A)");
  Serial.print("\t");
  
  Serial.print("Capacidad");
  Serial.print("\t");
  
  Serial.println("Tiempo de descarga (ms)");
}

void loop() {

  emergencyStop = digitalRead(3);
  t = millis();
  digitalWrite(13, HIGH);

  if (testComplete == true) {
    Serial.println("Prueba Completada!");
    while (1) {
      //time waster, inefficiency FTW!
    }
  } else {
    Serial.print(counter);
    Serial.print("\t");

    voltaje = (analogRead(A0) * 4.85 / 1023) - V_DROP; // Cambiar el numerador (i.e.: 4.75) hasta que se lea el mismo numero que en el multimetro, he descubierto que tiende a ser "Voltaje del pin de 5V + 0.15V"
    Serial.print(voltaje);
    Serial.print("\t");

    corriente = voltaje / R_LOAD;
    Serial.print(corriente);
    Serial.print("\t");

    capacidad = capacidad + corriente / 3600;;
    Serial.print(capacidad);
    Serial.print("\t");
    Serial.print("\t");

    Serial.println(t);

    counter = counter + 1;
    delay(10);
  }
  if (emergencyStop == true) {
    testComplete = true;
    Serial.println("Parada de EMERGENCIA!");
  }

  //  if (voltage <= FINAL_VOLTAGE) {
  //    digitalWrite(13, LOW);
  //    delay(500);
  //    digitalWrite(13, HIGH);
  //    delay(500);
  //    digitalWrite(13, LOW);
  //    delay(500);
  //
  //    testComplete = true;
  //  }
}
//Case closed... or not
