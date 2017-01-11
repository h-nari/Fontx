#include "ota_util.h"
#include "conf.h"

#if USE_OTA

static int8_t ota_col;

void ota_init()
{
#ifdef OTA_PORT
  ArduinoOTA.setPort(OTA_PORT);
#endif
#ifdef OTA_HOSTNAME
  ArduinoOTA.setHostname(OTA_HOSTNAME);
#endif
#ifdef OTA_PASSWORD
  ArduinoOTA.setPassword(OTA_PASSWORD);
#endif
  ArduinoOTA.onStart([](){
      Serial.println("start");
      ota_col = 0;
    });
  ArduinoOTA.onEnd([](){
      Serial.println("\nEnd");
    });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total){
      Serial.print('.');
      if(++ota_col >= 50){
	Serial.println();
	ota_col = 0;
      }
    });
  ArduinoOTA.onError([](ota_error_t error){
      Serial.printf("Error[%u]: ", error);
      if(error == OTA_AUTH_ERROR)
	Serial.println("Auth Failed");
      else if(error == OTA_BEGIN_ERROR)
	Serial.println("Begin Failed,code size too big?");
      else if(error == OTA_CONNECT_ERROR)
	Serial.println("Connect Failed");
      else if(error == OTA_RECEIVE_ERROR)
	Serial.println("Receive Failed");
      else if(error == OTA_END_ERROR)
	Serial.println("End Failed");
    });
  ArduinoOTA.begin();
}
#endif

