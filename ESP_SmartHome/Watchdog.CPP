// Watchdog.CPP

//declaring prototypes
void  Watchdog_Reset(void);
void  Reset_Watchdog(void);
String Watchdog_Next_Reset_GetData(void);
String Watchdog_Next_Reset_handle(String Label);

#ifdef Watchdog_active
//Setup Watchdog timer
#include <Ticker.h>
//reset ESP after 5 Minutes no action from Web
const int Watchdog_Time = 60*5; //in sec
int Last_Watchdog_Reset;
Ticker Watchdog;
#endif

void Watchdog_Reset(void) {
#ifdef Watchdog_active
#ifdef Serial_on
  String Text = "";
  String Data = "";
  Data = milli2time(millis());
  Text = "Watchdog Reset Timestamp = " + Data;
  Serial.println(Text);
  Serial.println("Watchdog Reset");
#endif
  ESP.restart();
#endif
}

void Reset_Watchdog(void) {
#ifdef Watchdog_active
  Watchdog.detach();
  Watchdog.once(Watchdog_Time, Watchdog_Reset);
  Last_Watchdog_Reset = millis();
#ifdef Serial_on
  Serial.println("Reset watchdog");
#endif
#endif
}

String Watchdog_Next_Reset_GetData(void)
{
#ifdef Watchdog_active
  String Text = "";
  Text = milli2time((Last_Watchdog_Reset + (Watchdog_Time * 1000)) - millis());
  return Text;
#else
  return "null";
#endif
}

String Watchdog_Next_Reset_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = Watchdog_Next_Reset_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
