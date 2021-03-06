/* YourDuino Multiple DS18B20 Temperature Sensors on 1 wire
  Connections:
  DS18B20 Pinout (Left to Right, pins down, flat side toward you)
  - Left   = Ground
  - Center = Signal (Pin 2):  (with 3.3K to 4.7K resistor to +5 or 3.3 )
  - Right  = +5 or +3.3 V

   Questions: terry@yourduino.com 
   V1.01  01/17/2013 ...based on examples from Rik Kretzinger
   
/*-----( Import needed libraries )-----*/
// Get 1-wire Library here: http://www.pjrc.com/teerequestTemperaturesnsy/td_libs_OneWire.html
#include <OneWire.h>

//Get DallasTemperature Library here:  http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library
#include <DallasTemperature.h>

/*-----( Declare Constants and Pin Numbers )-----*/
#define ONE_WIRE_BUS_PIN 2

/*-----( Declare objects )-----*/
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS_PIN);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*-----( Declare Variables )-----*/
// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress Probe01 = { 0x28, 0x76, 0x91, 0xA1, 0x08, 0x00, 0x00, 0x4D }; //FR
DeviceAddress Probe02 = { 0x28, 0x48, 0x5E, 0xA4, 0x08, 0x00, 0x00, 0x7F }; //CR
DeviceAddress Probe03 = { 0x28, 0x62, 0xDB, 0xA0, 0x08, 0x00, 0x00, 0x11 }; //RR
DeviceAddress Probe04 = { 0x28, 0x88, 0x16, 0xA3, 0x08, 0x00, 0x00, 0xB1 }; //FL
DeviceAddress Probe05 = { 0x28, 0x8C, 0x06, 0xA1, 0x08, 0x00, 0x00, 0x16 }; //CL
DeviceAddress Probe06 = { 0x28, 0x9F, 0xD9, 0xA0, 0x08, 0x00, 0x00, 0xAA }; //RL


void setup()   /****** SETUP: RUNS ONCE ******/
{
  // start serial port to show results
  Serial.begin(115200);
  Serial.print("Initializing Temperature Control Library Version ");
  Serial.println(DALLASTEMPLIBVERSION);
  
  // Initialize the Temperature measurement library
  sensors.begin();
  
  // set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
  sensors.setResolution(Probe01, 10);
  sensors.setResolution(Probe02, 10);
  sensors.setResolution(Probe03, 10);
  sensors.setResolution(Probe04, 10);
  sensors.setResolution(Probe05, 10);
  sensors.setResolution(Probe06, 10);


}//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{

  int test;
  delay(1000);
  Serial.println();
  Serial.print("Number of Devices found on bus = ");  
  //Serial.println(sensors.getDeviceCount());   
  Serial.print("Getting temperatures... ");  
  Serial.println();   
  
  // Command all devices on bus to read temperature  
  test = sensors.requestTemperaturesByAddress(Probe01);  
      Serial.println(test);

  delay(1000);
  
  Serial.print("Probe FR temperature is:   ");
  printTemperature(Probe01);
  Serial.println();

    delay(1000);

  test = sensors.requestTemperaturesByAddress(Probe02);  
      Serial.println(test);

  delay(1000);
  Serial.print("Probe CR temperature is:   ");
  printTemperature(Probe02);
  Serial.println();
    delay(1000);

   test = sensors.requestTemperaturesByAddress(Probe03);  
       Serial.println(test);

  delay(1000);
  Serial.print("Probe RR temperature is:   ");
  printTemperature(Probe03);
  Serial.println();
    delay(1000);

     test = sensors.requestTemperaturesByAddress(Probe04);  
         Serial.println(test);

  delay(1000);
  Serial.print("Probe FL temperature is:   ");
  printTemperature(Probe04);
  Serial.println();
    delay(1000);

    test = sensors.requestTemperaturesByAddress(Probe05);  
        Serial.println(test);

  delay(1000);
  Serial.print("Probe CL temperature is:   ");
  printTemperature(Probe05);
  Serial.println();
    delay(1000);

    test = sensors.requestTemperaturesByAddress(Probe06);  
    Serial.println(test);
  delay(1000);
  Serial.print("Probe RL temperature is:   ");
  printTemperature(Probe06);
  Serial.println();
   
  
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
void printTemperature(DeviceAddress deviceAddress)
{
float tempC;
  do{
 tempC = sensors.getTempC(deviceAddress);
  }
while(tempC == -127.00); 

   if (tempC == -127.00) 
   {
   Serial.print("Error getting temperature  ");
   } 
   else
   {
   Serial.print("C: ");
   Serial.print(tempC);
   Serial.print(" F: ");
   Serial.print(DallasTemperature::toFahrenheit(tempC));
   }
}// End printTemperature
//*********( THE END )***********
