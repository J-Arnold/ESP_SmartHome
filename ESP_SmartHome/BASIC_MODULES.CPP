// BASIC_MODULES.CPP

extern "C" {     
  #include "user_interface.h"
  uint16 readvdd33(void);
}// - See more at: http://www.esp8266.com/viewtopic.php?f=13&t=3839#sthash.D22VMrVZ.dpuf

String milli2time(unsigned long mSekunden)
{   // Zeit in ms seit µC Reset wird zerlegt für hh:mm:ss Format
String TIME = "";
String help = ""; 
      
int Tage          =  mSekunden/86400000;
int Stunden       = (mSekunden-((Tage*86400000)))/3600000; 
int Minuten       = (mSekunden-((Tage*86400000)+(Stunden*3600000)))/60000;
int Sekunden      = (mSekunden-((Tage*86400000)+(Stunden*3600000)+(Minuten*60000)))/1000;
int MilliSekunden =  mSekunden-((Tage*86400000)+(Stunden*3600000)+(Minuten*60000)+(Sekunden*1000));
help = String(Tage);
TIME = help + "Tage ";
help = String(Stunden);
help = "000" + help;
help = help.substring(help.length()-2);
TIME = TIME + help + ":";
help = String(Minuten);
help = "000" + help;
help = help.substring(help.length()-2);
TIME = TIME + help + ":";
help = String(Sekunden);
help = "000" + help;
help = help.substring(help.length()-2);
TIME = TIME + help + " ";
help = String(MilliSekunden);
help = "0000" + help;
help = help.substring(help.length()-3);
TIME = TIME + help;
return TIME;
} 

String WiFi_RSSI_handle(String Label){
  String Text = "";
  String Data = "";
  Data = WiFi.RSSI();
  Text = Label + "=" + Data;
  return Text;
} 

String vdd33_handle(String Label){
  String Text = "";
  String Data = "";
  Data = readvdd33();
  Text = Label + "=" + Data;
#ifdef Serial_on
  Serial.println(Text);
#endif
  return Text;
} 

String UPTIME_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = milli2time(millis());
  Text = Label + "=" + Data;
  return Text;
}

String Root_Text() {
  String Text = "";
  String Data = "";
  String Root_Return_Text;

//ESP.getResetReason() returns String containing the last reset resaon in human readable format.  
  Data = ESP.getResetReason();
  Text = "getResetReason = " + Data;
  Root_Return_Text = Root_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = WiFi.RSSI();
  Text = WiFi_RSSI_text_long + Data + WiFi_RSSI_text_unit;
  Root_Return_Text = Root_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = milli2time(millis());
  Text = UPTIME_text_long + Data + UPTIME_text_unit;
  Root_Return_Text = Root_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

//ESP.getVcc() may be used to measure supply voltage. ESP needs to reconfigure the ADC at startup in order for this feature to be available. Add the following line to the top of your sketch to use getVcc:
  Data = readvdd33();
  Text = vdd33_text_long + Data + vdd33_text_unit;
  Root_Return_Text = Root_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
  return(Root_Return_Text);
}

String System_Text() {
  String Text = "";
  String Data = "";
  String System_Return_Text;
  
//ESP.getResetReason() returns String containing the last reset resaon in human readable format.  
  Data = ESP.getResetReason();
  Text = "getResetReason = " + Data;
  System_Return_Text = System_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

//ESP.getFreeHeap() returns the free heap size.
  Data = ESP.getFreeHeap();
  Text = "getFreeHeap = " + Data + " bytes";
  System_Return_Text = System_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

//ESP.getChipId() returns the ESP8266 chip ID as a 32-bit integer.
  Data = ESP.getChipId();
  Text = "getChipId = " + Data;
  System_Return_Text = System_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

//Several APIs may be used to get flash chip info:
//ESP.getFlashChipId() returns the flash chip ID as a 32-bit integer.
  Data = ESP.getFlashChipId();
  Text = "getFlashChipId = " + Data;
  System_Return_Text = System_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

// ESP.getFlashChipSize() returns the flash chip size, in bytes, as seen by the SDK (may be less than actual size).
  Data = ESP.getFlashChipSize();
  Text = "getFlashChipSize = " + Data;
  System_Return_Text = System_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

//ESP.getFlashChipSpeed() returns the flash chip frequency, in Hz.
  Data = ESP.getFlashChipSpeed();
  Text = "getFlashChipSpeed = " + Data;
  System_Return_Text = System_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

//ESP.getCycleCount() returns the cpu instruction cycle count since start as an unsigned 32-bit. This is useful for accurate timing of very short actions like bit banging.
  Data = ESP.getCycleCount();
  Text = "getCycleCount = " + Data;
  System_Return_Text = System_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  return(System_Return_Text);
}

