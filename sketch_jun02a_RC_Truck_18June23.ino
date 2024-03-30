//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 50 bytes
  { 255,4,0,0,0,43,0,16,31,1,1,0,24,17,12,12,2,31,70,0,
  1,0,3,39,12,12,2,31,76,0,1,0,44,39,12,12,2,31,82,0,
  1,0,23,61,12,12,2,31,66,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_Forward; // =1 if button pressed, else =0 
  uint8_t button_Left; // =1 if button pressed, else =0 
  uint8_t button_Right; // =1 if button pressed, else =0 
  uint8_t button_Backward; // =1 if button pressed, else =0 
  //uint8_t button_Centre; // =1 if button pressed, else =0
  //int8_t slider_1; // =0..100 slider position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

/* Servo Library */
#include <Servo.h>

int angle =60;    // initial angle  for servo
int angleStep =5;

//int ms = RemoteXY.slider_1*20+500;

// H-Bridge pins//
int motorPin1 = 5;               // pin 1 on H-bridge
int motorPin2 = 6;               // pin 2 on H-bridge

// Buzzer and LEDs//
int buzz = 13;               // pin 13 buzzer
int fled = A5;               // pin A0 Front led
int bled = A4;               // pin A1 back led


// Servo object//
Servo steer_serv; // steering

// Servo intial position//
//int pos1 = 60; // steering

void setup()  
{
  RemoteXY_Init (); 
  pinMode(motorPin1, OUTPUT); // H-Bridge pin1
  pinMode(motorPin2, OUTPUT); // H-Bridge pin1
  pinMode(buzz, OUTPUT);  // pin 13 buzzer
  pinMode(fled, OUTPUT);  // pin A0 Front led
  pinMode(bled, OUTPUT);  // pin A1 back led
  steer_serv.attach(2); // Servo pin    
  //steer_serv.write(pos1); // intial position
  steer_serv.write(angle); // intial position
  //RemoteXY.slider_1 = 50; 
}
void loop() 
{
    
    RemoteXY_Handler ();
    //int ms = RemoteXY.slider_1*20+500; 
    //steer_serv.writeMicroseconds(ms);
    /*
    if (RemoteXY.button_Forward==0 && RemoteXY.button_Backward==0 && RemoteXY.button_Right==0 && RemoteXY.button_Left==0) // Stop case
    {
      digitalWrite(motorPin1, LOW);   
      digitalWrite(motorPin2, LOW);   
      digitalWrite(fled, LOW);          //front led off
      digitalWrite(bled, LOW);          //back led off
    }
   else if (RemoteXY.button_Backward==1 && RemoteXY.button_Forward==0 && RemoteXY.button_Right==0 && RemoteXY.button_Left==0 ) // Move backward case
    {
      analogWrite(motorPin1, 255); 
      digitalWrite(motorPin2, LOW); 
      digitalWrite(bled, HIGH);          //back led on
    }
    else if (RemoteXY.button_Forward==1 && RemoteXY.button_Backward==0 && RemoteXY.button_Right==0 && RemoteXY.button_Left==0) // Move forward  case
    {
      digitalWrite(motorPin1, LOW); 
      analogWrite(motorPin2, 255);
      digitalWrite(fled, HIGH);          //front led on    
    }
   */
   //  Servo from 50 to 140 degree
   
   if (RemoteXY.button_Left==1 && RemoteXY.button_Right==0) // move Left case   
    {
      while(RemoteXY.button_Left==1 && RemoteXY.button_Right==0)
      {       
      if (angle > 0 && angle <= 100)
      {
        angle = angle - angleStep;
       if(angle < 0)
       {
       angle = 0;
       }
       else
       {
      steer_serv.write(angle); // move the servo to desired angle
        }
        }
       //delay(100); // waits for the servo to get there
      }
    }
    else if (RemoteXY.button_Right==1 && RemoteXY.button_Left==0)   
    {
    while(RemoteXY.button_Right==1 && RemoteXY.button_Left==0)
    {
      if (angle >= 0 && angle <= 100)
      {
        angle = angle + angleStep;
       if(angle > 100)
       {
       angle = 100;
       }
       else
       {
      steer_serv.write(angle); // move the servo to desired angle
        }     
    }
       //delay(100); // waits for the servo to get there

       }
      }
      
  }
