# Electric I8 BMW

  I took the chassis of an old toy car and modified it. After struggling with the old motors, I swaped them for more powerful ones and used bigger tires for better traction. The car is controlled via bluetooth from the phone with an application already existed in Google Play (5/5 stars from me!).
  The chosen application (see the end of this readme file) offers you: 8 directions to move, a range to control the power of the motors, 4 aditional button to set however you like + you can use the gyroscope of your phone to control the car.

## The controls are:

    * Move forwards
    * Move backwars
    * Turn left on the spot
    * Turn right on the spot
    * Turn left while moving forwards
    * Turn right while moving forwards
    * Turn left while moving backwards
    * Turn right while moving backwards
    * Flash the headlights(you know, it's an BMW...)
    * Control the speed of the car

## Features:

    * Automatic signals when you want to turn left/right
    * Stoplight turns on when you decelerate/stop/move backwards
    * Easu U-turn when you move backwards
    * Control the car using the gyroscope of the phone
    
## Downsides:

    * 9V batteries discharge way too fast. Should have used 1.5V batteries connected in series.
    * the car is pretty heavy so the top speed is not that high
    * front wheels were bad for turning so I used a ball pin
    
## Technical details

  I used 1 Arduino Uno board, 2 * 9V battery, Extension Board for breadboard,  small breadboard, 2 * (DC motor + tire), HC-05 Bluetooth module, L293D motor driver, Logic Converter 5V<->3.3V, couple of LEDs, resistors and bounch of wires.

## Special thanks to the people who organised this course and lab colleagues!

## For videos and photos:
   https://youtu.be/RX9mcECSF88</br>
   https://drive.google.com/open?id=1KKGjIKE5WfLOoxt4rLFbZZXR0RXPox6z</br>
   https://www.youtube.com/watch?v=iIFwz1cTYYE</br>

## Bibliography:
   * Link for application: https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en
   * Pins for motor driver: http://www.robotplatform.com/howto/L293/img_l/L293D_connections.jpg
