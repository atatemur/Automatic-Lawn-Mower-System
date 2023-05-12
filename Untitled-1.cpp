//PINS
const byte trig = 9;
const byte leftEcho = 10;
const byte frontEcho = 11;
const byte motor1Forward = 3;
const byte motor1Backward = 2;
const byte motor2Forward = 5;
const byte motor2Backward = 4;
const byte slideSwitch = 12;

//Value holders
unsigned long frontDuration;
unsigned long leftDuration;
unsigned short frontDistance;
unsigned short leftDistance;
unsigned int distancefromborder = 10;
unsigned int turns = 0;

void setup()
{
    pinMode(slideSwitch, INPUT);
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
  PingRightDistance();
  PingFrontDistance();

  if(frontDistance>334&&leftDistance<=distancefromborder)
  {
    BeginMowing();
  }


  delay(10); // Delay a little bit to improve simulation performance
}

void TurnRight()
{
  digitalWrite(motor1Forward,LOW);
  digitalWrite(motor1Backward,LOW);
  digitalWrite(motor2Forward,HIGH);
  digitalWrite(motor2Forward, LOW);
  turns++;
}

void StopMoving()
{
  digitalWrite(motor1Forward,LOW);
  digitalWrite(motor1Backward,LOW);
  digitalWrite(motor2Forward,LOW);
  digitalWrite(motor2Forward, LOW);

}
void BeginMowing()
{
  digitalWrite(motor1Forward,HIGH);
  digitalWrite(motor1Backward,LOW);
  digitalWrite(motor2Forward,HIGH);
  digitalWrite(motor2Backward,LOW); 
}
void PingFrontDistance()
{
  // Ensuring a clean HIGH pulse by starting with LOW.
  // The sensor initiates when a HIGH signal for about 10μs is given.
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
  
  // Wait for the pin to become HIGH ( Recieve the pulse )
  // and starts timing.
    frontDuration = pulseIn(frontEcho, HIGH);

    frontDistance = (frontDuration/2) / 29.1; 
}

void PingLeftDistance()
{
  // Ensuring a clean HIGH pulse by starting with LOW.
  // The sensor initiates when a HIGH signal for about 10μs is given.
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
  
  // Wait for the pin to become HIGH ( Recieve the pulse )
  // and starts timing.
    leftDuration = pulseIn(leftEcho, HIGH);
  
    leftDistance = (leftDuration/2) / 29.1; 

}

