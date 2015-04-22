class Wireless {
  
  public:
    
    struct packet {
      String comm;
      String arg1;
      String arg2;
      
      packet() : comm(""), arg1(""), arg2("") {}
      
      void set(String type, String note, String beat) {
        comm = type;
        arg1 = note;
        arg2 = beat;
      }
      
    };
    
    Wireless() {}
    
    virtual bool getRemoteCommand(packet& cmd) = 0;
};
