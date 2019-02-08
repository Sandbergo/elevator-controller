// Wrapper for libComedi Elevator control.
// These functions provides an interface to the elevators in the real time lab
//
// 2007, Martin Korsgaard
#ifndef __INCLUDE_DRIVER_H__
#define __INCLUDE_DRIVER_H__


// Number of floors
#define N_FLOORS 4

//Number of buttons
#define N_BUTTONS 3




/**
   Initialize elevator.
   @return Non-zero on success, 0 on failure.
 */
int elev_init(void);



/**
   Motor direction for function elev_set_motor_direction().
 */
typedef enum tag_elev_motor_direction {
        DIRN_DOWN = -1,
        DIRN_STOP = 0,
        DIRN_UP = 1
} elev_motor_direction_t;



/**
   Sets the motor direction of the elevator.
   @param dirn New direction of the elevator.
 */
void elev_set_motor_direction(elev_motor_direction_t dirn);



/**
   Turn door-open lamp on or off.
   @param value Non-zero value turns lamp on, 0 turns lamp off.
 */
void elev_set_door_open_lamp(int value);



/**
   Get signal from obstruction switch.
   @return 1 if obstruction is enabled. 0 if not.
 */
int elev_get_obstruction_signal(void);



/**
   Get signal from stop button.
   @return 1 if stop button is pushed, 0 if not.
 */
int elev_get_stop_signal(void);



/**
   Turn stop lamp on or off.
   @param value Non-zero value turns lamp on, 0 turns lamp off.
 */
void elev_set_stop_lamp(int value);



/**
   Get floor sensor signal.
   @return -1 if elevator is not on a floor. 0-3 if elevator is on floor. 0 is
    ground floor, 3 is top floor.
 */
int elev_get_floor_sensor_signal(void);



/**
   Set floor indicator lamp for a given floor.
   @param floor Which floor lamp to turn on. Other floor lamps are turned off.
 */
void elev_set_floor_indicator(int floor);



/**
   Button types for function elev_set_button_lamp() and elev_get_button().
 */
typedef enum tag_elev_lamp_type {
        BUTTON_CALL_UP = 0,
        BUTTON_CALL_DOWN = 1,
        BUTTON_COMMAND = 2
} elev_button_type_t;



/**
   Gets a button signal.
   @param button Which button type to check. Can be BUTTON_CALL_UP,
    BUTTON_CALL_DOWN or BUTTON_COMMAND (button "inside the elevator).
   @param floor Which floor to check button. Must be 0-3.
   @return 0 if button is not pushed. 1 if button is pushed.
 */
int elev_get_button_signal(elev_button_type_t button, int floor);



/**
   Set a button lamp.
   @param lamp Which type of lamp to set. Can be BUTTON_CALL_UP,
    BUTTON_CALL_DOWN or BUTTON_COMMAND (button "inside" the elevator).
   @param floor Floor of lamp to set. Must be 0-3
   @param value Non-zero value turns lamp on, 0 turns lamp off.
 */
void elev_set_button_lamp(elev_button_type_t button, int floor, int value);



#endif // #ifndef __INCLUDE_DRIVER_H__
