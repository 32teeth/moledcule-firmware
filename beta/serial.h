/*
** @method listen
** @desc listen to serial port if DEBUG is defined
*/
void listen()
{
  #ifdef DEBUG
    if(Serial.available() > 0)
    {
      String data = Serial.readStringUntil('\n');
      String message;
    }
  #endif
};

/*
** @method print
** @param str (String)
** @desc print string to serial port if DEBUG is defined
*/
void print(String str)
{
  #ifdef DEBUG
    delay(5);
    Serial.println(str);
    Serial.flush();
  #endif
};
