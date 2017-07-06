// INA219_1.CPP
#ifdef INA219_1_active

#include <Adafruit_INA219.h>

Adafruit_INA219 INA219_1;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

#endif


void INA219_1_INIT(void)
{
#ifdef INA219_1_active
  Serial.print(F("INA219_1 Test......"));
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  INA219_1.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //INA219_1.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  INA219_1.setCalibration_16V_400mA();
  Serial.println("OK");
#endif
}

String INA219_1_shuntvoltage_GetData(void)
{
#ifdef INA219_1_active
  String Text = "";
 Text = INA219_1.getShuntVoltage_mV();
  return Text;
#else
  return "null";
#endif
}

String INA219_1_busvoltage_GetData(void)
{
#ifdef INA219_1_active
  String Text = "";
 Text = INA219_1.getBusVoltage_V();
  return Text;
#else
  return "null";
#endif
}

String INA219_1_current_mA_GetData(void)
{
#ifdef INA219_1_active
  String Text = "";
 Text = INA219_1.getCurrent_mA();
  return Text;
#else
  return "null";
#endif
}

String INA219_1_loadvoltage_GetData(void)
{
#ifdef INA219_1_active
  String Text = "";
 Text = INA219_1.getBusVoltage_V() + (INA219_1.getShuntVoltage_mV() / 1000);
  return Text;
#else
  return "null";
#endif
}
  
String INA219_1_shuntvoltage_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = INA219_1_shuntvoltage_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String INA219_1_busvoltage_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = INA219_1_busvoltage_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String INA219_1_current_mA_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = INA219_1_current_mA_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String INA219_1_loadvoltage_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = INA219_1_loadvoltage_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
