#ifndef __EMU_H__
#define __EMU_H__

#include <pthread.h>
#include <stdlib.h>

#include "inccommon.h"

#include COMMON(isa.h)
#include COMMON(list.h)

// per-instance resources.
typedef struct {
    // multi-core information
    pthread_t tid;
    int cid;

    uint32_t regs[REG_MAX];

    // Control registers
    uint32_t pta; // page table address
    uint32_t ita; // interrupt table address
    uint8_t flag; // flags register
    uint8_t exec; // exceptions 
    uint8_t bootstrapped; // active? (SMP)
} cpuinstance_t;

// shared resources.
typedef struct {
    int running;

    // we shouldn't have to worry about CPU instances overwriting each other on the emulator level. It's up to the user to handle memory locks to prevent data overwrites. (Either way, by the stage that we have multiple CPUs bootstrapped and running on code, we'd of already reached user code that could in theory implement these locks)

    uint8_t *ram; // dynamically allocated, up to 3.9GB un-paged physical memory (counting for the exclusion of memory mapped addresses).
    uint8_t rom[ROM_SIZE]; // 512KB (should probably reduce this) 
    LIST_TYPE(cpuinstance_t *) cpus; // cpu instances
} sharedemu_t;

extern sharedemu_t *shared;

/**
 * Translate virtual addresses to physical addresses according to pagemap.
 *
 * @param cpu CPU instance.
 * @param virt Virtual address.
 * @param phys Physical address.
 * @param iswrite Are we writing to this location? if so, check for write permissions.
 *
 * @returns Translation success.
 */
int emu_virtphys(cpuinstance_t *cpu, uint32_t virt, uint32_t *phys, int iswrite);
/**
 * Write Memory address.
 *
 * @param cpu CPU instance.
 * @param addr Physical address to write to.
 * @param src Source data.
 * @param length Data length to write.
 *
 * @returns Write success.
 */
int emu_write(cpuinstance_t *cpu, uint32_t addr, uint32_t src, uint32_t length);
/**
 * Read memory address.
 *
 * @param cpu CPU instance.
 * @param addr Physical address to read from.
 * @param dest Destination pointer.
 * @param length Data length to read.
 *
 * @returns Read success.
 */
int emu_read(cpuinstance_t *cpu, uint32_t addr, uint32_t *dest, uint32_t length);
/**
 * Run CPU cycles.
 *
 * @param cpu CPU instance.
 * @param cycles CPU cycles to run.
 *
 * @returns Cycles we did.
 */
uint32_t emu_docycles(cpuinstance_t *cpu, uint32_t cycles);
/**
 * Initialise emulator
 *
 * @param bootrom ROM image.
 * @param ramsize Amount of RAM to allocate.
 * @param cpucount Number of CPUs for multi-processing.
 */
void emu_init(char *bootrom, uint64_t ramsize, int cpucount);

#endif
