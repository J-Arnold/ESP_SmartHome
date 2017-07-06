// Rollo_2.CPP
#ifdef Rollo_2_active
#include <Ticker.h>
int Rollo_2_time = 20; // in Sekunden
int Rollo_2_Pin_Hoch = 16;
int Rollo_2_Pin_Runter = 14;
#define Rollo_2_direction_Stop 0
#define Rollo_2_direction_Hoch 1
#define Rollo_2_direction_Runter 2
int Rollo_2_direction = Rollo_2_direction_Stop; // 0 = Stop; 1 = Hoch; 2 = Runter 

Ticker Rollo_2_Ticker;

void  Rollo_2_off (void){
  Rollo_2_direction = Rollo_2_direction_Stop;
}
#endif

void Rollo_2_INIT(void)
{
#ifdef Rollo_2_active
  Serial.print("Rollo_2 Test.......");
  pinMode(Rollo_2_Pin_Hoch, OUTPUT);
  pinMode(Rollo_2_Pin_Runter, OUTPUT);
  digitalWrite(Rollo_2_Pin_Hoch, HIGH);
  digitalWrite(Rollo_2_Pin_Runter, HIGH);
  Serial.println("OK");
#endif
}

void Rollo_2_Hoch(void)
{
#ifdef Rollo_2_active
  Rollo_2_Ticker.once(Rollo_2_time, Rollo_2_off);
  digitalWrite(Rollo_2_Pin_Runter, HIGH);
  if(Rollo_2_direction == Rollo_2_direction_Runter)
  {
    digitalWrite(Rollo_2_Pin_Hoch, LOW);
    delay(500); 
    digitalWrite(Rollo_2_Pin_Hoch, HIGH);
  }
  if(Rollo_2_direction != Rollo_2_direction_Hoch)
  {
    digitalWrite(Rollo_2_Pin_Hoch, LOW);
    delay(500); 
    digitalWrite(Rollo_2_Pin_Hoch, HIGH);
  }
  Rollo_2_direction = Rollo_2_direction_Hoch;
#endif
}

void Rollo_2_Stop(void)
{
#ifdef Rollo_2_active
  Rollo_2_Ticker.detach();
  
  if(Rollo_2_direction == Rollo_2_direction_Runter)
  {
    digitalWrite(Rollo_2_Pin_Hoch, LOW);
    delay(500); 
    digitalWrite(Rollo_2_Pin_Hoch, HIGH);
  }
  
  if(Rollo_2_direction == Rollo_2_direction_Hoch)
  {
    digitalWrite(Rollo_2_Pin_Runter, LOW);
    delay(500); 
    digitalWrite(Rollo_2_Pin_Runter, HIGH);
    Rollo_2_direction = Rollo_2_direction_Runter;
  }
#endif
}

void Rollo_2_Runter(void)
{
#ifdef Rollo_2_active
  Rollo_2_Ticker.once(Rollo_2_time, Rollo_2_off);
  digitalWrite(Rollo_2_Pin_Hoch, HIGH);
  if(Rollo_2_direction == Rollo_2_direction_Hoch)
  {
    digitalWrite(Rollo_2_Pin_Runter, LOW);
    delay(500);
    digitalWrite(Rollo_2_Pin_Runter, HIGH); 
  }
  if(Rollo_2_direction == Rollo_2_direction_Runter)
  {
    digitalWrite(Rollo_2_Pin_Runter, LOW);
    delay(500);
    digitalWrite(Rollo_2_Pin_Runter, HIGH);
  }
  Rollo_2_direction = Rollo_2_direction_Runter;
#endif
}

String Rollo_2_HTML(void)
{
#ifdef Rollo_2_active
  String Text = "";
  Text = "<a href=\"?action=HOCH2\"><button>Hoch</button></a>&nbsp;<a href=\"?action=STOP2\"><button>Stop</button></a>&nbsp;<a href=\"?action=RUNTER2\"><button>Runter</button></a>";
  return Text;
#else
  return "null";
#endif
}

String Rollo_2_HTML_GetData(void)
{
#ifdef Rollo_2_active
  String Text = "";
  Text = "<a href=\"?action=";
  Text = Text + Rollo_2_Hoch_text;
  Text = Text + "\"><button>Hoch</button></a>&nbsp;<a href=\"?action=";
  Text = Text + Rollo_2_Stop_text;
  Text = Text + "\"><button>Stop</button></a>&nbsp;<a href=\"?action=";
  Text = Text + Rollo_2_Runter_text;
  Text = Text + "\"><button>Runter</button></a>";
  return Text;
#else
  return "null";
#endif
}

String Rollo_2_HTML_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = Rollo_2_HTML_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String Rollo_2_Hoch_handle(String Label) {
  Rollo_2_Hoch();
  return "Rollo_2_Hoch";
} 
  
String Rollo_2_Stop_handle(String Label) {
  Rollo_2_Stop();
  return "Rollo_2_Stop";
} 

String Rollo_2_Runter_handle(String Label) {
  Rollo_2_Runter();
  return "Rollo_2_Runter";
} 
