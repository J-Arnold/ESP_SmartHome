// BME280_1.CPP
#ifdef BME280_1_active
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 BME280_1; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);
#endif

void BME280_1_INIT(void)
{
#ifdef BME280_1_active
  Serial.print("BME280_1 Test......");
//I2C device found at address 0x76  ! bme280 1
//I2C device found at address 0x77  ! bme280 2
  if (!BME280_1.begin(0x76)) {
    Serial.println("Fail");
  } else {
    Serial.println("OK");
  }
#endif
}

String BME280_1_TEMP_GetData(void)
{
#ifdef BME280_1_active
  String Text = "";
 Text = BME280_1.readTemperature();
  return Text;
#else
  return "null";
#endif
}

String BME280_1_TEMP_GetData_fahrenheit(void)
{
#ifdef BME280_1_active
  float C;
  float F;
  C = BME280_1.readTemperature();
  F = C * 9.0 / 5.0 + 32;
  return String(F);
#else
  return "null";
#endif
}

String BME280_1_PRESS_GetData(void)
{
#ifdef BME280_1_active
  float C;
  String Text = "";
  C = BME280_1.readPressure() / 100.0F;
  Text = C;
  return Text;
#else
  return "null";
#endif
}

String BME280_1_HYDRO_GetData(void)
{
#ifdef BME280_1_active
  String Text = "";
  Text = BME280_1.readHumidity();
  return Text;
#else
  return "null";
#endif
}

String BME280_1_ALT_GetData(void)
{
#ifdef BME280_1_active
  String Text = "";
  Text = BME280_1.readAltitude(SEALEVELPRESSURE_HPA);
  return Text;
#else
  return "null";
#endif
}

String BME280_1_TEMP_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = BME280_1_TEMP_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String BME280_1_HYDRO_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = BME280_1_HYDRO_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String BME280_1_PRESS_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = BME280_1_PRESS_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String BME280_1_ALT_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = BME280_1_ALT_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
