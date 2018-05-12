
# Stepper-Force-Feedback-Wheel

program to my Arduino mega2560 to read the PWM signal from the discovery board and control the stepper motor driver
to convert the PWM coming from the DISCOVERY board into a percentage of effect intensity,I'm reading the time that the signal stays on,
then the time it stays off so i can calculate the duty cycle in percentage, that will be used to control torque( or percentage of Amps
applied to the coils of the stepper), controlling this way the torque and the force of the direct drive effect.
The direction signal I will use to set direction and for the speed that the stepper will spin, I'll use a command proportional to the effect
level, so if the effect is around 100% the wheel gonna sping as fast as possible, and the opposite for lower intensity
