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
#ifndef FontxFileMax
#define FontxFileMax	3
#endif

class Fontx {
 public:
  virtual bool getGlyph (uint32_t code , const uint8_t **pGlyph,
			 uint8_t *pw, uint8_t *ph) = 0;
};

class RomFontx : public Fontx {
 protected:
  uint8_t  m_cFontx;
  const uint8_t *m_aFontx[FontxFileMax];
  
 public:
  RomFontx();
  RomFontx(const uint8_t *f0,const uint8_t *f1=NULL,const uint8_t*f2=NULL);
  bool getGlyph (uint32_t code , const uint8_t **pGlyph,
		 uint8_t *pw, uint8_t *ph) override;
  void resetFontx(void);
  void addFontx(const uint8_t *fontx);
  void setFontx(const uint8_t *f0,const uint8_t *f1=NULL,const uint8_t*f2=NULL);
};


#endif /* _fontx_h_ */
