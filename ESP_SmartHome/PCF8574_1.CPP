// PCF8574_1.CPP
#ifdef PCF8574_1_active
#include <PCF8574.h>

PCF8574 PCF8574_1;
#endif

void PCF8574_1_INIT(void)
{
#ifdef PCF8574_1_active
/* Start I2C bus and PCF8574 instance */
  Serial.print("PCF8574_1 Test.....");
  PCF8574_1.begin(0x20);
  PCF8574_1.pinMode(0, INPUT_PULLUP);
  PCF8574_1.pinMode(1, INPUT_PULLUP);
  PCF8574_1.pinMode(2, INPUT_PULLUP);
  PCF8574_1.pinMode(3, INPUT_PULLUP);
  PCF8574_1.pinMode(4, INPUT_PULLUP);
  PCF8574_1.pinMode(5, INPUT_PULLUP);
  PCF8574_1.pinMode(6, INPUT_PULLUP);
  PCF8574_1.pinMode(7, INPUT_PULLUP);
  Serial.println("OK");
#endif
}

String PCF8574_1_GetData(int pin)
{
#ifdef PCF8574_1_active
  String Text = "";
  Text = PCF8574_1.digitalRead(pin-1);
  return Text;
#else
  return "null";
#endif
}

String PCF8574_1_handle(int pin, String Label) {
  String Text = "";
  String Data = "";
  Data = PCF8574_1_GetData(pin);
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
