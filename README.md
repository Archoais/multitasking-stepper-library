# multitasking-stepper-library


Currently under construction!

An arduino library to control up to 6 steppers in a multitasking fashion, due to pin limitations in one board. Different speeds, directions, number of steps and acceleration.

Theoretically number of steppers that can be controlled is limited by the stack memory of the arduino, if each motor has a separate encoder which interfaces via I2C.
