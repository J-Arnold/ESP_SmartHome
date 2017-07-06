//#define ESP_SmartHome_Demo1
#define ESP_SmartHome_All
//#define ESP_SmartHome_None

#define VERSION "V1.0.0 2017-07-05"
// GPIO 00
// GPIO 02 LED
// GPIO 04 I2C SDA
// GPIO 05 I2C SCL
// GPIO 09 
// GPIO 10 DS18B20_1
// GPIO 12 DS18B20_2
// GPIO 13 
// GPIO 14 
// GPIO 15
// GPIO 16 
//I2C device found at address 0x18  ! MCP9808 1
//I2C device found at address 0x19  ! MCP9808 2
//I2C device found at address 0x20  ! PCF8574
//I2C device found at address 0x23  ! BH1750
//I2C device found at address 0x29  ! TSL2561
//I2C device found at address 0x38  ! VEML6070
//I2C device found at address 0x39  ! VEML6070
//I2C device found at address 0x40  ! INA219
//I2C device found at address 0x3C  ! OLED
//I2C device found at address 0x76  ! bme280 1
//I2C device found at address 0x77  ! bme280 2
//I2C device found at address 0x1E  ! HMC5883L
// ESP8266 libraries used:
// - BH1750            - https://github.com/claws/BH1750
// - BME280 & MCP9808  - https://github.com/adafruit/Adafruit_Sensor
// - BME280            - https://github.com/adafruit/Adafruit_BME280_Library
// - DS18B20           - https://github.com/milesburton/Arduino-Temperature-Control-Library
// - DS18B20           - https://github.com/PaulStoffregen/OneWire
// - INA219            - https://github.com/adafruit/Adafruit_INA219
// - MCP9808           - https://github.com/adafruit/Adafruit_MCP9808_Library
// - PCF8574           - https://github.com/skywodd/pcf8574_arduino_library
// in PCF8574.h
/** Comment this define to disable interrupt support */
//#define PCF8574_INTERRUPT_SUPPORT

// - SI1145            - https://github.com/adafruit/Adafruit_SI1145_Library
// - TSL2561           - https://github.com/adafruit/Adafruit_TSL2561
// - VEML6070          - https://github.com/adafruit/Adafruit_VEML6070

#include <Wire.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include "Config.h"

#define Serial_on
// Use server.send(200, "text/plain"," to send Plain Text HTML are shown");
String WebSideType = WebSideType;
#define WebSideStart "<!DOCTYPE HTML><html><body> "
#define WebSideEnd "</body></html>"
//#define WebSideStart "<!DOCTYPE HTML> <html> "
//#define WebSideEnd "<BR> </html> "

#ifdef BH1750_1_active
#include "BH1750_1.CPP"
#endif
#ifdef BME280_1_active
#include "BME280_1.CPP"
#endif
#ifdef BME280_2_active
#include "BME280_2.CPP"
#endif
#ifdef DS18B20_1_active
#include "DS18B20_1.CPP"
#endif
#ifdef DS18B20_2_active
#include "DS18B20_2.CPP"
#endif
#ifdef INA219_1_active
#include "INA219_1.CPP"
#endif
#ifdef MCP9808_1_active
#include "MCP9808_1.CPP"
#endif
#ifdef MCP9808_2_active
#include "MCP9808_2.CPP"
#endif
#ifdef PCF8574_1_active
#include "PCF8574_1.CPP"
#endif
#ifdef Rollo_1_active
#include "Rollo_1.CPP"
#endif
#ifdef Rollo_2_active
#include "Rollo_2.CPP"
#endif
#ifdef SI1145_1_active
#include "SI1145_1.CPP"
#endif
#ifdef TSL2561_1_active
#include "TSL2561_1.CPP"
#endif
#ifdef VEML6070_1_active
#include "VEML6070_1.CPP"
#endif

#include "BASIC_MODULES.CPP"

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
IPAddress dns(192,168,100,254);  
IPAddress gateway(192,168,100,254); 
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);

#define GPIO_02_LED 2

Ticker Reset;

int NoOutput = 0;

void  Server_Header() {
//  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
//  server.sendHeader("Pragma", "no-cache");
//  server.sendHeader("Expires", "-1");
//  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
}

