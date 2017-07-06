// Rollo_1.CPP
#ifdef Rollo_1_active
#include <Ticker.h>
int Rollo_1_time = 20; // in Sekunden
int Rollo_1_Pin_Hoch = 13; 
int Rollo_1_Pin_Runter = 12;
#define Rollo_1_direction_Stop 0
#define Rollo_1_direction_Hoch 1
#define Rollo_1_direction_Runter 2
int Rollo_1_direction = Rollo_1_direction_Stop; // 0 = Stop; 1 = Hoch; 2 = Runter 

Ticker Rollo_1_Ticker;

void  Rollo_1_off (void){
  Rollo_1_direction = Rollo_1_direction_Stop;
}
#endif

void Rollo_1_INIT(void)
{
#ifdef Rollo_1_active
  Serial.print("Rollo_1 Test.......");
  pinMode(Rollo_1_Pin_Hoch, OUTPUT);
  pinMode(Rollo_1_Pin_Runter, OUTPUT);
  digitalWrite(Rollo_1_Pin_Hoch, HIGH);
  digitalWrite(Rollo_1_Pin_Runter, HIGH);
  Serial.println("OK");
#endif
}

void Rollo_1_Hoch(void)
{
#ifdef Rollo_1_active
  Rollo_1_Ticker.once(Rollo_1_time, Rollo_1_off);
  digitalWrite(Rollo_1_Pin_Runter, HIGH);
  if(Rollo_1_direction == Rollo_1_direction_Runter)
  {
    digitalWrite(Rollo_1_Pin_Hoch, LOW);
    delay(500); 
    digitalWrite(Rollo_1_Pin_Hoch, HIGH);
  }
  if(Rollo_1_direction != Rollo_1_direction_Hoch)
  {
    digitalWrite(Rollo_1_Pin_Hoch, LOW);
    delay(500); 
    digitalWrite(Rollo_1_Pin_Hoch, HIGH);
  }
  Rollo_1_direction = Rollo_1_direction_Hoch;
#endif
}

void Rollo_1_Stop(void)
{
#ifdef Rollo_1_active
  Rollo_1_Ticker.detach();
  
  if(Rollo_1_direction == Rollo_1_direction_Runter)
  {
    digitalWrite(Rollo_1_Pin_Hoch, LOW);
    delay(500); 
    digitalWrite(Rollo_1_Pin_Hoch, HIGH);
  }
  
  if(Rollo_1_direction == Rollo_1_direction_Hoch)
  {
    digitalWrite(Rollo_1_Pin_Runter, LOW);
    delay(500); 
    digitalWrite(Rollo_1_Pin_Runter, HIGH);
    Rollo_1_direction = Rollo_1_direction_Runter;
  }
#endif
}

void Rollo_1_Runter(void)
{
#ifdef Rollo_1_active
  Rollo_1_Ticker.once(Rollo_1_time, Rollo_1_off);
  digitalWrite(Rollo_1_Pin_Hoch, HIGH);
  if(Rollo_1_direction == Rollo_1_direction_Hoch)
  {
    digitalWrite(Rollo_1_Pin_Runter, LOW);
    delay(500);
    digitalWrite(Rollo_1_Pin_Runter, HIGH); 
  }
  if(Rollo_1_direction == Rollo_1_direction_Runter)
  {
    digitalWrite(Rollo_1_Pin_Runter, LOW);
    delay(500);
    digitalWrite(Rollo_1_Pin_Runter, HIGH);
  }
  Rollo_1_direction = Rollo_1_direction_Runter;
#endif
}

String Rollo_1_HTML_GetData(void)
{
#ifdef Rollo_1_active
  String Text = "";
  Text = "<a href=\"?action=";
  Text = Text + Rollo_1_Hoch_text;
  Text = Text + "\"><button>Hoch</button></a>&nbsp;<a href=\"?action=";
  Text = Text + Rollo_1_Stop_text;
  Text = Text + "\"><button>Stop</button></a>&nbsp;<a href=\"?action=";
  Text = Text + Rollo_1_Runter_text;
  Text = Text + "\"><button>Runter</button></a>";
  return Text;
#else
  return "null";
#endif
}

String Rollo_1_HTML_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = Rollo_1_HTML_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String Rollo_1_Hoch_handle(String Label) {
  Rollo_1_Hoch();
  return "Rollo_1_Hoch";
} 
  
String Rollo_1_Stop_handle(String Label) {
  Rollo_1_Stop();
  return "Rollo_1_Stop";
} 

String Rollo_1_Runter_handle(String Label) {
  Rollo_1_Runter();
  return "Rollo_1_Runter";
} 
