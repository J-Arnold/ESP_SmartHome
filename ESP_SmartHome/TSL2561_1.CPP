// TSL2561_1.CPP
#ifdef TSL2561_1_active
#include <Adafruit_TSL2561_U.h>

// The address will be different depending on whether you leave
// the ADDR pin float (addr 0x39), or tie it to ground or vcc. In those cases
// use TSL2561_ADDR_LOW (0x29) or TSL2561_ADDR_HIGH (0x49) respectively
Adafruit_TSL2561_Unified TSL2561 = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 12345);
#endif

/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2561
*/
/**************************************************************************/
void TSL2561_1_INIT(void)
{
#ifdef TSL2561_1_active
  Serial.print("TSL2561_1 Test.....");
  if(!TSL2561.begin())
  {
    Serial.println("no TSL2561_LUX detected!");
  } else {
  /* You can also manually set the gain or enable auto-gain support */
    // TSL2561.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
    // TSL2561.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
    TSL2561.enableAutoRange(true);          /* Auto-gain ... switches automatically between 1x and 16x */

    /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
    // TSL2561.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);   /* fast but low resolution */
    // TSL2561.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
    TSL2561.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);     /* 16-bit data but slowest conversions */
    Serial.println("OK");

    /* Update these values depending on what you've set above! */  
    Serial.println("------------------------------------");
    Serial.print  ("Gain:         "); Serial.println("Auto");
    Serial.print  ("Timing:       "); Serial.println("402 ms");
    Serial.println("------------------------------------");
  }
#endif
}

String TSL2561_1_GetData(void)
{
#ifdef TSL2561_1_active
  String Text = "";
  sensors_event_t event;
  TSL2561.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);
  TSL2561.getEvent(&event);
 
  if (event.light) 
  {
    Text = String(event.light);
  }
  else
  {
    TSL2561.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);
    TSL2561.getEvent(&event);
    if (event.light) 
    {
      Text = String(event.light);
    }
    else
    {
      TSL2561.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
      TSL2561.getEvent(&event);
      if (event.light) 
      { 
        Text = String(event.light);      
      }
      else
      {
        Text = "Sensor overload";
      }
    }
  }
  return Text;
#else
  return "null";
#endif
}


String TSL2561_1_handle(String Label) {
  String Text = "";
  String Data = "";
  Data = TSL2561_1_GetData();
  if(Data == "Sensor overload")
  {
    Data = "0.00";
  } 
  Text = Label + "=" + Data;
  if(Data == "null")
  {
//    Text = "";
  }
  return Text;
}

#ifdef noting
/* Get a new sensor event */ 
  sensors_event_t event;
  tsl.getEvent(&event);
  
/* Display the results (light is measured in lux) */ 
  if (event.light) 
  {
    Text = "LUX=";
    Text.concat(String(event.light));
  }
  else
  {
/* If event.light = 0 lux the sensor is probably saturated
   and no reliable data could be generated! */
    Text = "Sensor overload";
  }
  Text.toCharArray(CText, 20);
  sendStrXY(CText, ln++, 0);
  Serial.println(Text);

uint16_t broadband = 0;
uint16_t infrared = 0;

/* Populate broadband and infrared with the latest values */
getLuminosity (&broadband, &infrared);
#endif
