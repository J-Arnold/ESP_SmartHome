// BME280_2.CPP
#ifdef BME280_2_active
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme2; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);
#endif

void BME280_2_INIT(void)
{
#ifdef BME280_2_active
  Serial.print("BME280_2 Test......");
//I2C device found at address 0x76  ! bme280 1 Jens
//I2C device found at address 0x77  ! bme280 2 Kai
  if (!bme2.begin(0x77)) {
    Serial.println("Fail");
  } else {
    Serial.println("OK");
  }
#endif
}

String BME280_2_TEMP_GetData(void)
{
#ifdef BME280_2_active
  String Text = "";
 Text = bme2.readTemperature();
  return Text;
#else
  return "null";
#endif
}

String BME280_2_TEMP_GetData_fahrenheit(void)
{
#ifdef BME280_2_active
  float C;
  float F;
  C = bme2.readTemperature();
  F = C * 9.0 / 5.0 + 32;
  return String(F);
#else
  return "null";
#endif
}

String BME280_2_PRESS_GetData(void)
{
#ifdef BME280_2_active
  float C;
  String Text = "";
  C = bme2.readPressure() / 100.0F;
  Text = C;
  return Text;
#else
  return "null";
#endif
}

String BME280_2_HYDRO_GetData(void)
{
#ifdef BME280_2_active
  String Text = "";
  Text = bme2.readHumidity();
  return Text;
#else
  return "null";
#endif
}

String BME280_2_ALT_GetData(void)
{
#ifdef BME280_2_active
  String Text = "";
  Text = bme2.readAltitude(SEALEVELPRESSURE_HPA);
  return Text;
#else
  return "null";
#endif
}

String BME280_2_TEMP_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = BME280_2_TEMP_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String BME280_2_HYDRO_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = BME280_2_HYDRO_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String BME280_2_PRESS_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = BME280_2_PRESS_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String BME280_2_ALT_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = BME280_2_ALT_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
