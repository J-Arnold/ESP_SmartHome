// DHT11_2.CPP
#ifdef DHT11_2_active
#include <DHT.h>

#define DHT11_2_PIN 10 // what pin is connected to
DHT DHT11_2(DHT11_2_PIN, DHT11,15);
#endif

void DHT11_2_INIT(void)
{
#ifdef DHT11_2_active
  Serial.print("DHT11_2 Test.......");
  DHT11_1.begin();
  Serial.println("OK");
#endif
}

String DHT11_2_HYDRO_GetData(void)
{
#ifdef DHT11_2_active
  String Text = "";
  Text = DHT11_2.readHumidity();
  return Text;
#else
  return "null";
#endif
}

String DHT11_2_TEMP_GetData(void)
{
#ifdef DHT11_2_active
  String Text = "";
  Text = DHT11_2.readTemperature();
  return Text;
#else
  return "null";
#endif
}

String DHT11_2_TEMP_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = DHT11_2_TEMP_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String DHT11_2_HYDRO_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = DHT11_2_HYDRO_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
