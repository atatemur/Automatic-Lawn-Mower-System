//PINS
const byte trig = 9;
const byte leftEcho = 6;
const byte rightEcho = 10;
const byte frontEcho = 11;
const byte motor1Forward = 3;
const byte motor1Backward = 2;
const byte motor2Forward = 5;
const byte motor2Backward = 4;
const byte slideSwitch = 12;

//Value holders
unsigned long frontDuration;
unsigned long leftDuration;
unsigned long rightDuration;
unsigned short frontDistance;
unsigned short leftDistance;
unsigned short rightDistance;


void setup()
{
  pinMode(slideswitch, INPUT);
  //Sonic sensor pins
  pinMode(trig, OUTPUT);
  pinMode(leftEcho,INPUT);
  pinMode(rightEcho,INPUT);
  pinMode(frontEcho,INPUT);
  
  //Left motor pins
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);
  
  //rightmotorPins
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);

}
int mode = 0;

void loop()
{
  
  delay(10); // Delay a little bit to improve simulation performance
}

void PingDistance()
{
  // Ensuring a clean HIGH pulse by starting with LOW.
  // The sensor initiates when a HIGH signal for about 10μs is given.
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Wait for the pin to become HIGH ( Recieve the pulse )
  // and starts timing.
  frontduration = pulseIn(frontEcho, HIGH);
  leftduration = pulseIn(leftEcho, HIGH);
	rightduration = pulseIn(rightEcho,HIGH);
  
  
}
