// MCP9808_1.CPP
#ifdef MCP9808_1_active
#include <Adafruit_MCP9808.h>
#include <Adafruit_Sensor.h>

Adafruit_MCP9808 MCP9808_1 = Adafruit_MCP9808();
#endif

void MCP9808_1_INIT(void)
{
#ifdef MCP9808_1_active
  Serial.print("MCP9808_1 Test.....");
  // Make sure the sensor is found, you can also pass in a different i2c
  // address with tempsensor.begin(0x19) for example
  if (!MCP9808_1.begin(0x18)) {
    Serial.println("Fail");
  } else {
  /* //can be turend on for testing
  Serial.println("wake up MCP9808.... "); // wake up MCP9808 - power consumption ~200 mikro Ampere
  tempsensor.shutdown_wake(0);            // Don't remove this line! required before reading temp
  // Read and print out the temperature, then convert to *F
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
  Serial.print(f); Serial.println("*F");
  delay(250);
  Serial.println("Shutdown MCP9808.... ");
  */
    MCP9808_1.shutdown_wake(1); // shutdown MCP9808 - power consumption ~0.1 mikro Ampere
    Serial.println("OK");
  }
#endif
}

String MCP9808_1_TEMP_GetData(void)
{
#ifdef MCP9808_1_active
  String Text = "";
  MCP9808_1.shutdown_wake(0);
  Text = MCP9808_1.readTempC();
  delay(250);
  MCP9808_1.shutdown_wake(1);
  return Text;
#else
  return "null";
#endif
}

String MCP9808_1_TEMP_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = MCP9808_1_TEMP_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

/*
String MCP9808_1_TEMP_GetData_fahrenheit(void)
{
#ifdef MCP9808_1_active
  float C;
  float F;
  MCP9808_1.shutdown_wake(0);
  C = MCP9808_1.readTempC();
  F = C * 9.0 / 5.0 + 32;
  MCP9808_1.shutdown_wake(1);
  return String(F);
#else
  return "null";
#endif
}
*/
