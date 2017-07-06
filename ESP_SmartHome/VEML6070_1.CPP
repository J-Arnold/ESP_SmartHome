// VEML6070_1.CPP
#ifdef VEML6070_1_active

#include "Adafruit_VEML6070.h"

Adafruit_VEML6070 VEML6070_1 = Adafruit_VEML6070();

#endif

void VEML6070_1_INIT(void)
{
#ifdef VEML6070_1_active
  Serial.print(F("VEML6070_1 Test...."));
  VEML6070_1.begin(VEML6070_1_T);
  Serial.println("OK");
#endif
}

String VEML6070_1_UV_GetData(void)
{
#ifdef VEML6070_1_active
  String Text = "";
 Text = VEML6070_1.readUV();
  return Text;
#else
  return "null";
#endif
}

String VEML6070_1_UV_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = VEML6070_1_UV_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
