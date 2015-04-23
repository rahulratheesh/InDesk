class Wireless {
  
  public:
    
    struct packet {
      String comm;
      String arg1;
      String arg2;
      
      packet() : comm(""), arg1(""), arg2("") {}
      
      void set(String command, String argument1, String argument2) {
        comm = command;
        arg1 = argument1;
        arg2 = argument2;
      }
      
    };
    
    Wireless() {}
    
    virtual bool getRemoteCommand(packet& pkt) = 0;
};
