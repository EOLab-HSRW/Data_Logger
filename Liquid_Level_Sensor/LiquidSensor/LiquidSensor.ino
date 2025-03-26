#include "liquidsensor.h"
#include <Arduino.h>  

void setup()
{
  liquidsensor_init();

	// Initialize Serial for debug output
	time_t timeout = millis();
	Serial.begin(115200);
	while (!Serial)
	{
		if ((millis() - timeout) < 5000)
		{
            delay(100);
        }
        else
        {
            break;
        }
	}
}

void loop()
{

  String result = "Ergebnis der Messung in mAh"+String(getCurrent());
  Serial.println(result.c_str());
  delay(3000);
}