void  Reset_System() {
#ifdef Serial_on
  String Text = "";
  String Data = "";
  Data = milli2time(millis());
  Text = "watchdog Reset Timestamp = " + Data;
  Serial.println(Text);
  Serial.println("watchdog Reset");
#endif
  ESP.restart();
}

void  Reset_Reset() {
  Reset.detach();
  Reset.once(300, Reset_System); //reset ESP after 5 Minutes no action from Web
#ifdef Serial_on
  Serial.println("Reset watchdog");
#endif
}

void setup() {
  pinMode(GPIO_02_LED, OUTPUT);
  digitalWrite(GPIO_02_LED, LOW);
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  delay(10);
#ifdef Serial_on
  Serial.println();
  Serial.print("getResetReason = ");
  Serial.println(ESP.getResetReason());
  Serial.println("Starting ESP_SmartHome");
  Serial.println(VERSION);
#endif
  // Connect to WiFi network
#ifdef Serial_on
  Serial.println();
  Serial.print("Connecting to ");
#endif
//  WiFi.mode(WIFI_STA);
  WiFi.config(ip, dns, gateway, subnet); 
  WiFi.begin(ssid, password);
  wifi_station_set_hostname(wiFiHostname);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef Serial_on
    Serial.print(".");
#endif
  }
#ifdef Serial_on
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(ssid); 
  Serial.print("WiFi RSSI=");
  Serial.println(WiFi.RSSI());
#endif
  
  // Start the server
  server.begin();
#ifdef Serial_on
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
#endif

#ifdef BH1750_1_active
  BH1750_1_INIT();
#endif
#ifdef BME280_1_active
  BME280_1_INIT();
#endif
#ifdef BME280_2_active
  BME280_2_INIT();
#endif
#ifdef DS18B20_1_active
  DS18B20_1_INIT();
#endif
#ifdef DS18B20_2_active
  DS18B20_2_INIT();
#endif
#ifdef INA219_1_active
  INA219_1_INIT();
#endif
#ifdef MCP9808_1_active
  MCP9808_1_INIT();
#endif
#ifdef MCP9808_2_active
  MCP9808_2_INIT();
#endif
#ifdef PCF8574_1_active
  PCF8574_1_INIT();
#endif
#ifdef Rollo_1_active
  Rollo_1_INIT();
#endif
#ifdef Rollo_2_active
  Rollo_2_INIT();
#endif 
#ifdef SI1145_1_active
  SI1145_1_INIT();
#endif
#ifdef TSL2561_1_active
  TSL2561_1_INIT();
#endif
#ifdef VEML6070_1_active
  VEML6070_1_INIT();
#endif

  server.on("/", Root_handle);
  server.on("/info", Info_handle);
  server.on("/ping", Ping_handle);
  server.on("/time", Time_handle);
  server.onNotFound(handleNotFound);

  digitalWrite(GPIO_02_LED, HIGH);

  Reset.once(300, Reset_System); //reset ESP after 5 Minutes no action from Web
}
 
void loop() {
  server.handleClient();
}

