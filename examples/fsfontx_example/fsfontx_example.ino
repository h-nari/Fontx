#include "conf.h"

#if USE_OTA
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ota_util.h"
#endif


#include <FS.h>
#include <Fontx.h>
#include <FsFontx.h>

FsFontx fx("/ILGH16XB.FNT","/ILGZ16XB.FNT");

void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println("\nReset:");

#if USE_OTA
	WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print('.');
	}
	Serial.println();
	Serial.print("IP: ");
	Serial.println(WiFi.localIP());

  static int8_t ota_col;
  ota_init();
#endif
	
#if 1
	if(!SPIFFS.begin())
		Serial.println("SPIFFS failed.");
	else {
		Dir dir = SPIFFS.openDir("/");
		int cnt = 0;
		while(dir.next()){
			File f = dir.openFile("r");
			Serial.printf("[%d] %-12s %12u\n",++cnt,f.name(), f.size());
			f.close();
		}
		Serial.printf("%d files found.\n",cnt);
	}
#endif
	const uint8_t *p;
	uint8_t w,h;
	uint16_t str[] = {u'漢',u'字',u'T',u'E',u'S',u'T'};

	for(int i=0;i<sizeof(str)/sizeof(str[0]);i++){
		if(!fx.getGlyph(str[i], &p, &w, &h)){
			Serial.printf("getGlyph failed. code:%x\n",str[i]);
		} else {
			for(int y=0; y<h; y++){
				Serial.printf("%02d: ",y);
				for(int x=0; x<w; x++){
					Serial.print(p[x/8] & (0x80 >> (x % 8)) ? '*' : '.'); 
				}
				Serial.println();
				p += (w + 7)/8;
			}
		}
	}
	
}

void loop()
{
#if USE_OTA
  ArduinoOTA.handle();
#endif
}
    
/*** Local variables: ***/
/*** tab-width:2 ***/
/*** End: ***/
