#ifndef _utf8_decoder_h
#define _utf8_decoder_h

#include <stdint.h>

#define UTF8_BYTE_MAX	6

class Utf8Decoder {
 private:
  uint8_t m_clen;
  uint8_t m_wi;
  uint8_t m_buf[UTF8_BYTE_MAX];

 public:
  Utf8Decoder();
  void init();
  bool decode(uint8_t c, uint32_t *ucode);

 protected:
  bool error(uint8_t c, const char *mes);

};

#endif /* _utf8_decoder_h */
