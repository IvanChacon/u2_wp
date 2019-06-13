#include <webots/robot.h>
 #include <webots/motor.h>
 #include <webots/keyboard.h>
 #include <webots/distance_sensor.h>

 #include <stdio.h>
 #include <math.h>
 /*
 enum {
  WB_KEYBOARD_END,
  WB_KEYBOARD_HOME,
  WB_KEYBOARD_LEFT,
  WB_KEYBOARD_UP,
  WB_KEYBOARD_RIGHT,
  WB_KEYBOARD_DOWN,
  WB_KEYBOARD_PAGEUP,
  WB_KEYBOARD_PAGEDOWN,
  WB_KEYBOARD_NUMPAD_HOME,
  WB_KEYBOARD_WB_KEYBOARD_PAGEDOWN,
  WB_KEYBOARD_NUMPAD_UP,
  WB_KEYBOARD_NUMPAD_RIGHT,
  WB_KEYBOARD_NUMPAD_DOWN,
  WB_KEYBOARD_NUMPAD_END,
  WB_KEYBOARD_KEY,
  WB_KEYBOARD_SHIFT,
  WB_KEYBOARD_CONTROL,
  WB_KEYBOARD_ALT
 };
  */

 /*
  * You may want to add macros here.
  */
 #define TIME_STEP 64

 /*
  * This is the main program.
  * The arguments of the main function can be specified by the
  * "controllerArgs" field of the Robot node
  */
 int main(int argc, char **argv)
 {
   /* necessary to initialize webots stuff */
   wb_robot_init();
   wb_keyboard_enable(TIME_STEP); //sample period for the keyboard, the same as
    wb_keyboard_enable(TIME_STEP); //sample period for the keyboard, the same as
                                // TIME_STEP, to use our real keyboard on wb
  int pressed_key;
  


   /*
    * You should declare here WbDeviceTag variables for storing
    * robot devices like this:
    *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
    *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
    */
    // Motor devices
    WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
    WbDeviceTag wheel_left = wb_robot_get_device("motor_left");

    wb_motor_set_position (wheel_right, INFINITY);
    wb_motor_set_position (wheel_left, INFINITY);

    // Distance sensor devices
    WbDeviceTag dist_sensor  = wb_robot_get_device("distance_sensor");

    wb_distance_sensor_enable (dist_sensor, TIME_STEP);

    double ds_value;

   /* main loop
    * Perform simulation steps of TIME_STEP milliseconds
    * and leave the loop when the simulation is over
    */
   while (wb_robot_step(TIME_STEP) != -1) {

     /*
      * Read the sensors :
      * Enter here functions to read sensor data, like:
      *  double val = wb_distance_sensor_get_value(my_sensor);
      */
      pressed_key= wb_keyboard_get_key();
     

      ds_value = wb_distance_sensor_get_value (dist_sensor);
      printf("Distance sensor: %lf\n", ds_value );


     /* Process sensor data here */

     /*
      * Enter here functions to send actuator commands, like:
      * wb_differential_wheels_set_speed(100.0,100.0);
      */

      if (pressed_key == WB_KEYBOARD_UP)
      {
        wb_motor_set_velocity (wheel_right, -6.28);
        wb_motor_set_velocity (wheel_left, -6.28);
        printf ("UP key pressed!\n");

      }

      else if (pressed_key == WB_KEYBOARD_DOWN)
      {
        wb_motor_set_velocity (wheel_right, 6.28);
        wb_motor_set_velocity (wheel_left, 6.28);
        printf ("DOWN key pressed!\n");
      }

      else if (pressed_key == WB_KEYBOARD_RIGHT)
      {
        wb_motor_set_velocity(wheel_right, 6.28);
        wb_motor_set_velocity(wheel_left, -6.28);
        printf ("LEFT key pressed!\n");
      }

      else if (pressed_key == WB_KEYBOARD_LEFT)
      {
        wb_motor_set_velocity(wheel_right, -6.28);
        wb_motor_set_velocity(wheel_left, 6.28);
        printf ("RIGHT key pressed!\n");
      }

      else
      {
        wb_motor_set_velocity (wheel_right, 0);
        wb_motor_set_velocity (wheel_left, 0);
      }
      //wb_motor_set_velocity(wheel_right, 6.283);
      //wb_motor_set_velocity(wheel_left, 6.283);

   };

   /* Enter your cleanup code here */

   /* This is necessary to cleanup webots resources */
   wb_robot_cleanup();

   return 0;
 }
