/*
 * HDPR temperature sensor reading sketch
 */

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_PIN 2

OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);
float temperatures[6] = {0};

struct SENSOR
{
  char name[3];
  DeviceAddress address;
  float temperature;
};

SENSOR temp_sensors[6] = {
  {"FR", {0x28, 0x76, 0x91, 0xA1, 0x08, 0x00, 0x00, 0x4D}, 0},
  {"CR", {0x28, 0x48, 0x5E, 0xA4, 0x08, 0x00, 0x00, 0x7F}, 0},
  {"RR", {0x28, 0x62, 0xDB, 0xA0, 0x08, 0x00, 0x00, 0x11}, 0},
  {"FL", {0x28, 0x88, 0x16, 0xA3, 0x08, 0x00, 0x00, 0xB1}, 0},
  {"CL", {0x28, 0x8C, 0x06, 0xA1, 0x08, 0x00, 0x00, 0x16}, 0},
  {"RL", {0x28, 0x9F, 0xD9, 0xA0, 0x08, 0x00, 0x00, 0xAA}, 0}
  };

void setup()
{
  Serial.begin(9600);
  
  sensors.begin();

  for(int i = 0; i < sizeof(temp_sensors) / sizeof(temp_sensors[0]); i++)
  {
    sensors.setResolution(temp_sensors[i].address, 10);
  }
}

void loop()
{
  float temp;
  sensors.requestTemperatures();
  
  for(int i = 0; i < 6; i++)
  {
    // Read the sensor
    temp = sensors.getTempC(temp_sensors[i].address);
    
    // If it returns -127 it means the reading was unsuccesful
    /*if(temp == -127.0f)
    {
      temperatures[i] = temp_sensors[i].temperature;
    }
    else
    {
      // Send the temperature only when the reading was successful
      temperatures[i] = temp;
      temp_sensors[i].temperature = temp;
    }*/
    
    // Send all temperatures anyway and take care of the errors somewhere else
    temperatures[i] = temp;
  }

  sendTemperatures();
  
  delay(200);
  digitalWrite(13, !digitalRead(13));
}

void sendTemperatures()
{
  // Header signature
  static const byte header[4] = {0xFE, 0x81, 0xFF, 0x55};
  
  // Sequential counter, loops back to 0 after 127
  static byte sequence = 0;

  // Transmit header
  int i;
  for(i = 0; i < sizeof(header) / sizeof(header[0]); i++)
  {
    Serial.write(header[i]);
  }

  // Write out the sequence and increase by 1
  Serial.write(sequence++);

  // Loop sequence back to 0
  if(sequence == 128)
  {
    sequence = 0;
  }

  // Send out the temperature values
  for(i = 0; i < sizeof(temperatures); i++)
  {
    // Write out all the bytes of the temperature array
    byte * b = (byte *) &temperatures + i;
    Serial.write(*b);
  }
}

