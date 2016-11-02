#ifndef _fontx_h_
#define _fontx_h_

#include <Arduino.h>

#ifndef IMPORT_BIN
#define IMPORT_BIN(file,sym) asm (					\
				  ".section \".irom.text\"\n"		\
				  ".balign 4\n"				\
				  ".global " #sym "\n"			\
				  #sym ":\n"				\
				  ".incbin \"" file "\"\n"		\
				  ".global sizeof_" #sym "\n"		\
				  ".set _sizeof_" #sym ", . - " #sym "\n" \
				  ".balign 4\n"				\
				  ".section \".text\"\n")
#endif /* IMPORT_BIN */
#define FontxFileMax	3

class Fontx {
 public:
  int8_t m_spaceX;
  int8_t m_spaceY;
 protected:
  uint8_t  m_cFontx;
  uint8_t *m_aFontx[FontxFileMax];
  
 public:
  Fontx();
  bool getGlyph (uint16_t code , const uint8_t **pGlyph,
		 uint8_t *pw, uint8_t *ph);
  bool isValid() {return m_cFontx > 0;}
  void resetFontx(void);
  void addFontx(uint8_t *fontx);
  void setFontx(uint8_t *f0, uint8_t *f1=NULL, uint8_t *f2=NULL);

 protected:
  void process_utf8_byte(uint8_t c, int16_t *pX, int16_t *pY, bool bDraw=true,
			 int16_t *pX2=NULL);
  bool getFont(uint16_t code, const uint8_t **pFont);
  
};


#endif /* _fontx_h_ */
