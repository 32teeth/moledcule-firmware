/*
 * @author Eugene Andruszczenko
 * @version 0.1
 * @date created 03/08/17
 * @date updated 03/08/17
 * @web http://moledcule.club
 */

/*
 * @description pin mapping
 */

#if SYSTEM == KAIMANA
  #define PIN_P1 3
  #define PIN_P2 2
  #define PIN_P3 0
  #define PIN_P4 1

  #define PIN_K1 4
  #define PIN_K2 A3
  #define PIN_K3 12
  #define PIN_K4 6

  #define PIN_START 10
  #define PIN_SELECT 9
  #define PIN_HOME 8

  #define PIN_RIGHT A2
  #define PIN_DOWN 11
  #define PIN_LEFT A1
  #define PIN_UP A0
#endif
#if SYSTEM == MOLEDCULE
  #define PIN_P1 13
  #define PIN_P2 9
  #define PIN_P3 10
  #define PIN_P4 8

  #define PIN_K1 6
  #define PIN_K2 12
  #define PIN_K3 4
  #define PIN_K4 2

  #define PIN_START 5
  #define PIN_SELECT A0
  #define PIN_HOME A1

  #define PIN_RIGHT A2
  #define PIN_DOWN A5
  #define PIN_LEFT A3
  #define PIN_UP A4
#endif
