// ESP_SmartHome.h

//declaring prototypes ESP_SmartHome
void Server_Header(void);
void Root_handle(void);
void Info_handle(void);
void Ping_handle(void);
void Time_handle(void);
void handleNotFound(void);

//declaring prototypes BASIC_MODULES.CPP
String milli2time(unsigned long mSekunden);
String WiFi_RSSI_handle(String Label);
String Version_handle(String Label);
String vdd33_handle(String Label);
String UPTIME_handle(String Label);
String Root_Text(void);
String Sensor_Text(void);
