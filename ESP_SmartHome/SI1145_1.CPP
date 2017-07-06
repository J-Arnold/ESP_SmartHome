// SI1145_1.CPP
#ifdef SI1145_1_active

#include <BH1750.h>

#include "Adafruit_SI1145.h"
Adafruit_SI1145 SI1145_1 = Adafruit_SI1145();

#endif
/*************************************************** 
  This is a library for the Si1145 UV/IR/Visible Light Sensor

  Designed specifically to work with the Si1145 sensor in the
  adafruit shop
  ----> https://www.adafruit.com/products/1777

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

void SI1145_1_INIT(void)
{
#ifdef SI1145_1_active
  Serial.print(F("SI1145_1 Test......"));
  if (! SI1145_1.begin()) {
    Serial.println("Fail");
  } else {
    Serial.println("OK");
  } 
#endif
}

/*
  Serial.print("Vis: "); Serial.println(uv.readVisible());
  Serial.print("IR: "); Serial.println(uv.readIR());
  
  // Uncomment if you have an IR LED attached to LED pin!
  //Serial.print("Prox: "); Serial.println(uv.readProx());

  float UVindex = uv.readUV();
  // the index is multiplied by 100 so to get the
  // integer index, divide by 100!
  UVindex /= 100.0;  
  Serial.print("UV: ");  Serial.println(UVindex);
*/

String SI1145_1_VISIBLE_GetData(void)
{
#ifdef SI1145_1_active
  String Text = "";
 Text = SI1145_1.readVisible();
  return Text;
#else
  return "null";
#endif
}

String SI1145_1_VISIBLE_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = SI1145_1_VISIBLE_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String SI1145_1_IR_GetData(void)
{
#ifdef SI1145_1_active
  String Text = "";
 Text = SI1145_1.readIR();
  return Text;
#else
  return "null";
#endif
}

String SI1145_1_IR_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = SI1145_1_IR_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

String SI1145_1_UV_GetData(void)
{
#ifdef SI1145_1_active
  String Text = "";
// the index is multiplied by 100 so to get the
// integer index, divide by 100!
 Text = SI1145_1.readUV()/100;
  return Text;
#else
  return "null";
#endif
}

String SI1145_1_UV_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = SI1145_1_UV_GetData();
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}
