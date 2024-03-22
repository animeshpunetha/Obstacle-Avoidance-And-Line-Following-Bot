int trig = A2;
int echo = A3;
int servo = A5;

int rightDistance, leftDistance, frontDistance,leftSensor,rightSensor;

void setup()
{
    Serial.begin(9600);

    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(servo, OUTPUT);

    for(int angle=70; angle<=140; angle = angle + 5)
    {
        servoFunction(servo,angle);
    }

    for(int angle=140; angle>=0; angle = angle - 5)
    {
        servoFunction(servo,angle);
    }

    for(int angle=0; angle<=70; angle = angle + 5)
    {
        servoFunction(servo,angle);
    }

    frontDistance = ultrasonicRead();
    delay(20);

}

void loop()
{
    frontDistance = ultrasonicRead();

    leftSensor = digitalRead(A0);
    rightSensor = digitalRead(A1);

    if(leftSensor == HIGH && rightSensor == HIGH)
    {
        if(frontDistance>=15)
        {
            moveForeward();
        }
        
        else
        {
            checkSide();
        }
        
    }

    else if(leftSensor == LOW && rightSensor == HIGH)
    {
        moveLeft();
    }

    else if(leftSensor == HIGH && rightSensor == LOW)
    {
        moveRight();
    }

    else if(leftSensor == LOW && rightSensor == LOW)
    {
        moveStop();
    }
}

void moveRight()
{
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
}

void moveLeft()
{
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
}

void moveForeward()
{
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
}

void moveBackward()
{
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
}

void moveStop()
{
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
}

void servoFunction(int servo, int angle)
{
    digitalWrite(servo, HIGH);
    delayMicroseconds((angle*11)+500);   
    digitalWrite(servo, LOW);
    delay(50);
}

long ultrasonicRead()
{
    delay(10);
    digitalWrite(trig, LOW);
    delay(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    long time = pulseIn(echo, HIGH);
    long distance = time/29/2;
    return distance;
}

void checkSide()
{
    moveStop();
    delay(1000);

    for(int angle=70; angle<=140; angle+=5)
    {
        servoFunction(servo,angle);
    }
    delay(300);
    rightDistance = ultrasonicRead();

    for(int angle=140; angle>=0; angle = angle - 5)
    {
        servoFunction(servo,angle);
    }
    delay(300);
    leftDistance = ultrasonicRead();

    for(int angle=0; angle<=70; angle = angle + 5)
    {
        servoFunction(servo,angle);
    }
    delay(50);
    
     if(rightDistance>leftDistance)
    {
        moveRight();
        delay(500);
        moveForeward();
        delay(600);
        moveLeft();
        delay(500);
        moveForeward();
        delay(600);
        moveLeft();
        delay(500);
    }

    else
    {
        moveLeft();
        delay(500);
        moveForeward();
        delay(600);
        moveRight();
        delay(500);
        moveForeward();
        delay(600);
        moveRight();
        delay(500);
    }
}
