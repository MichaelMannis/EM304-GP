##### motor\_Controller library



**Object constructor:**

\-motor servo\_name(pca\_channel\_number), ex: "motor servo1(0)".



\-motor stepper\_name(pin1, pin2, pin3, pin4), ex: "motor stepper1(3, 4, 8, 11)".



**callable variables:**

\-motor::serialData        *float,   should only be called after readSerial()*

\-motor::serialRecieved    *bool,    should only be called after readSerial()*

\-motor::timer             *bool*



**callable functions:**

\-motor::begin()

\-motor::readSerial()

\-motor::timeSerial(int {microseconds}, Boolean {truefalse})

\-void moveServo(int {angle\_degrees}, int {delay})            *This one only works with a PCA board.*

\-void stepperSeconds(float {seconds})                                *This one is only for steppers connected to Arduino pins.*



**Descriptions:**

\-"motor::begin()" is put in the void setup section, it sets I2C Arduino clock to 400kHz and PWM frequency to 50Hz. It also calibrates a PCA board for you if one is plugged into your microcontroller.



\-When calling static variables or static functions in the motor class, motor:: before the call is required. This just means you have to declare the class each time you want to use anything form it.



\-"motor::readSerial()" is used in void loop. It reads a float vale from an Arduino serial chip and stores it in "motor::serialData". If data has been read on a particular loop iteration, "motor::serialRecieved" is set to true for that iteration. If no data has been read from motor::readSerial(), motor::serialRecieved will be set to false. Note that readSerial() will only read the serial chip buffer until there is a float number, and then clears the serial buffer once that number has been read and stored. Note that the data will stay in "motor::serialData" until the variable is cleared or updated.



\-motor::serialRecieved, just detects the moment at which data is recieved from readSerial(). This variable is useful when we only want an action done at the moment when data is read. Example of this at bottom of page.



\-motor::timeSerial(int {microseconds}, Boolean {truefalse}) is used in void loop. It sets a timer from 0ms when the {truefalse} parameter is false. If the {truefalse} has been false for a time of {microseconds}, the function sets "motor::timer" to true. If the {truefalse} parameter is true before the timer reaches {microseconds}, the timer resets back to zero.



\-The "motor::timer" variable has to be reset back to 'false' manually when you are done using it, "motor::timer=false", this prevents you from getting stuck in a loop where "motor::timer" is always true. See example at bottom.



\-void moveServo(int {angle}, int {delay}), makes the servo move to a specific angle at a specific speed. Using readSerial() followed with moveServo({motor::angle}, 0) in void loop will continuously move the motor to a stream of angles sent into the serial monitor.



\-void moveClockwise(float {seconds}), this function moves a stepper motor clockwise for {seconds}. This function is designed based on the 28BYJ-48 stepper motor, it moves the motor at an exact constant 14.5 RPM on a ULN2003 driver being supplied 5 volts. When the motor stats to move, there is a voltage drop of 0.4 volts across the ULN2003 terminals under zero load. Once the motor come to a holt the voltage slowly rises back to 5.



\-void moveAntiClockwise(float {seconds}), moves anti clockwise for {seconds}.



**Example code:** Using the whole class.



\#include <motor.h>



motor servo1(0);



void setup() {

&#x20; Serial.begin(9600);

&#x20;  motor::begin();

}



void loop() {



&#x20; motor::readSerial();



&#x20; if (motor::serialRecieved) {

&#x20;   servo1.move(motor::angle, 0);

&#x20; }

&#x20; motor::timeSerial(5000, motor::serialRecieved);     //counts to 5 while "motor::serialRecieved" is false, counter goes back 						      to zero every time "motor::serialRecieved" is true.

&#x20; if (motor::timer) {                                 //"motor::timer" is true if serialRecieved is true for 5 seconds 						               (therefor no serial data inputted for 5 seconds)

&#x20;   servo1.move(180, 50);                             //slowly moves the servo, to any chosen angle, if no serial data 							       is entered after 5 seconds.

&#x20;   motor::timer=false;                               //the timer must be reset back to false at then end of the statement

&#x20; }                                                   so you don't get stuck in a loop of "motor::timer" always being true.

}

