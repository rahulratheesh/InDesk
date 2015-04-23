#include "wireless.h"

class Bluetooth : public Wireless {
  
  public:
  
    Bluetooth() : Wireless() {
    }
    
    void init() {
      BTSerial.begin(38400);
      // set the bluetooth work in slave mode
      BTSerial.print("\r\n+STWMOD=0\r\n");
      // set the bluetooth name as "SeeedBTSlave"
      BTSerial.print("\r\n+STNA=SeeedBTSlave\r\n");
      // Permit Paired device to connect me
      BTSerial.print("\r\n+STOAUT=1\r\n"); 
      // Auto-connection should be forbidden
      BTSerial.print("\r\n+STAUTO=0\r\n"); 
      // This delay is required.
      delay(2000); 
      // make the slave bluetooth inquirable
      BTSerial.print("\r\n+INQ=1\r\n"); 
      Serial.println("The slave bluetooth is inquirable!");
      // This delay is required.
      delay(2000); 
      BTSerial.flush(); 
    }
    
    virtual bool getRemoteCommand(packet& pkt) {
      
      // no commands available
      if (BTSerial.available() <= 0)
          return false;
          
      command = BTSerial.readStringUntil('\n');
      //Serial.println(command);
      
      int spaceIndex = command.indexOf(" ");
      String type = command.substring(0, spaceIndex);
      String arguments = command.substring(spaceIndex + 1);
      spaceIndex = arguments.indexOf(" ");
      String arg1 = arguments.substring(0, spaceIndex);
      String arg2 = arguments.substring(spaceIndex + 1);
      Serial.println(type + " " + arg1 + " " + arg2);
      pkt.set(type, arg1, arg2);
       
    }
    
    
  private:
      
      String command;
     
};


