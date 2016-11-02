#include "uni2sjis.h"

result_t uni2sjis(uint32_t ucode, uint32_t *pScode)
{
  uint32_t c_min = 0;
  uint32_t c_max = uni2sjis_max - 1;

  while(c_min <= c_max){
    int c = (c_min + c_max) / 2;
    if(ucode < pgm_read_word(&uni2sjis_tbl[c].uni))
      c_max = c - 1;
    else if(ucode > pgm_read_word(&uni2sjis_tbl[c].uni))
      c_min = c + 1;
    else {
      *pScode = pgm_read_word(&uni2sjis_tbl[c].sjis);
      return r_ok;
    }
  }
  return r_error;
}

