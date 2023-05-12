/*
  AnalogReadSerial
  Reads an analog input (potentiometer) on pin 0,
  prints the result to the serial monitor.

  OPEN THE SERIAL MONITOR TO VIEW THE OUTPUT FROM
  THE POTENTIOMETER >>

  Attach the center pin of a potentiometer to pin
  A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/




//PINS
const byte trig = 9;
const byte leftEcho = 10;
const byte frontEcho = 11;
const byte motor1Forward = 3;
const byte motor1Backward = 2;
const byte motor2Forward = 4;
const byte motor2Backward = 5;
const byte slideSwitch = 12;

//Value holders
unsigned long frontDuration;
unsigned long leftDuration;
unsigned short frontDistance;
unsigned short leftDistance;
unsigned int distancefromborder = 30;
int turns = 0;
bool isSetUp = false;
bool isRunning = true;





void setup()
{
    pinMode(slideSwitch, INPUT);
  //Sonic sensor pins
    pinMode(trig, OUTPUT);
    pinMode(leftEcho,INPUT);
    pinMode(frontEcho,INPUT);
  
  //Left motor pins
    pinMode(motor1Forward, OUTPUT);
    pinMode(motor1Backward, OUTPUT);
  
  //rightmotorPins
    pinMode(motor2Forward, OUTPUT);
    pinMode(motor2Backward, OUTPUT);
  
    Serial.begin(9600);
}
int mode = 0;

void loop()
{
  PingFrontDistance();
  PingLeftDistance();
  //Check if ON/OFF switch is flipped
  if(digitalRead(slideSwitch)==LOW) ShutDown();
  else isRunning = true;
  //check if job is finished/is out of range
  if(distancefromborder>=334) ShutDown();

  //check so that it doesn't run when it shouldn't
  if(isRunning)
  {
    Serial.println("------------------");
	Serial.println(frontDistance);
    Serial.println(distancefromborder);
	Serial.println(turns);

      if(turns>=3)
      {
        distancefromborder+=20;
        turns=-1;
      }
      if(frontDistance > distancefromborder && leftDistance <= distancefromborder)
      {
        BeginMowing();
      }
      else
      {
        TurnRight();
        delay(500);
      }
  	delay(10);
  }
  else
  {
    StopMoving();
  }
  delay(10); // Delay a little bit to improve simulation performance
}

void ShutDown()
{
  isRunning=false;
}

void TurnRight()
{
  digitalWrite(motor1Forward,LOW);
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

