//Libraries used
#include <Wire.h>              //Wire library for communicating through I2C
#include <Adafruit_PCF8574.h>  //Library for PCF8574 GPIO expander, opens up 8 GPIO pins through one address 0x20

// The available pins on the CYD are
// GPIO 35 — on the P3 connector, GPIO 22 — on the P3 and CN1 connector, GPIO 27 — on the CN1 connector.
// GPIO 27 will be used for SERIAL DATA for I2C communication.
// GPIO 22 will be used for SERIAL CLOCK for I2C Communication.
#define I2C_SDA 27  //Sets I2C Data to GPIO pin 27.
#define I2C_SCL 22  //Sets I2c Clock to GPIO pin 22.

#define PCF_BUTTON 6  //Initializes GPIO pin 6 of the PCF8574.
#define ADA_INTER_PIN 35    //Sets the PCF8574 interupt pin (INT) to GPIO pin 35.

//To begin I2C communication with ESP32 first you must construct the Wire object of class TwoWire.
//If we choose to add more I2C periferals we would define them as TwoWire(1),TwoWire(2), etc.
TwoWire PCF8574 = TwoWire(0);

// Now if we try to initialize I2C communication our Wire library would overwrite the Adafruit_PCF8574 library,
// so we must construct a wire object of class Adafruit_PCF8574.
Adafruit_PCF8574 pcf;
//int val;

void setup() {
  Serial.begin(115200);          //Begins serial communication.
  Wire.begin(I2C_SDA, I2C_SCL);  //Initializes Data & Clock pins for I2C communication.


  Serial.println("Adafruit PCF8574 test");

  //Initializes Wire communication. Takes in the parameters of DATA pin, CLOCK Pin, Clock Speed.
  if (!PCF8574.begin(I2C_SDA, I2C_SCL, 100000)) {
    Serial.println("Couldn't find it.");
  }
  //Initializes PCF8574 communication. Takes in the parameter of Address. (0x20 being the default).
  if (!pcf.begin(0x20)) {
    Serial.println("Couldn't find PCF8574");
  }
  Serial.println("I Guess We Found It!");

  //Sets the pin mode of a pin either INPUT, INPUT with built in Pullup resistor or OUTPUT.
  //Takes the parameters of selected pin, selected mode.
  pcf.pinMode(PCF_BUTTON, INPUT);
  pinMode(ADA_INTER_PIN, INPUT_PULLUP); //sets the interupt pin to input and sets on the internal pullup resistor. 
  attachInterrupt(digitalPinToInterrupt(ADA_INTER_PIN), buttonRead, CHANGE);
}

void buttonRead (void) {
  Serial.println("B"); //Print the character "B" when a button is pressed and tests the interupt. 
}

void loop() {
  //bool val = pcf.digitalRead(PCF_BUTTON);
  
  delay(500);
  //Serial.println(val);

}