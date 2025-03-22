#include <Servo.h>

int sensor_pin1 = A0; // Analog pin for first soil moisture sensor
int sensor_pin2 = A1; // Analog pin for second soil moisture sensor
int relay_pin = 7;    // Digital pin for relay
int servo_pin = 9;    // Digital pin for servo motor
int pos=30;
unsigned long pumpStartTime; // Variable to store the pump start time
unsigned long pumpRunTime;   // Variable to store the pump run time
Servo servo; // Define servo motor object

void setup() {
  Serial.begin(9600);
  pinMode(sensor_pin1, INPUT);
  pinMode(sensor_pin2, INPUT);
  pinMode(relay_pin, OUTPUT);
  servo.attach(servo_pin); 
}

void loop() {
  int sensor_data1 = analogRead(sensor_pin1);
  int sensor_data2 = analogRead(sensor_pin2);
  
  // Soil moisture level for sensor 1
  Serial.println("Sensor 1 data:");
  Serial.println(sensor_data1);
  if (sensor_data1 > 950) {
    Serial.println("No moisture, soil is dry");
    digitalWrite(relay_pin, HIGH);
    pumpStartTime = millis(); // Store pump start time
    for(pos=30;pos<=100;pos+=1){
      servo.write(pos);
      delay(1000);
    }
    for(pos=100;pos>=30;pos-=1){
      servo.write(pos);
      delay(1000);
    }
    pumpRunTime = millis() - pumpStartTime; // Calculate pump run time
    Serial.print("Pump ran for: ");
    Serial.print(pumpRunTime / 1000); // Convert milliseconds to seconds for display
    Serial.println(" seconds");
  } else if (sensor_data1 >= 400 && sensor_data1 <= 700) {
    Serial.println("Some moisture, soil is medium");
    digitalWrite(relay_pin, LOW);
    servo.write(30); // Rotate servo to medium angle
  } else if (sensor_data1 < 400) {
    Serial.println("Soil is wet");
    digitalWrite(relay_pin, LOW);
    servo.write(30); // Rotate servo to minimum angle (wet)
  }
  
  // Soil moisture level for sensor 2
  Serial.println("Sensor 2 data:");
  Serial.println(sensor_data2);
  if (sensor_data2 > 950) {
    Serial.println("No moisture, soil is dry");
    digitalWrite(relay_pin, HIGH);
    pumpStartTime = millis(); // Store pump start time
    for(pos=30;pos<=100;pos+=1){
      servo.write(pos);
      delay(1000);
    }
    for(pos=100;pos>=30;pos-=1){
      servo.write(pos);
      delay(1000);
    } // Rotate servo to maximum angle (dry)
    pumpRunTime = millis() - pumpStartTime; // Calculate pump run time
    Serial.print("Pump ran for: ");
    Serial.print(pumpRunTime / 1000); // Convert milliseconds to seconds for display
    Serial.println(" seconds");
  } else if (sensor_data2 >400 and sensor_data2<700 ) {
    Serial.println("Some moisture, soil is medium");
    digitalWrite(relay_pin, LOW);
    servo.write(30); // Rotate servo to medium angle
  } else if (sensor_data2 < 400) {
    Serial.println("Soil is wet");
    digitalWrite(relay_pin, LOW);
    servo.write(30); // Rotate servo to minimum angle (wet)
  }
  
  delay(1000);
}
