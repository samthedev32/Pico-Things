#include "servo.h"

int main()
{
    // Init Servo
    servo_init(6);

    // Setup Servo Max "Speed" (or POS)
    servo_setMillis(6, 2000);
    sleep_ms(2000);

    // Set Servo Min "Speed" (or POS)
    servo_setMillis(6, 1000);
    sleep_ms(2000);

    while (1)
    {
        // Move Servo to 0 Degrees
        servo_setMillis(6, 1000);
        sleep_ms(2000);

        // Move Servo to 90 Degrees
        servo_setMillis(6, 1500);
        sleep_ms(2000);

        // Move Servo to WHAT DA HAIL? ISN'T IT ONLY 180 DEGREES?!?!?!?
        servo_setMillis(6, 5000);
        sleep_ms(2000);
    }
    return 0;
}