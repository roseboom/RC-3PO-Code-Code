//The Most Superior Code to All Others:
#define SENSEPIN1 0
#define SENSEPIN2 1
#define SENSEPIN3 2
#define MOTORSPEED1 128
#define MOTORSPEED2 128
#define ANGLESENSE1 45 //PROBABLY IN RADIANS
#define ANGLESENSE2 30 //Probably in Radians


//------------------------------------------------------------------------------------------
void Forward(); //Moves Bot forward
void Backward(); //Moves bot backwards
void PivotRight(); //Pivots bot right
void PivotLeft(); //Pivots bot left
int Sensing(); //Used for sensing walls and objects, sensors must be mounted within a cm of eachother. and Norm must be set.
void Reflection(); //Used for tracking the line
void Backout(); //Used for when a obstacle is sensed
void EndGame(); //Used for scoring the goals

//Outputs

//------------------------------------------------------------------------------------------
void setup() { 
Serial.begin(9600);
Serial.println("Let's Begin");
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11, OUTPUT); //PWM
  pinMode(9, OUTPUT); //PWM
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
 


};

//----------------------------------------------------------------------------------------
int Sensing ()
{float RangeA1, VoltageA1;
float RangeA2, VoltageA2;
float RangeA3, VoltageA3;
float AvgA;
float RangeB1, VoltageB1;
float RangeB2, VoltageB2;
float RangeB3, VoltageB3;
float AvgB;
float RangeC1, VoltageC1;
float RangeC2, VoltageC2;
float RangeC3, VoltageC3;
float AvgC;
int FLAG1;
int horizDistA;
int horizDistB;
int Diff;
int norm;   //URGENT NEED TO SET VALUE

float DifferenceAB;
float DifferenceBC;
float DifferenceAC;

//First Sensor Average
VoltageA1 = analogRead(A0); //I Read the input value from the sensor
RangeA1 = (6787/(VoltageA1 -3))-4;    //Conversion from the infra red to the Range
VoltageA2 = analogRead(A0); //I Read the input value from the sensor
RangeA2 = (6787/(VoltageA2 -3))-4;    //Conversion from the infra red to the Range
VoltageA3 = analogRead(A0); //I Read the input value from the sensor
RangeA3 = (6787/(VoltageA3 -3))-4;    //Conversion from the infra red to the Range
AvgA = (RangeA1 + RangeA2 + RangeA3);
Serial.print("Range of Sensor 1 is ");
Serial.println(AvgA);

//Second Sensor Average
VoltageB1 = analogRead(A1); //I Read the input value from the sensor
RangeB1 = (6787/(VoltageB1 -3))-4;    //Conversion from the infra red to the Range
VoltageB2 = analogRead(A1); //I Read the input value from the sensor
RangeB2 = (6787/(VoltageB2 -3))-4;    //Conversion from the infra red to the Range
VoltageB3 = analogRead(A1); //I Read the input value from the sensor
RangeB3 = (6787/(VoltageB3 -3))-4;    //Conversion from the infra red to the Range
AvgB = (RangeB1 + RangeB2 + RangeB3);
Serial.print("Range of Sensor 2 is ");
Serial.println(AvgB);
//Calcs
horizDistA = AvgA * sin(ANGLESENSE1);
horizDistB = AvgB * sin(ANGLESENSE2);
Diff = horizDistA - horizDistB;
if (Diff == 0){
Serial.println("A Wall has appeared");
FLAG1 = 2;
}
else if(Diff == norm)
Serial.println("No Problems ahead Captain");
else 
{Serial.println("We must see an obstacle");
Backout();
FLAG1 = 1;
};





return FLAG1;
}

//---------------------------------------------------------------------------------------------
void Reflection()
{  int reflect1;
  int reflect2;
  int reflect3;
  int a;
  reflect1 = digitalRead(SENSEPIN1); //This reads the output from the sensor to determine reflectiveness //Left
  reflect2 = digitalRead(SENSEPIN2);//Center
  reflect3 = digitalRead(SENSEPIN3);//Right
  if(reflect1 ==1 && reflect2 == 1 && reflect3 ==1 )
        {
          PivotLeft();
           delay(1000); // Turns 90 degrees
           for(a = 0; reflect1 + reflect2+ reflect3>0; a++)
           {
              for(a =0; reflect2 == 1; a++)
              {
               //Following Forward
                reflect1 = digitalRead(SENSEPIN1); //This reads the output from the sensor to determine reflectiveness //Left
                reflect2 = digitalRead(SENSEPIN2);//Center
                reflect3 = digitalRead(SENSEPIN3);//Right
               //Left
                analogWrite(11, MOTORSPEED1);
                digitalWrite(12,HIGH);
                digitalWrite(13,LOW );

              //Right
                analogWrite(9, MOTORSPEED1);
                digitalWrite(7, HIGH);
                digitalWrite(8, LOW);
                                    }
            if(reflect1 == 1)
            {PivotLeft();
            delay(200); //45 degree turn}
            if (reflect3 == 1)
            {PivotRight();
            delay(200); //45 Degree Turn
            }
            }
           }
           analogWrite(11,0);
           analogWrite(9,0); 
            
  
}
}


//--------------------------------------------------------------------------------------------------
void Forward()
{ int a;
int Time = 150000;
int FLAGF = 0;

for(a=0; FLAGF == 0 && millis()<Time ; a++)
{
  //Left
  analogWrite(11, MOTORSPEED1);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW );

  //Right
  analogWrite(9, MOTORSPEED1);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);

  //Sensor
  FLAGF = Sensing();
  
}
if (FLAGF == 1)
Backout();
}


//---------------------------------------------------------------------------------
void Backward()
{
  //Left
  analogWrite(11, MOTORSPEED1);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH );

  //Right
  analogWrite(9, MOTORSPEED1);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  delay(3000);
}

//--------------------------------------------------------------------------------------
void PivotLeft()
{
    //Left
  analogWrite(11, MOTORSPEED1);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH );

  //Right
  analogWrite(9, MOTORSPEED1);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

//----------------------------------------------------------------------------------------
void PivotRight()
{
  
    //Left
  analogWrite(11, MOTORSPEED1);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW );

  //Right
  analogWrite(9, MOTORSPEED1);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);

}

//-----------------------------------------------------------------------------------------
void Backout()
{ Backward();
PivotLeft();
delay(1000); // 90 degree turn
};

//-----------------------------------------------------------------------------------------
void EndGame()
{ int a;
int reflectA = 0;
int reflectB = 0;
int reflectC = 0;
int FLAGF;

Forward();
  PivotRight();
  delay(1000); //90 degree turn
  for(a=0; reflectA +reflectB + reflectC <1 && FLAGF ==0 ; a++)
{reflectA = digitalRead(SENSEPIN1);
reflectB = digitalRead(SENSEPIN2);
reflectC = digitalRead(SENSEPIN3);

  //Left
  analogWrite(11, MOTORSPEED1);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW );

  //Right
  analogWrite(9, MOTORSPEED1);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);

  //Sensor
  FLAGF = Sensing();
  
}
  Reflection();
};
//-----------------------------------------------------------------------------------------
void loop() 
{int b;
  for(b=0; millis()>150000; b++)
  {
    Forward();
    PivotLeft();
    delay(1200); //135 degree turn
    Forward();
    PivotLeft();
    delay(1000); // 90 degree angle
    Forward();
    PivotLeft(); // 135 Degrees
    delay(1000);
  }

EndGame();
}