void Root_handle() {
  String WebSide = "";
  String WebSideArgumentRead = "";
  String WebSideArgumentAction = "";
  String Data = "";
  String Text = "";
  
//  WebSideArgumentRead = "";
//  WebSideArgumentAction = "";
  WebSideArgumentRead = server.arg("read");
  WebSideArgumentAction = server.arg("action");
#ifdef Serial_on
  Data = milli2time(millis());
  Text = "Timestamp = " + Data;
  Serial.println(Text);
  Serial.print("WebSideArgumentRead = '");
  Serial.print(WebSideArgumentRead);
  Serial.println("'");
  Serial.print("WebSideArgumentAction = '");
  Serial.print(WebSideArgumentAction);
  Serial.println("'");
#endif
  if (WebSideArgumentRead == WiFi_RSSI_text) Text = WiFi_RSSI_handle(WiFi_RSSI_text);
  else if (WebSideArgumentRead == vdd33_text) Text = vdd33_handle(vdd33_text);
  else if (WebSideArgumentRead == UPTIME_text) Text = UPTIME_handle(UPTIME_text);
#ifdef BH1750_1_active
  else if (WebSideArgumentRead == BH1750_1_LUX_text) Text = BH1750_1_LUX_handle(BH1750_1_LUX_text);
#endif
#ifdef BME280_1_active
  else if (WebSideArgumentRead == BME280_1_ALT_text) Text = BME280_1_TEMP_handle(BME280_1_ALT_text);
  else if (WebSideArgumentRead == BME280_1_HYDRO_text) Text = BME280_1_HYDRO_handle(BME280_1_HYDRO_text); 
  else if (WebSideArgumentRead == BME280_1_PRESS_text) Text = BME280_1_PRESS_handle(BME280_1_PRESS_text);
  else if (WebSideArgumentRead == BME280_1_TEMP_text) Text = BME280_1_ALT_handle(BME280_1_TEMP_text);
#endif
#ifdef BME280_2_active
  else if (WebSideArgumentRead == BME280_2_ALT_text) Text = BME280_1_TEMP_handle(BME280_2_ALT_text);
  else if (WebSideArgumentRead == BME280_2_HYDRO_text) Text = BME280_1_HYDRO_handle(BME280_2_HYDRO_text); 
  else if (WebSideArgumentRead == BME280_2_PRESS_text) Text = BME280_1_PRESS_handle(BME280_2_PRESS_text);
  else if (WebSideArgumentRead == BME280_2_TEMP_text) Text = BME280_1_ALT_handle(BME280_2_TEMP_text);
#endif
#ifdef DS18B20_1_active
  else if (WebSideArgumentRead == DS18B20_1_TEMP_text) Text = DS18B20_1_TEMP_handle(DS18B20_1_TEMP_text);
#endif
#ifdef DS18B20_2_active
  else if (WebSideArgumentRead == DS18B20_2_TEMP_text) Text = DS18B20_2_TEMP_handle(DS18B20_2_TEMP_text);
#endif
#ifdef INA219_1_active
  else if (WebSideArgumentAction == INA219_1_shuntvoltage_text) Text = INA219_1_shuntvoltage_handle(INA219_1_shuntvoltage_text);
  else if (WebSideArgumentAction == INA219_1_busvoltage_text) Text = INA219_1_busvoltage_handle(INA219_1_busvoltage_text);
  else if (WebSideArgumentAction == INA219_1_current_mA_text) Text = INA219_1_current_mA_handle(INA219_1_current_mA_text);
  else if (WebSideArgumentAction == INA219_1_loadvoltage_text) Text = INA219_1_loadvoltage_handle(INA219_1_loadvoltage_text);
#endif
#ifdef MCP9808_1_active
  else if (WebSideArgumentRead == MCP9808_1_TEMP_text) Text = MCP9808_1_TEMP_handle(MCP9808_1_TEMP_text);
#endif
#ifdef MCP9808_2_active
  else if (WebSideArgumentRead == MCP9808_2_TEMP_text) Text = MCP9808_2_TEMP_handle(MCP9808_2_TEMP_text);
#endif
#ifdef PCF8574_1_active
  else if (WebSideArgumentRead == PCF8574_1_1_text) Text = PCF8574_1_handle(1, PCF8574_1_1_text);
  else if (WebSideArgumentRead == PCF8574_1_2_text) Text = PCF8574_1_handle(2, PCF8574_1_2_text);
  else if (WebSideArgumentRead == PCF8574_1_3_text) Text = PCF8574_1_handle(3, PCF8574_1_3_text);
  else if (WebSideArgumentRead == PCF8574_1_4_text) Text = PCF8574_1_handle(4, PCF8574_1_4_text);
  else if (WebSideArgumentRead == PCF8574_1_5_text) Text = PCF8574_1_handle(5, PCF8574_1_5_text);
  else if (WebSideArgumentRead == PCF8574_1_6_text) Text = PCF8574_1_handle(6, PCF8574_1_6_text);
  else if (WebSideArgumentRead == PCF8574_1_7_text) Text = PCF8574_1_handle(7, PCF8574_1_7_text);
  else if (WebSideArgumentRead == PCF8574_1_8_text) Text = PCF8574_1_handle(8, PCF8574_1_8_text);
#endif
#ifdef Rollo_1_active
  else if (WebSideArgumentAction == Rollo_1_Hoch_text) Text = Rollo_2_Hoch_handle(Rollo_1_Hoch_text);
  else if (WebSideArgumentAction == Rollo_1_Stop_text) Text = Rollo_2_Stop_handle(Rollo_1_Stop_text);
  else if (WebSideArgumentAction == Rollo_1_Runter_text) Text = Rollo_2_Runter_handle(Rollo_1_Runter_text);
#endif
#ifdef Rollo_2_active
  else if (WebSideArgumentAction == Rollo_2_Hoch_text) Text = Rollo_2_Hoch_handle(Rollo_2_Hoch_text);
  else if (WebSideArgumentAction == Rollo_2_Stop_text) Text = Rollo_2_Stop_handle(Rollo_2_Stop_text);
  else if (WebSideArgumentAction == Rollo_2_Runter_text) Text = Rollo_2_Runter_handle(Rollo_2_Runter_text);
#endif
#ifdef SI1145_1_active
  else if (WebSideArgumentAction == SI1145_1_IR_text) Text = SI1145_1_IR_handle(SI1145_1_IR_text);
  else if (WebSideArgumentAction == SI1145_1_UV_text) Text = SI1145_1_UV_handle(SI1145_1_UV_text);
  else if (WebSideArgumentAction == SI1145_1_VISIBLE_text) Text = SI1145_1_VISIBLE_handle(SI1145_1_VISIBLE_text);
#endif
#ifdef TSL2561_1_active
  else if (WebSideArgumentRead == TSL2561_1_LUX_text) Text = TSL2561_1_handle(TSL2561_1_LUX_text);
#endif
#ifdef VEML6070_1_active
  else if (WebSideArgumentRead == VEML6070_1_UV_text) Text = VEML6070_1_UV_handle(VEML6070_1_UV_text);
#endif
  else { Text = Root_Text(); }
#ifdef Serial_on
  Serial.println(Text);
#endif
  WebSide = WebSideStart + Text + WebSideEnd;
  Server_Header();
  server.send(200, WebSideType, WebSide);
  server.client().stop();
  Reset_Reset();
}

