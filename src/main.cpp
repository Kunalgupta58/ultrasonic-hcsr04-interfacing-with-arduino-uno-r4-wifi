#include <Arduino.h>

#define trigPin 9
#define echoPin 10
void setup() {
// write your initialization code here
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

void loop() {
// write your code here
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration=pulseIn(echoPin, HIGH);
    long distance=duration*0.034 /2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
}