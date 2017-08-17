// DHT11_1.CPP
#ifdef DHT11_1_active
#include <DHT.h>

#define DHT11_1_PIN 13 // what pin is connected to
DHT DHT11_1(DHT11_1_PIN, DHT11,15);
#endif

void DHT11_1_INIT(void)
{
#ifdef DHT11_1_active
  Serial.print("DHT11_1 Test.......");
  DHT11_1.begin();
  Serial.println("OK");
#endif
}

String DHT11_1_HYDRO_GetData(void)
{
#ifdef DHT11_1_active
  String Text = "";
  Text = DHT11_1.readHumidity();
  return Text;
#else
  return "null";
#endif
}

String DHT11_1_TEMP_GetData(void)
{
#ifdef DHT11_1_active
  String Text = "";
  Text = DHT11_1.readTemperature();
  return Text;
#else
  return "null";
#endif
}

String DHT11_1_TEMP_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = DHT11_1_TEMP_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String DHT11_1_HYDRO_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = DHT11_1_HYDRO_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
