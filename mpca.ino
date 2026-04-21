#include <Arduino.h>

#define RED 13
#define YELLOW 12
#define GREEN 11

#define PED_RED 8
#define PED_GREEN 7

#define IR 2
#define TRIG 9
#define ECHO 10
#define SOUND 6

#define VEH_GREEN_TIME 20000
#define VEH_YELLOW_TIME 3000
#define PED_GREEN_TIME 10000

unsigned long prev_time = 0;
unsigned long irStartTime = 0;

int state = 0;
long distance = 0;
bool trafficJam = false;

void setLight(int r, int y, int g);
long getDistance();

void setup() {
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(IR, INPUT_PULLUP);
  pinMode(SOUND, OUTPUT);

}

void loop() {
  unsigned long now = millis();

  distance = getDistance();
  int soundValue = !digitalRead(SOUND);
  Serial.println(soundValue);
  int irValue = !digitalRead(IR);

  if (irValue == 1) {
    if (irStartTime == 0) {
      irStartTime = millis();
    }
    if (millis() - irStartTime > 60000) {
      trafficJam = true;
      Serial.println("TRAFFIC DETECTED");
    }
  } else {
    irStartTime = 0;
    trafficJam = false;
  }

  Serial.print("Distance: ");
  Serial.println(distance);

  Serial.print("IR: ");
  Serial.println(irValue);

  switch (state) {

    case 0:
      setLight(LOW, LOW, HIGH);
      digitalWrite(PED_RED, HIGH);
      digitalWrite(PED_GREEN, LOW);
      

      Serial.println("VEHICLE GREEN");

      if (now - prev_time >= VEH_GREEN_TIME || (distance > 0 && distance < 15) || trafficJam) {
        prev_time = now;
        state = 1;
      }
      break;

    case 1:
      setLight(LOW, HIGH, LOW);
      digitalWrite(PED_RED, HIGH);
      digitalWrite(PED_GREEN, LOW);
     
      Serial.println("YELLOW");

      if (now - prev_time >= VEH_YELLOW_TIME) {
        prev_time = now;
        state = 2;
      }
      break;

    case 2:
      setLight(HIGH, LOW, LOW);
      digitalWrite(PED_RED, LOW);
      digitalWrite(PED_GREEN, HIGH);
      

      Serial.println("PEDESTRIAN GREEN");
 
        Serial.println("Vehicle Detected Close");
      }

      if (now - prev_time >= PED_GREEN_TIME) {
        prev_time = now;
        state = 0;
      }
      break;
  }

  delay(1000);
}

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  long dist = duration * 0.034 / 2;

  return dist;
}

void setLight(int r, int y, int g) {
  digitalWrite(RED, r);
  digitalWrite(YELLOW, y);
  digitalWrite(GREEN, g);
}
