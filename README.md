# HDPR motor temperature

This repository contains the sketch that must be loaded on the Arduino Leonardo that polls the DS18B20 temperature sensors installed inside the motor housings of HDPR.

## Install

The sketch requires the [OneWire](https://github.com/PaulStoffregen/OneWire) and [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library) libraries.

## Usage

* `temperature_sensors_HDPR`: sends the temperature values according to the [temperature driver](https://github.com/hdpr-rover/drivers-temperature) protocol.
* `temperature_test`: sends dummy values to test the [temperature driver](https://github.com/hdpr-rover/drivers-temperature).
* `multiple_dallas_temperature`: reads the HDPR temperatures and outputs them in a readable format in the Arduino serial monitor.

