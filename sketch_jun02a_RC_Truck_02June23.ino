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
uint8_t RemoteXY_CONF[] =   // 67 bytes
  { 255,5,0,0,0,60,0,16,31,1,1,0,24,17,12,12,2,31,70,0,
  1,0,4,39,12,12,2,31,76,0,1,0,41,40,12,12,2,31,82,0,
  1,0,23,56,12,12,2,31,66,0,2,0,18,79,22,11,2,26,31,31,
  79,78,0,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_Forward; // =1 if button pressed, else =0 
  uint8_t button_Left; // =1 if button pressed, else =0 
  uint8_t button_Right; // =1 if button pressed, else =0 
  uint8_t button_Backward; // =1 if button pressed, else =0 
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

/* Servo Library */
#include <Servo.h>

uint8_t BT_input_F = 0;
uint8_t BT_input_B = 0;
uint8_t BT_input_R = 0;
uint8_t BT_input_L = 0;

/* to store input character received via BT.*/

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
int pos1 = 60; // steering


void setup()  
{
  RemoteXY_Init (); 
  pinMode(motorPin1, OUTPUT); // H-Bridge pin1
  pinMode(motorPin2, OUTPUT); // H-Bridge pin1
  pinMode(buzz, OUTPUT);  // pin 13 buzzer
  pinMode(fled, OUTPUT);  // pin A0 Front led
  pinMode(bled, OUTPUT);  // pin A1 back led
  steer_serv.attach(2); // Servo pin    
  steer_serv.write(pos1); // intial position
}
void loop() 
{
    RemoteXY_Handler ();
    if (RemoteXY.switch_1==1)
  {
     BT_input_F=RemoteXY.button_Forward;
     BT_input_B=RemoteXY.button_Backward;
     BT_input_L=RemoteXY.button_Left;
     BT_input_R=RemoteXY.button_Right;

    if (BT_input_F==0 && BT_input_B==0 && BT_input_L==0 && BT_input_R==0) // Stop case
    {
      digitalWrite(motorPin1, LOW);   
      digitalWrite(motorPin2, LOW);   
      digitalWrite(fled, LOW);          //front led off
      digitalWrite(bled, LOW);          //back led off
    }
   else if (BT_input_B==1 && BT_input_F==0) // Move backward case
    {
      analogWrite(motorPin1, 255); 
      digitalWrite(motorPin2, LOW); 
      digitalWrite(bled, HIGH);          //back led on
    }
    else if (BT_input_F==1 && BT_input_B==0) // Move forward  case
    {
      digitalWrite(motorPin1, LOW); 
      analogWrite(motorPin2, 255);
      digitalWrite(fled, HIGH);          //front led on      
    }
   
   //  Servo from 50 to 140 degree
   else if (BT_input_R==1)   
    {
      while(BT_input_R==1 && pos1<80)
      {       
      pos1++;  //increases the value of the "pos" variable each time the push button of the left is pressed         
      delay(40); //20 milliseconds of delay        
      steer_serv.write(pos1); //servo goes to variable pos
        }
      }   
    else if (BT_input_L==1)   
    {
    while(BT_input_L==1 && pos1>50 )
    {     
    pos1--;  //increases the value of the "pos" variable each time the push button of the left is pressed          
    delay(40); //5 milliseconds of delay 
    steer_serv.write(pos1); //servo goes to variable pos
       }
      }
    }
  }
