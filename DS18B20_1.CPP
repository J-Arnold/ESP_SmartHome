// DS18B20_1.CPP
#ifdef DS18B20_1_active
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_1 10  // DS18B20 pin
OneWire oneWire1(ONE_WIRE_BUS_1);
DallasTemperature DS18B20_1(&oneWire1);
#endif

void DS18B20_1_INIT(void)
{
#ifdef DS18B20_1_active
  Serial.print("DS18B20_1 Test.....");

  Serial.println("OK");
#endif
}

String DS18B20_1_TEMP_GetData(void)
{
#ifdef DS18B20_1_active
  String Text = "";
  DS18B20_1.requestTemperatures(); 
  Text = DS18B20_1.getTempCByIndex(0);
  return Text;
#else
  return "null";
#endif
}

//Temperatur Außen Gatenseite 1OG
String DS18B20_1_TEMP_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = DS18B20_1_TEMP_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
