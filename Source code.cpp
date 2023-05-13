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
int resets = 0;
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

void loop()
{
  PingFrontDistance();
  PingLeftDistance();
  //Check if ON/OFF switch is flipped
  if(digitalRead(slideSwitch)==LOW) ShutDown();
  else isRunning = true;
  //check if job is finished/is out of range
  if(distancefromborder>=334) ShutDown();
  //helps to not get machine stuck doing turns

  //check so that it doesn't run when it shouldn't
  if(isRunning)
  {
    //some serial window lines used for debugging
    //they are not necessary
    Serial.println("------------------");
	  Serial.println(frontDistance);
    Serial.println(distancefromborder);
	  Serial.println(turns);

      //checking to make sure if the machine has made a full circe
      if(turns>=3)
      {
        //increase the distance so that it can start closing in on the middle
        distancefromborder+=20;
        //initial value has to be 1 bigger as there is one less turn in the initial run
        turns=-1;
      }
      //checks if there are no obstacles in front of the machine
      //second part makes sure the machine doesn't stray too far away from the wall
      if(frontDistance > distancefromborder && leftDistance <= distancefromborder)
      {
      //if both checks are passed then the machine should begin moving
        BeginMowing();
      }
      else
      {
        //once there is an obstacle in close vaccinity the machine should turn
        TurnRight();
        //delay is dependant on size of the wheel, this is the most universal one,
        //but it is without doubt not perfect for every set up
        delay(500);
      }
  }
  else //if no longer running the machine should stop doing things
  {
    StopMoving();
  }
  delay(10); // Delay a little bit to improve simulation performance
}
void ShutDown() 
{
//shuts down the entire machine
  isRunning=false;
  distancefromborder = 30;
  resets=0;
  turns=0;
  StopMoving();
}


void TurnRight()
{
  //machine should already be in movement if a turn is necessary
  //if machine is already moving we only need to disable the right motor,
  //because the left one will do the turn on its own
  digitalWrite(motor1Forward,LOW);
  turns++;
}

void StopMoving()
{
  //Stops ALL the motors
  digitalWrite(motor1Forward,LOW);
  digitalWrite(motor1Backward,LOW);
  digitalWrite(motor2Forward,LOW);
  digitalWrite(motor2Forward, LOW);

}
void BeginMowing()
{
  //Starts both motors forward
  digitalWrite(motor1Forward,HIGH);
  digitalWrite(motor1Backward,LOW);
  digitalWrite(motor2Forward,HIGH);
  digitalWrite(motor2Backward,LOW); 
}
void PingFrontDistance()
{
  //A method that calls on the front ultrasonic distance sensor to detect 
  //the distance to  any nearby objects

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

    //distance is calculated with a special formula dervied from the speed of sound
    frontDistance = (frontDuration/2) / 29.1; 
}

void PingLeftDistance()
{
  //A method that calls on the front ultrasonic distance sensor to detect 
  //the distance to  any nearby objects

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
  
      //distance is calculated with a special formula dervied from the speed of sound
    leftDistance = (leftDuration/2) / 29.1; 

}

