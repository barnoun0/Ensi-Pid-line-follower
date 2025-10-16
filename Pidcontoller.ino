// === IR Sensor + PID Line Follower (Final Fixed Version) ===

// === IR SENSOR SETTINGS ===
const int sensorPins[6] = {A0, A1, A2, A3, A4, A5};
// If your leftmost sensor is A0 and rightmost is A5, keep weights as below:
const int sensorWeights[6] = {40, 10, 2, -2, -10, -40};

// === MOTOR PINS ===
#define IN1 6 
#define IN2 10  
#define IN3 11 
#define IN4 9  

int sensorValues[6];
int digitalValues[6];
int blackVal[6];
int whiteVal[6];
int threshold[6];

float Kp = 15;
float Ki = 0.01;
float Kd = 2;

float error = 0;
float previousError = 0;
float integral = 0;
float derivative = 0;

int motorSpeed = 100;

const int numReadings = 150;

void calibrateSensors() {
  long sum;

  // --- BLACK CALIBRATION ---
  digitalWrite(13, HIGH);
  delay(2000);  
  for (int i = 0; i < 6; i++) {
    sum = 0;
    for (int count = 0; count < numReadings; count++) {
      sum += analogRead(sensorPins[i]);
    }
    blackVal[i] = sum / numReadings;
    delay(10);
  }

  // --- WHITE CALIBRATION ---
  digitalWrite(13, LOW);
  delay(4000);  
  for (int i = 0; i < 6; i++) {
    sum = 0;
    for (int count = 0; count < numReadings; count++) {
      sum += analogRead(sensorPins[i]);
    }
    whiteVal[i] = sum / numReadings;
    delay(10);
  }

  for (int i = 0; i < 6; i++) {
    threshold[i] = (whiteVal[i] + blackVal[i]) / 2;
  }
}

void setMotor(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  if (leftSpeed >= 0) {
    analogWrite(IN3, leftSpeed);   // Forward
    analogWrite(IN4, 0);
  } else {
    analogWrite(IN3, 0);
    analogWrite(IN4, -leftSpeed);  // Backward
  }

  if (rightSpeed >= 0) {
    analogWrite(IN1, rightSpeed);  // Forward
    analogWrite(IN2, 0);
  } else {
    analogWrite(IN1, 0);
    analogWrite(IN2, -rightSpeed); // Backward
  }
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  for (int i = 0; i < 6; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  pinMode(13, OUTPUT);
  pinMode(2, INPUT); // Optional start button

  calibrateSensors();

  while (digitalRead(2) == LOW) {
    digitalWrite(13, HIGH);
  }
  digitalWrite(13, LOW);
}

void loop() {
  int weightedSum = 0;
  int activeCount = 0;

  for (int i = 0; i < 6; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    digitalValues[i] = (sensorValues[i] < threshold[i]) ? 1 : 0;

    if (digitalValues[i]) {
      weightedSum += sensorWeights[i];
      activeCount++;
    }
  }

  if (activeCount > 0) {
    error = (float)weightedSum / activeCount;
  } else {
    error = previousError;  // Line lost
  }

  integral += error;
  derivative = error - previousError;
  float correction = Kp * error + Ki * integral + Kd * derivative; // yrodha valeur ynajem yakrah pont h

  int leftSpeed = motorSpeed - correction;
  int rightSpeed = motorSpeed + correction;

  setMotor(leftSpeed, rightSpeed);

  previousError = error;
}
