/*
 * @class Comm
 * @description 
 */
class Comm
{
  public:

    /*
     *
     */
    Comm()
    {
      this->listen();   
    };

    void start()
    {
      Serial.begin(115200);
      while (!Serial) ;
      delay(1000);
    };
    void listen()
    {
      if(Serial.available() > 0)
      {
        String data = Serial.readStringUntil('\n');
        String message;
      }
    };

    /*
     *
     */
    ~Comm();

  private:    
};
