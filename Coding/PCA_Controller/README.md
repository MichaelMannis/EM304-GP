##### PCA\_Controller library



**Object constructor:**

\-PCA servo\_name(pca\_channel\_number), ex: "PCA servo1(0)"



**callable variables:**

\-PCA::angle             *integer, can only be called after readSerial()*

\-PCA::serialRecieved    *bool,    can only be called after readSerial()*

\-PCA::timer             *bool*



**callable functions:**

\-PCA::begin()

\-PCA::readSerial()

\-PCA::timeSerial(int {microseconds}, Boolean {truefalse})

\-servo1.moveServo(int {angle\_degrees}, int {delay})



**Descriptions:**

\-"PCA::begin()" is put in the void setup section, it calibrates the PCA board.



\-When calling the class variables or functions, PCA::{variable/function} is required.



\-"PCA::readSerial()" is used in void loop. It reads an integer sent to the Arduinos serial chip and stores it in "PCA::angle". If data has been passed to "PCA::angle" on a particular loop iteration, "PCA::serialRecieved" is set to true for that iteration. Data can be sent to the serial chip outside of arduino IDE. Python and java can write serial data to the chip using .write() serial functions.      python: ser.write(b"90\n") will send 90 to the serial chip which can then be picked up by this function, but only if it is written in this specific form. 



\-PCA::timeSerial(int {microseconds}, Boolean {truefalse}) is used in void loop. It sets a timer from 0ms when the {truefalse} parameter is false. If the {truefalse} has been false for a time of {microseconds}, the function sets "PCA::timer" to true. If the {truefalse} parameter is true before the timer reaches {microseconds}, the timer resets back to zero.



\-The "PCA::timer" variable has to be reset back to 'false' manually when you are done using it, "PCA::timer=false", this prevents you from getting stuck in a loop where "PCA::timer" is always true. See example at bottom.



\-servo1.moveServo(int {angle}, int {delay}), makes the motor move to a specific angle at a specific speed. Using readSerial() followed with servo1.move(PCA::angle, 0) in void loop will continuously move the motor to the stream of angles sent into the serial monitor.







**Example code:** Using the whole class.



\#include <PCA.h>



PCA servo1(0);



void setup() {

&#x20; Serial.begin(9600);

&#x20;  PCA::begin();

}



void loop() {



&#x20; PCA::readSerial();



&#x20; if (PCA::serialRecieved) {

&#x20;   servo1.move(PCA::angle, 0);

&#x20; }

&#x20; PCA::timeSerial(5000, PCA::serialRecieved);       //counts to 5 while "PCA::serialRecieved" is false, counter goes back 						      to zero every time "PCA::serialRecieved" is true.

&#x20; if (PCA::timer) {                                 //"PCA::timer" is true if serialRecieved is true for 5 seconds 						               (therefor no serial data inputted for 5 seconds)

&#x20;   servo1.move(180, 50);                            //slowly moves the servo, to any chosen angle, if no serial data 							       is entered after 5 seconds.

&#x20;   PCA::timer=false;                               //the timer must be reset back to false at then end of the statement

&#x20; }                                                   so you don't get stuck in a loop of "PCA::timer" always being true.

}



