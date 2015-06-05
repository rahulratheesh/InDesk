#include "wireless.h"
extern QueueList <String> queue;

class Bluetooth : public Wireless {
  
  public:
  
    Bluetooth() : Wireless() {
    }
        
    virtual bool getRemoteCommand(packet& pkt) {
      
      // no commands available
      if (BTSerial.available() <= 0)
          return false;
          
      command = BTSerial.readStringUntil('\n');
//      Serial.println(command);

      queue.push(command);
      
      int spaceIndex = command.indexOf(" ");
      String type = command.substring(0, spaceIndex);
      String arguments = command.substring(spaceIndex + 1);
      spaceIndex = arguments.indexOf(" ");
      String arg1 = arguments.substring(0, spaceIndex);
      String arg2 = arguments.substring(spaceIndex + 1);
//      Serial.println(type + " " + arg1 + " " + arg2);
      pkt.set(type, arg1, arg2);
      
      return true;
       
    }
    
    
  private:
      
      String command;
     
};


