// DS18B20_2.CPP
#ifdef DS18B20_2_active
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_2 12  // DS18B20 pin
OneWire oneWire2(ONE_WIRE_BUS_2);
DallasTemperature DS18B20_2(&oneWire2);
#endif

void DS18B20_2_INIT(void)
{
#ifdef DS18B20_2_active
  Serial.print("DS18B20_2 Test.....");

  Serial.println("OK");
#endif
}

String DS18B20_2_TEMP_GetData(void)
{
#ifdef DS18B20_2_active
  String Text = "";
  DS18B20_2.requestTemperatures(); 
  Text = DS18B20_2.getTempCByIndex(0);
  return Text;
#else
  return "null";
#endif
}

//Temperatur Außen Gatenseite 1OG
String DS18B20_2_TEMP_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = DS18B20_2_TEMP_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
