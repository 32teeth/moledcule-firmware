/*
** @method printIO
** @desc create string buffer and dump to serial
*/
void printIO()
{
  char buffer[250];
  (String)sprintf(
    buffer,
    "punhc:%d kick:%d alt:%d direction:%d",
    PUNCH.address,
    KICK.address,
    ALT.address,
    DIRECTION.address
  );

  print(buffer);
}

/*
** @method setPins
** @param io (Struct IO)
** @desc set pin, pin mode and write initial io state
*/
void setIO(IO& io)
{
  pinMode(io.pin, INPUT);
  digitalWrite(io.pin, io.state);
}

/*
** @method getPins
** @param io (Struct IO)
** @desc set io state
*/
void getIO(IO& io)
{
  io.state = digitalRead(io.pin);
}

/*
** @method readIO
** @desc itterate through structs and set appropriate structs
*/
void readIO()
{
  PUNCH.address = 0;
  for(byte n = 0; n < 4; n++)
  {
    getIO(PUNCHS[n]);
    PUNCHS[n].changed = PUNCH.states[n] != PUNCHS[n].state ? moledcule.now + duration : PUNCHS[n].changed;
    PUNCH.states[n] = PUNCHS[n].state;
    PUNCH.address |= PUNCH.states[n] == 0 ? 1 << n : 0 << n;
  }
  PUNCH.bin = getBin(PUNCH.address);
}
