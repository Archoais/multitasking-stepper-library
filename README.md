# multitasking-stepper-library


**WARNING: Library Currently under construction!!**

An arduino library to control up to 6 steppers in a multitasking fashion (12 pins on the board, two per stepper). Different speeds, directions, number of steps and acceleration.

Theoretically number of steppers that can be controlled is only limited by the stack memory of the arduino and the number of addresses on the I2C bus, if each motor has a separate encoder which interfaces via I2C.

This means that over 30 motors can be controlled simultaneously with acceptable resposiveness.

<img src="images/Code.png" width="1000">
