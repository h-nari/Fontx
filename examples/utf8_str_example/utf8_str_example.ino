#include <Fontx.h>
#include <Utf8Decoder.h>
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
	char *str = "半角ｶﾅ";

	Utf8Decoder d;
	uint32_t ucode;
	
	for(char *s = str; *s; s++){
		if(d.decode(*s, &ucode)){
			if(!fx.getGlyph(ucode, &p, &w, &h)){
				Serial.printf("getGlyph failed. code:%x\n",ucode);
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
}

void loop()
{
}
    
/*** Local variables: ***/
/*** tab-width:2 ***/
/*** End: ***/
