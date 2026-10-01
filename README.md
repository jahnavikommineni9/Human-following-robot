# Human-Following Robot Using Arduino

An Arduino-based robotics project that demonstrates a robot moving toward and following a person using distance sensors and motor control. This repository provides a starter implementation for a two-wheel robot using an Arduino-compatible board, ultrasonic sensors, and a motor driver.

## Project background

If accurate for your project, you can use this wording:

"I developed this project during my second year of B.Tech as part of my learning in robotics, embedded systems, and automation. I am uploading it to GitHub now to document my earlier work and showcase my practical experience."

Update this section if your actual project timeline or hardware differs.

## Features

- Reads distance from front-facing ultrasonic sensors
- Drives two DC motors through an L298N-compatible motor driver
- Moves forward when an object/person is within a configured following range
- Stops when the target is too close or no target is detected
- Uses a simple differential-drive movement model
- Includes adjustable distance thresholds and wiring notes

> **Important limitation:** This starter follows nearby objects based on distance readings. It does not identify a specific human or distinguish a person from other objects. For person-specific following, add a camera and a person-detection model, or another suitable tracking sensor.

## Hardware requirements

- Arduino Uno or compatible board
- 2 HC-SR04 ultrasonic distance sensors (left and right)
- L298N motor driver (or compatible dual H-bridge)
- 2 DC geared motors and robot chassis
- Suitable battery pack for motors and electronics
- Jumper wires and common ground

## Example wiring

These are example pin assignments for an Arduino Uno. Change them to match your actual circuit.

| Component | Arduino pin |
|---|---|
| Left ultrasonic TRIG | D2 |
| Left ultrasonic ECHO | D3 |
| Right ultrasonic TRIG | D4 |
| Right ultrasonic ECHO | D5 |
| Motor driver ENA | D6 (PWM) |
| Motor driver IN1 | D7 |
| Motor driver IN2 | D8 |
| Motor driver IN3 | D9 |
| Motor driver IN4 | D10 |
| Motor driver ENB | D11 (PWM) |

Connect the motor driver's logic GND, Arduino GND, and sensor GND together. Power the motors from a suitable motor supply, not from the Arduino 5 V pin. Follow the driver board's voltage and current limits.

## Software requirements

- Arduino IDE
- Arduino Uno board support (included with the standard Arduino IDE)
- No additional library required for this example

## How it works

1. The two ultrasonic sensors measure the distance in front of the robot on the left and right.
2. If both readings indicate that a target is within the following range, the robot moves forward.
3. If the left and right readings differ significantly, the robot turns toward the side with the nearer reading.
4. If the target is too close or too far away, the robot stops.
5. The measured distances and movement decision are printed to Serial Monitor for debugging.

The distance-based steering is a simple demonstration and may need tuning for your sensor placement, room layout, and motor characteristics.

## Upload and test

1. Open `src/Human_Following_Robot.ino` in Arduino IDE.
2. Select **Arduino Uno** (or your compatible board) and the correct port.
3. Check the wiring against the table above.
4. Upload the sketch.
5. Place a large object or person in front of the robot at a safe distance.
6. Open Serial Monitor at **9600 baud** to view sensor readings and movement decisions.
7. Test at low motor speed first, with the robot wheels lifted off the ground during initial motor checks.

## Results and output

The Serial Monitor reports the left and right distance measurements and the robot's current action (forward, turning, or stopped). Add actual photographs of your assembled robot and screenshots of your test output to the `docs/` folder.

Example Markdown to display your own images:

```markdown
![Human-following robot prototype](docs/robot-prototype.jpg)
![Serial Monitor output](docs/serial-monitor.png)
```

No result photos are included in this starter because they should represent your actual hardware and test results.

## Safety notes

- Test on a clear, flat surface and keep fingers, hair, clothing, and cables away from wheels and gears.
- Use a suitable motor battery and check polarity before powering the circuit.
- Stop testing if motors, driver, wiring, or battery become hot.
- This is an educational prototype and should not be used for safety-critical navigation.

## Future improvements

- Add a camera and person-detection model to distinguish people from other objects.
- Use a pan/tilt mechanism or tracking sensor to improve target direction estimation.
- Add speed control based on distance and smoother turning.
- Add a battery monitor and emergency stop.
- Record test results for different distances and lighting/room conditions.

## GitHub upload

Create a repository named `Human-Following-Robot` with **Add README turned off**, because this project already contains a README. Extract this ZIP, open a terminal in the extracted project folder, and run:

```bash
git init
git add .
git commit -m "Add Arduino human-following robot project"
git branch -M main
git remote add origin https://github.com/YOUR-USERNAME/Human-Following-Robot.git
git push -u origin main
```
