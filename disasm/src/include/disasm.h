#ifndef __DISASM_H__
#define __DISASM_H__

#include <stdlib.h>

#include "inccommon.h"

#include COMMON(isa.h)

typedef struct {
    uint32_t ip;

    uint8_t *program;
} disasmstate_t;

#endif
