#ifndef _uni2sjis_h
#define _uni2sjis_h

#ifdef __cplusplus
extern "C" {
#endif

#include <pgmspace.h>
#include "result.h"
#include "stdint.h"

typedef struct {
  uint16_t uni;
  uint16_t sjis;
} cnv_t;

extern const cnv_t uni2sjis_tbl[];
extern const int uni2sjis_max;
result_t uni2sjis(uint32_t ucode, uint32_t *pScode);

#ifdef __cplusplus
}
#endif
#endif /* _uni2sjis_h */
