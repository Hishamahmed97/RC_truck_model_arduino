//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

/* Servo Library */
#include <Servo.h>

#include <RemoteXY.h>

* Create bluetooth object of Tx and RX of Bluetooth module */
SoftwareSerial BlueTooth(0,1);    // (TXD, RXD) of HC-05
char BT_input;                    // to store input character received via BT

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2 // should be zero or one
#define REMOTEXY_SERIAL_TX 3 // should be zero or one
#define REMOTEXY_SERIAL_SPEED 9600



// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 32 bytes
  { 255,1,0,0,0,25,0,16,31,1,10,48,9,10,15,15,4,26,31,70,
  79,82,87,65,82,68,0,31,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t pushSwitch_1; // =1 if state is ON, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 
  
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  
  if (RemoteXY.pushSwitch_1==1)
  {
    ser
  }
  // do not call delay() 


}
