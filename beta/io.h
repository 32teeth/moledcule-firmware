/*
 * @author Eugene Andruszczenko
 * @version 0.1
 * @date created 03/08/17
 * @date updated 03/08/17
 * @web http://moledcule.club
 */

/*
 * @description all punch IO
 */
//typedef struct{byte pin;byte state;byte index;long changed;} IO;
IO P1 = {PIN_P1, 1, INDEX_P1, 0};
IO P2 = {PIN_P2, 1, INDEX_P2, 0};
IO P3 = {PIN_P3, 1, INDEX_P3, 0};
IO P4 = {PIN_P4, 1, INDEX_P4, 0};

/*
 * @description all kick IO
 */
IO K1 = {PIN_K1, 1, INDEX_K1, 0};
IO K2 = {PIN_K2, 1, INDEX_K2, 0};
IO K3 = {PIN_K3, 1, INDEX_K3, 0};
IO K4 = {PIN_K4, 1, INDEX_K4, 0};

/*
 * @description all alt IO
 */
IO START = {PIN_START, 1, INDEX_START, 0};
IO SELECT = {PIN_SELECT, 1, INDEX_SELECT, 0};
IO HOME = {PIN_HOME, 1, INDEX_HOME, 0};
