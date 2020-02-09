# ESC Calibration 

## Arduino

**PIN Connection**

- ESC1 to Arduino's digital pin #4
- ESC2 to Arduino's digital pin #5
- ESC3 to Arduino's digital pin #6
- ESC4 to Arduino's digital pin #7



**Usage**

 After having uploaded sketch on your Arduino and having ESCs **not powered up yet** :

1. Plug your Arduino to your computer with USB cable, open terminal, then type 1️⃣. This will send max throttle to each ESC in order to make them enter programming mode.
2. Power up your ESCs. You must hear "beep1 beep2 beep3" tones meaning the power supply is OK.
3. After 2sec, "beep beep" tone emits, meaning the throttle highest point has been correctly confirmed.
4. Then, type 0️⃣ to send 0 throttle. This will set the lowest throttle level for each ESC.
5. Several "beep" tones emits, wich means the quantity of the lithium battery cells (3 beeps for a 3 cells LiPo).
6. A long beep tone emits meaning the throttle lowest point has been correctly confirmed. Your ESC's are now well calibrated and ready for test.
7. Type 2️⃣ to launch test function. This will send 0 to max throttle to ESCs : you must see your motors starting to run with increasing speed, then stop when maximum speed is reached.



## STM32F103



**PIN Connection**

- ESC1 to STM32F103RB's digital pin PB9(TIM4->CCR4)
- ESC2 to STM32F103RB's digital pin PB0(TIM3->CCR3)
- ESC3 to STM32F103RB's digital pin PB1(TIM3->CCR4)
- ESC4 to STM32F103RB's digital pin PB8(TIM4->CCR3)



**Usage**

 After having uploaded sketch on your Arduino and having ESCs **not powered up yet** :

1. Plug your Arduino to your computer with USB cable, open terminal, then type 1️⃣. This will send max throttle to each ESC in order to make them enter programming mode.
2. Power up your ESCs. You must hear "beep1 beep2 beep3" tones meaning the power supply is OK.
3. After 2sec, "beep beep" tone emits, meaning the throttle highest point has been correctly confirmed.
4. Then, type 0️⃣ to send 0 throttle. This will set the lowest throttle level for each ESC.
5. Several "beep" tones emits, wich means the quantity of the lithium battery cells (3 beeps for a 3 cells LiPo).
6. A long beep tone emits meaning the throttle lowest point has been correctly confirmed. Your ESC's are now well calibrated and ready for test.
7. Type 2️⃣ to launch test function. This will send 0 to max throttle to ESCs : you must see your motors starting to run with increasing speed, then stop when maximum speed is reached.