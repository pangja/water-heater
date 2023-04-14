#include "TempSensor.h"

// Data wire is plugged into port 4 on the Arduino
#define ONE_WIRE_BUS 6
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

TempSensor::TempSensor()
{
    sensors.begin();
    // Grab a count of devices on the wire
    numberOfDevices = sensors.getDeviceCount();

// UNCOMMENT FOR DEBUGGING
    // Serial.begin(9600);
    // // locate devices on the bus
    // Serial.print("Locating devices...");
    // Serial.print("Found ");
    // Serial.print(numberOfDevices, DEC);
    // Serial.println(" devices.");

  // //Loop through each device, print out address
  //   for(int i=0;i<numberOfDevices; i++) {
  //       // Search the wire for address
  //       if(sensors.getAddress(tempDeviceAddress, i)) {
  //         Serial.print("Found device ");
  //         Serial.print(i, DEC);
  //         Serial.print(" with address: ");
  //         Serial.println();
  //       } else {
  //         Serial.print("Found ghost device at ");
  //         Serial.print(i, DEC);
  //         Serial.print(" but could not detect address. Check power and cabling");
  //       }
  //   }
}

// Date member function
void TempSensor::getTemperatures()
{

  sensors.requestTemperatures(); // Send the command to get temperatures
  
  for(int i=0;i<numberOfDevices; i++) {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
    
    if (i == 0) {
        waterTemp = sensors.getTempC(tempDeviceAddress);
    } else {
        airTemp = sensors.getTempC(tempDeviceAddress);
    }
    }   
  }
}
