#ifndef _fs_fontx_h_
#define _fs_fontx_h_

#include <Fontx.h>
#include <FS.h>
#include "uni2sjis.h"

#ifndef FontxGlyphBufSize
#define FontxGlyphBufSize	(32*32/8)
#endif

struct FontxFile {
  const char *path;
  bool  opened;
  bool  valid;
  bool  is_ank;
  uint8_t w,h;
  uint16_t fsz;
  uint8_t  bc;
  File file;
};

class FsFontx : public Fontx {
 protected:
  uint8_t  m_cFontx;
  FontxFile m_aFontxFile[FontxFileMax];
  uint8_t  m_glyphBuf[FontxGlyphBufSize];
  
 public:
  FsFontx(const char *f0,const char *f1=NULL,const char *f2=NULL);
  void closeFontxFile();
  bool getGlyph (uint32_t ucode , const uint8_t **pGlyph,
		 uint8_t *pw, uint8_t *ph) override;
  bool checkFontFile(bool verbose=false);
  static void dumpFileSystem();

 protected:
  void addFont(const char *path);
  bool openFontxFile(FontxFile *ff);
  void closeFontxFile(FontxFile *ff);
};

#endif /* _fs_fontx_h_ */
