#include "elev.h"
#include <stdio.h>
#include <unistd.h>
#include "func.h"

int i = 0;

int main() {
        // Initialize hardware
        if (!elev_init()) {
                printf("Unable to initialize elevator hardware!\n");
                return 1;
        }

        printf("Press STOP button to stop elevator and exit program.\n");

        elev_set_motor_direction(DIRN_UP);
        setMotorDir(1);
        init();

        while (1) {
                // Change direction when we reach top/bottom floor
                if (elev_get_floor_sensor_signal() != -1) {
                        setCurrentFloor(elev_get_floor_sensor_signal());
                        update();
                }
                if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
                        elev_set_motor_direction(DIRN_STOP);
                        setMotorDir(0);
                        doorOpenClose();
                        setPreviousFloor(4);
                        elev_set_motor_direction(DIRN_DOWN);
                        setMotorDir(-1);
                        sleep(1);
                } else if (elev_get_floor_sensor_signal() == 0) {
                        elev_set_motor_direction(DIRN_STOP);
                        setMotorDir(0);
                        sleep(3);
                        elev_set_motor_direction(DIRN_UP);
                        setMotorDir(1);
                        sleep(1);
                }

                // Stop elevator and exit program if the stop button is pressed
                emStop(elev_get_stop_signal());
        }

        return 0;
}
