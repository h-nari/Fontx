#include "Utf8Decoder.h"

Utf8Decoder::Utf8Decoder()
{
  init();
}

void Utf8Decoder::init()
{
  m_wi = m_clen = 0;
}

bool Utf8Decoder::error(uint8_t c, const char *mes)
{
  return false;
}

bool Utf8Decoder::decode(uint8_t c, uint32_t *ucode)
{
  if(m_wi == 0){
    if(~c & 0x80) {
      *ucode = c & 0x7f;
      return true;
    }
    else if(~c & 0x40)
      return error(c,"b6 must be 1 in first byte");
    else if(~c & 0x20)
      m_clen = 2;
    else if(~c & 0x10)
      m_clen = 3;
    else if(~c & 0x08)
      m_clen = 4;
    else if(~c & 0x04)
      m_clen = 5;
    else if(~c & 0x02)
      m_clen = 6;
    m_buf[m_wi++] = c;
  }
  else {
    if(~c & 0x80)		
      return error(c,"b7 must be 1 in following bytes");
    if( c & 0x40)		
      return error(c,"b6 must be 0 in following bytes");
    if(m_wi < m_clen)
      m_buf[m_wi++] = c;
    else
      return error(c,"too long data");

    if(m_wi == m_clen){
      int i;
      uint32_t mask = (1 << (7 - m_clen))-1;
      uint32_t cc = m_buf[0] & mask;

      for(i=1; i<m_clen; i++){
	cc <<= 6;
	cc |= m_buf[i] & 0x3f;
      }
      *ucode = cc;
      m_wi = 0;
      return true;
    }
  }
  return false;
}
