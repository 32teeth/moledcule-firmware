/*
 * @author Eugene Andruszczenko
 * @version 0.0.5
 * @date created 08/19/16
 * @date updated 09/14/16
 * @description
 */

 
#ifndef Comm_h
#define Comm_h
#include <Arduino.h>

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
    Comm();

    void start();
    void listen();

    /*
     *
     */
    ~Comm();

  private:    
};

#endif
