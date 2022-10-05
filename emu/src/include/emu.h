#ifndef __EMU_H__
#define __EMU_H__

#include <stdlib.h>

#include "inccommon.h"

#include COMMON(isa.h)

typedef struct {
    uint8_t *ram;
    uint8_t rom[ROM_SIZE];

    uint32_t regs[REG_MAX];

    // Control registers
    uint32_t pta; // page table address
    uint32_t ita; // interrupt table address
    uint8_t flags; // flags register
    uint8_t execc; // exceptions 
} cpuinstance_t;

#endif
