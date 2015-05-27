#define BT_RX_PIN 2
#define BT_TX_PIN 1

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN);

#include "ElectricRayMotor.h"
#include "ElectricRayBluetoothControl.h"

ElectricRayMotor motor;
ElectricRayWirelessControl::command_t command;
ElectricRayBluetoothControl bluetooth;

  class ElectricRayRobot
  {
    public:
      ElectricRayRobot() { initialize(); }
      
      void initialize()
      {
        motor.leftDrive(0);
        motor.rightDrive(0);
      }
      
      void run()
      {
        bool haveRemoteCmd = bluetooth.getRemoteCommand(command);
        if (haveRemoteCmd)
        {
          motor.leftDrive(command.left);
          motor.rightDrive(command.right);
        }
      }
    
  };

ElectricRayRobot eray;

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop()
{
  eray.run();
}