String Sensor_Text() {
  String Text = "";
  String Data = "";
  String Sensor_Return_Text;

#ifdef Rollo_1_active
  Data = Rollo_1_HTML_GetData();
  Text = Rollo_1_HTML_text_long + Data + Rollo_1_HTML_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif
/*
#ifdef Rollo_2_active
  Data = Rollo_2_HTML_GetData();
  Text = Rollo_2_HTML_text_long + Data + Rollo_2_HTML_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif
*/
#ifdef BH1750_1_active
  Data = BH1750_1_LUX_GetData();
  Text = BH1750_1_LUX_text_long + Data + BH1750_1_LUX_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef BME280_1_active
  Data = BME280_1_ALT_GetData();
  Text = BME280_1_ALT_text_long + Data + BME280_1_ALT_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = BME280_1_HYDRO_GetData();
  Text = BME280_1_HYDRO_text_long + Data + BME280_1_HYDRO_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = BME280_1_PRESS_GetData();
  Text = BME280_1_PRESS_text_long + Data + BME280_1_PRESS_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = BME280_1_TEMP_GetData();
  Text = BME280_1_TEMP_text_long + Data + BME280_1_TEMP_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef BME280_2_active
  Data = BME280_2_ALT_GetData();
  Text = BME280_2_ALT_text_long + Data + BME280_2_ALT_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = BME280_2_HYDRO_GetData();
  Text = BME280_2_HYDRO_text_long + Data + BME280_2_HYDRO_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = BME280_2_PRESS_GetData();
  Text = BME280_2_PRESS_text_long + Data + BME280_2_PRESS_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = BME280_2_TEMP_GetData();
  Text = BME280_2_TEMP_text_long + Data + BME280_2_TEMP_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef DS18B20_1_active
  Data = DS18B20_1_TEMP_GetData();
  Text = DS18B20_1_TEMP_text_long + Data + DS18B20_1_TEMP_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef DS18B20_2_active
  Data = DS18B20_2_TEMP_GetData();
  Text = DS18B20_2_TEMP_text_long + Data + DS18B20_1_TEMP_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef INA219_1_active
  Data = INA219_1_busvoltage_GetData();
  Text = INA219_1_busvoltage_text_long + Data + INA219_1_busvoltage_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = INA219_1_current_mA_GetData();
  Text = INA219_1_current_mA_text_long + Data + INA219_1_current_mA_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = INA219_1_loadvoltage_GetData();
  Text = INA219_1_loadvoltage_text_long + Data + INA219_1_loadvoltage_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = INA219_1_shuntvoltage_GetData();
  Text = INA219_1_shuntvoltage_text_long + Data + INA219_1_shuntvoltage_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef MCP9808_1_active 
  Data = MCP9808_1_TEMP_GetData();
  Text = MCP9808_1_TEMP_text_long + Data + MCP9808_1_TEMP_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  MCP9808_1.shutdown_wake(0);
  Data = MCP9808_1.readTempC();
  delay(250);
  MCP9808_1.shutdown_wake(1);
  //Data = MCP9808_1_TEMP_GetData();
  Text = MCP9808_1_TEMP_text_long + Data + MCP9808_1_TEMP_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";

#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef MCP9808_2_active  
  Data = MCP9808_2_TEMP_GetData();
  Text = MCP9808_2_TEMP_text_long + Data + MCP9808_2_TEMP_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
  
  MCP9808_2.shutdown_wake(0);
  Data = MCP9808_2.readTempC();
  delay(250);
  MCP9808_2.shutdown_wake(1);
//  Data = MCP9808_2_TEMP_GetData();
  Text = MCP9808_2_TEMP_text_long + Data + MCP9808_2_TEMP_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef PCF8574_1_active
  Data = PCF8574_1_GetData(1);
  Text = PCF8574_1_1_text_long + Data + PCF8574_1_1_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = PCF8574_1_GetData(2);
  Text = PCF8574_1_2_text_long + Data + PCF8574_1_2_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = PCF8574_1_GetData(3);
  Text = PCF8574_1_3_text_long + Data + PCF8574_1_3_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = PCF8574_1_GetData(4);
  Text = PCF8574_1_4_text_long + Data + PCF8574_1_4_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = PCF8574_1_GetData(5);
  Text = PCF8574_1_5_text_long + Data + PCF8574_1_5_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = PCF8574_1_GetData(6);
  Text = PCF8574_1_6_text_long + Data + PCF8574_1_6_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = PCF8574_1_GetData(7);
  Text = PCF8574_1_7_text_long + Data + PCF8574_1_7_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = PCF8574_1_GetData(8);
  Text = PCF8574_1_8_text_long + Data + PCF8574_1_8_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef SI1145_1_active
  Data = SI1145_1_IR_GetData();
  Text = SI1145_1_IR_text_long + Data + SI1145_1_IR_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = SI1145_1_UV_GetData();
  Text = SI1145_1_UV_text_long + Data + SI1145_1_UV_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif

  Data = SI1145_1_VISIBLE_GetData();
  Text = SI1145_1_VISIBLE_text_long + Data + SI1145_1_VISIBLE_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef TSL2561_1_active
  Data = TSL2561_1_GetData();
  Text = TSL2561_1_LUX_text_long + Data + TSL2561_1_LUX_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

#ifdef VEML6070_1_active
  Data = VEML6070_1_UV_GetData();
  Text = VEML6070_1_UV_text_long + Data + VEML6070_1_UV_text_unit;
  Sensor_Return_Text = Sensor_Return_Text + Text + "</BR>";
#ifdef Serial_on
  Serial.println(Text);
#endif
#endif

  Sensor_Return_Text = Sensor_Return_Text + "<BR><BR><a href=\"http://" + WiFi.localIP() + "/\"><button>Back</button></a>";

  return(Sensor_Return_Text);
}

