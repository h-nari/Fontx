#ifndef ESP32

#include "FsFontx.h"

FsFontx::FsFontx(const char *f0,const char *f1,const char *f2) : Fontx()
{
  m_cFontx = 0;
  addFont(f0);
  addFont(f1);
  addFont(f2);
}

void FsFontx::addFont(const char *path)
{
  if(m_cFontx < FontxFileMax && path){
    m_aFontxFile[m_cFontx].path = path;
    m_aFontxFile[m_cFontx].opened = false;
    m_cFontx++;
  }
}

bool FsFontx::openFontxFile(FontxFile *ff)
{
  if(!ff->opened){
    ff->opened = true;
    fs::File f = SPIFFS.open(ff->path,"r");
    if(!f){
      ff->valid = false;
      Serial.printf("FsFontx:%s not found.\n",ff->path);
    } else {
      ff->file = f;
      char buf[18];

      f.readBytes(buf, sizeof buf);
      ff->w = buf[14];
      ff->h = buf[15];
      ff->is_ank = (buf[16] == 0);
      ff->bc = buf[17];
      ff->fsz = (ff->w + 7)/8 * ff->h;
      if(ff->fsz > FontxGlyphBufSize){
	Serial.println("too big font size.");
	ff->valid = false;
      } else {
	ff->valid = true;
      }
    }
  }
  return ff->valid;
}

void FsFontx::closeFontxFile(FontxFile *ff)
{
  if(ff->opened){
    ff->file.close();
    ff->opened = false;
  }
}


void FsFontx::closeFontxFile()
{
  for(int i=0; i<m_cFontx; i++)
    closeFontxFile(&m_aFontxFile[i]);
}

bool FsFontx::getGlyph (uint32_t ucode , const uint8_t **pGlyph,
			uint8_t *pw, uint8_t *ph)
{
  uint32_t sjis;

  if(ucode >= 0x100 && !uni2sjis(ucode, &sjis))
    return false;
  
  for(int i=0; i<m_cFontx; i++){
    FontxFile *ff = &m_aFontxFile[i];
    if(!openFontxFile(ff)) continue;
    
    if(ucode < 0x100){
      if(ff->is_ank){
	ff->file.seek(17 + ucode * ff->fsz, fs::SeekSet);
	ff->file.readBytes((char *)m_glyphBuf, ff->fsz);
	if(pGlyph) *pGlyph = m_glyphBuf;
	if(pw) *pw = ff->w;
	if(ph) *ph = ff->h;
	return true;
      }
    }
    else {
      if(!ff->file.seek(18, fs::SeekSet)){
	Serial.println("FsFontx::seek(18) failed.");
	continue;
      }
      uint16_t buf[2], nc = 0, bc = ff->bc;
    
      while(bc--){ 
	if(ff->file.readBytes((char *)buf, 4)!=4){
	  Serial.println("FsFontx::readBytes failed.");
	  continue;
	}

	if(sjis >= buf[0] && sjis <= buf[1]) {
	  nc += sjis - buf[0];
	  uint32_t pos = 18 + ff->bc * 4 + nc * ff->fsz;
	  if(!ff->file.seek(pos, fs::SeekSet)){
	    Serial.printf("FsFontx::seek(%u) failed.\n",pos);
	    break;
	  }
	  ff->file.readBytes((char *)m_glyphBuf, ff->fsz);
	  if(pGlyph) *pGlyph = m_glyphBuf;
	  if(pw) *pw = ff->w;
	  if(ph) *ph = ff->h;
	  return true;
	}
	nc += buf[1] - buf[0] + 1;
      }
    }
  }
  return false;
}

bool FsFontx::checkFontFile(bool verbose)
{
  for(int i=0; i<m_cFontx; i++){
    if(!openFontxFile(&m_aFontxFile[i])){
      if(verbose) dumpFileSystem();
      return false;
    }
  }
  return true;
}

void FsFontx::dumpFileSystem()
{
  fs::Dir dir = SPIFFS.openDir("/");
  int cnt = 0;
  while(dir.next()){
    fs::File f = dir.openFile("r");
    Serial.printf("[%d] %-12s %12u\n",++cnt,f.name(), f.size());
    f.close();
  }
  Serial.printf("%d files found.\n",cnt);
}

#endif // not defined(ESP32)
