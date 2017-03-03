#include <FS.h>
#include <Fontx.h>
#include <fontx/ILGH16XB.h>
#include <fontx/ILGZ16XB.h>

RomFontx fx(ILGH16XB,ILGZ16XB);

void setup()
{
  Serial.begin(115200);
  delay(100); 
  Serial.println("\nReset:");

	const uint8_t *p;
	uint8_t w,h;
	uint16_t str[] =
		{ 0x6f22, // unicode of '漢'
			0x5b57, // unicode of '字'
			u'T',u'E',u'S',u'T'};

	for(int i=0;i<sizeof(str)/sizeof(str[0]);i++){
		if(!fx.getGlyph(str[i], &p, &w, &h)){
			Serial.printf("getGlyph failed. code:%x\n",str[i]);
		} else {
			for(int y=0; y<h; y++){
				Serial.printf("%02d: ",y);
				for(int x=0; x<w; x++){
					uint8_t d = pgm_read_byte(&p[x/8]);
					Serial.print(d & (0x80 >> (x % 8)) ? '*' : '.'); 
				}
				Serial.println();
				p += (w + 7)/8;
			}
		}
	}
}

void loop()
{
}
    
/*** Local variables: ***/
/*** tab-width:2 ***/
/*** End: ***/
