# RC Sumo Robot

An Arduino-based remote-controlled sumo robot project utilizing a PS2 controller for real-time motion control and mode switching.

## Overview

The RC Sumo Robot is designed to compete in sumo robot wrestling by pushing an opponent out of a ring. It uses a PS2 controller for intuitive operation, allowing the driver to control the robot’s movement via analog joysticks and adjust speed or switch driving modes on the fly.

## Features

- **PS2 Controller Interface:** 
  - Uses the [PS2X_lib](https://github.com/madsci1016/Arduino-PS2X) for integrating the PS2 gamepad.
  - Supports button-based mode switching and analog stick control.
  
- **Multiple Driving Modes:**
  - **Mode 1 (Default):** Joystick-based control for forward, reverse, left, and right movement.
  - **Modes 2–4:** (Currently commented out) Additional behaviors for independent motor control and custom maneuvers.

- **Dynamic Speed Control:**
  - Adjust motor speed using the L1, L2, R1, and R2 buttons on the PS2 controller.
  
- **Motor Control:**
  - Four motor control functions (`forward()`, `back()`, `left()`, `right()`, and `stopp()`) drive the robot based on input.

## Hardware Requirements

- **Microcontroller:** Arduino Uno (or compatible)
- **Motor Driver:** Dual H-bridge (e.g., L298N)
- **Motors:** Two or four DC motors (depending on your chassis design)
- **PS2 Controller and Dongle:**
  - PS2 controller
  - PS2 dongle (with connections: PS2_DAT, PS2_CMD, PS2_SEL, PS2_CLK)
- **Chassis:** Suitable robot chassis with wheels
- **Power Supply:** Battery pack with appropriate voltage/current ratings
- **Miscellaneous:** Wiring, connectors, resistors (if needed), and mounting hardware

## Wiring Overview

- **Motor Connections (to Arduino digital pins):**
  - `INA1` (Pin 3), `INA2` (Pin 9)
  - `INB1` (Pin 5), `INB2` (Pin 6)
  
- **PS2 Controller Connections:**
  - `PS2_DAT` on Pin 11
  - `PS2_CMD` on Pin 12
  - `PS2_SEL` on Pin 10
  - `PS2_CLK` on Pin 13

*(Ensure that the wiring between the motor driver, motors, and PS2 dongle is secure and matches your hardware setup.)*

## Software Setup

1. **Install the Arduino IDE:**  
   Download and install from [arduino.cc](https://www.arduino.cc/).

2. **Install Required Libraries:**  
   - [PS2X_lib](https://github.com/madsci1016/Arduino-PS2X) for PS2 controller integration.
   
3. **Upload the Code:**  
   - Connect your Arduino to the computer.
   - Open the provided code in the Arduino IDE.
   - Compile and upload the sketch.

## Code Structure

- **Global Definitions & Setup:**  
  - Defines motor pins and PS2 dongle pins.
  - Initializes the PS2 controller and sets up motor pins.
  
- **Motor Functions:**  
  - `forward()`, `back()`, `left()`, `right()`, and `stopp()` encapsulate basic movement commands.
  
- **Main Loop:**  
  - Reads the PS2 controller inputs (analog sticks and buttons).
  - Adjusts speed and allows mode switching via PS2 buttons:
    - **Square:** Switch to Mode 2
    - **Circle:** Switch to Mode 3
    - **Cross:** Switch to Mode 4
    - **Triangle:** Return to Mode 1 (default)
  - Implements joystick-based motor control (active in Mode 1).

*Note: Modes 2, 3, and 4 are currently commented out but can be activated and customized for independent motor control or other behaviors.*

## How to Operate

1. **Power Up:**  
   Assemble your robot and power the Arduino along with the motor driver and PS2 dongle.
   
2. **Control with the PS2 Controller:**  
   - **Joystick Movement:**  
     - Push the left joystick forward (LY < 128) to move forward.
     - Pull it back (LY > 128) to reverse.
     - Move the right joystick to adjust turning.
   - **Speed Adjustment:**  
     - Press **L1** to set speed to a default value.
     - **L2** to decrease speed, **R2** to increase speed, and **R1** to stop.
   - **Mode Switching:**  
     - Use **Square**, **Circle**, **Cross**, and **Triangle** buttons to switch between modes.
   
3. **Test and Calibrate:**  
   - Run initial tests in a controlled area.
   - Adjust speed parameters or joystick thresholds in the code if needed.

## Troubleshooting

- **Controller Not Recognized:**  
  - Check wiring connections between the PS2 dongle and Arduino.
  - Ensure the correct library version of PS2X_lib is installed.
  
- **Unexpected Movement:**  
  - Verify motor wiring and ensure correct pin assignments.
  - Use the serial monitor to review the debug output for mode switching and speed adjustments.
  
- **Mode Switching Issues:**  
  - Debounce delays are implemented; if switching feels unresponsive, consider adjusting the delay times.

## Credits

- **Developed by:** [Dave Matthew | DMVexious on Github]
- **Based on:** PS2 controller integration projects and sumo robot challenges.
- **Contributions:** Feel free to fork and improve the project.

---

Happy building, and may your robot dominate the sumo ring!
