/*
  Human-Following Robot - Arduino starter
  Board: Arduino Uno (example pinout)
  Sensors: 2 x HC-SR04 ultrasonic sensors
  Motor driver: L298N-compatible dual H-bridge
*/

const int LEFT_TRIG = 2;
const int LEFT_ECHO = 3;
const int RIGHT_TRIG = 4;
const int RIGHT_ECHO = 5;

const int ENA = 6;   // PWM: left motor speed
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 9;
const int IN4 = 10;
const int ENB = 11;  // PWM: right motor speed

const int MOTOR_SPEED = 120;          // Tune for your chassis (0-255)
const float FOLLOW_MIN_CM = 25.0;     // Stop if target is too close
const float FOLLOW_MAX_CM = 100.0;    // Stop if target is too far
const float TURN_DIFFERENCE_CM = 12.0;

float readDistanceCm(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 25000UL);
  if (duration == 0) return -1.0;  // No echo / out of range
  return duration * 0.0343f / 2.0f;
}

bool validDistance(float d) {
  return d >= 2.0f && d <= 300.0f;
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveForward(int speedValue) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

void turnLeft(int speedValue) {
  // Pivot turn; swap motor direction pins if your wiring differs.
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

void turnRight(int speedValue) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

void setup() {
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  stopMotors();
  Serial.println(F("Human-Following Robot ready."));
}

void loop() {
  float leftCm = readDistanceCm(LEFT_TRIG, LEFT_ECHO);
  delay(40); // Reduce cross-talk between ultrasonic sensors
  float rightCm = readDistanceCm(RIGHT_TRIG, RIGHT_ECHO);

  Serial.print(F("Left: "));
  Serial.print(leftCm);
  Serial.print(F(" cm | Right: "));
  Serial.print(rightCm);
  Serial.print(F(" cm | Action: "));

  bool leftValid = validDistance(leftCm);
  bool rightValid = validDistance(rightCm);

  // Stop if neither sensor sees a target.
  if (!leftValid && !rightValid) {
    stopMotors();
    Serial.println(F("STOP - no target"));
  } else {
    float nearest = leftValid && rightValid
        ? min(leftCm, rightCm)
        : (leftValid ? leftCm : rightCm);

    if (nearest < FOLLOW_MIN_CM) {
      stopMotors();
      Serial.println(F("STOP - target too close"));
    } else if (nearest > FOLLOW_MAX_CM) {
      stopMotors();
      Serial.println(F("STOP - target too far"));
    } else if (leftValid && rightValid &&
               leftCm + TURN_DIFFERENCE_CM < rightCm) {
      turnLeft(MOTOR_SPEED);
      Serial.println(F("TURN LEFT"));
    } else if (leftValid && rightValid &&
               rightCm + TURN_DIFFERENCE_CM < leftCm) {
      turnRight(MOTOR_SPEED);
      Serial.println(F("TURN RIGHT"));
    } else {
      moveForward(MOTOR_SPEED);
      Serial.println(F("MOVE FORWARD"));
    }
  }

  delay(80);
}