void Info_handle() {
  String WebSide = "";
  String WebSideArgumentRead = "";
  String WebSideArgumentAction = "";
  String Data = "";
  String Text = "";
  
  WebSide = WebSideStart;
  WebSide = WebSide + Root_Text();
  WebSide = WebSide + System_Text();
  WebSide = WebSide + Sensor_Text();
  
  WebSide = WebSide + WebSideEnd;
  Server_Header();
  server.send(200, WebSideType, WebSide);
  server.client().stop();
  Reset_Reset();
}

void Ping_handle() {
  String WebSide = "";
  String Text = "Ping OK";
#ifdef Serial_on
  Serial.println(Text);
#endif
  
#ifdef Serial_on
  Serial.println(Text);
#endif
  WebSide = WebSideStart + Text + WebSideEnd;
  Server_Header();
  server.send(200, WebSideType, WebSide);
  server.client().stop();
  Reset_Reset();
}

void Time_handle() {
  String WebSide = "";
  String Data = "";
  String Text = "";
  Data = milli2time(millis());
  Text = "UPTIME = " + Data;
  
#ifdef Serial_on
  Serial.println(Text);
#endif
  
#ifdef Serial_on
  Serial.println(Text);
#endif
  WebSide = WebSideStart + Text + WebSideEnd;
  Server_Header();
  server.send(200, WebSideType, WebSide);
  server.client().stop();
  Reset_Reset();
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  Server_Header();
  server.send(404, WebSideType, message);
}

/*
String MCP9808_1_TEMP_handle() {
  String Text = "";
  String Data = "";
  Data = "null";
#ifdef MCP9808_1_active    
  MCP9808_1.shutdown_wake(0);
  Data = MCP9808_1.readTempC();
  delay(250);
  MCP9808_1.shutdown_wake(1);
#endif 
//  Data = MCP9808_1_TEMP_GetData();
  Text = "TEMP4=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
#ifdef Serial_on
    Serial.println(Text);
#endif
  return Text;
}

// Temperatur Zimmer Kai sehr genau
String MCP9808_2_TEMP_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = "null";
#ifdef MCP9808_2_TEMP    
  MCP9808_2.shutdown_wake(0);
  Data = MCP9808_2.readTempC();
  delay(250);
  MCP9808_2.shutdown_wake(1);
#endif 
//  Data = MCP9808_2_TEMP_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
#ifdef Serial_on
    Serial.println(Text);
#endif
  return Text;
}
*/
