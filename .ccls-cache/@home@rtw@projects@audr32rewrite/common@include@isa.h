#ifndef __ISA_H__
#define __ISA_H__

#include <stdint.h>

// common ISA details. (registers, instructions, modes, memory maps, etc.)

enum {
    REG_R0  = 0x0,
    REG_R1  = 0x1,
    REG_R2  = 0x2,
    REG_R3  = 0x3,
    REG_R4  = 0x4,
    REG_R5  = 0x5,
    REG_R6  = 0x6,
    REG_R7  = 0x7,
    REG_R8  = 0x8,
    REG_R9  = 0x9,
    REG_R10 = 0xA,
    REG_R11 = 0xB,
    REG_R12 = 0xC,
    REG_R13 = 0xD,
    REG_R14 = 0xE,
    REG_R15 = 0xF,

    REG_MAX
};

#define REG_NAMES ((char *[]) { "r0", "r1", "r2", "r3", "r4", "r5", "r6", \
                                "r7", "r8", "r9", "r10", "r11", "r12",    \
                                "r13", "r14", "r15" })

#define REG_AC REG_R0
#define REG_BS REG_R1
#define REG_CR REG_R2
#define REG_DA REG_R3
#define REG_BP REG_R4
#define REG_SP REG_R5
#define REG_IP REG_R6

enum {
    OP_MOV  = 0x0, // move data between two locations
    OP_ADD  = 0x1, // add operands
    OP_ADC  = 0x2, // add operands with carry
    OP_SUB  = 0x3, // subtract operands
    OP_SBB  = 0x4, // subtract operands with borrow
    OP_AND  = 0x5, // logical AND operands
    OP_OR   = 0x6, // logical OR operands
    OP_NOR  = 0x7, // logical NOR operands
    OP_SHL  = 0x8, // shift operand left by operand
    OP_SHR  = 0x9, // shift operand right by operand
    OP_CMP  = 0xA, // compare operands
    OP_JNZ  = 0xB, // jump if ZF not set
    OP_LEA  = 0xC, // load effective pointer address
    OP_INT  = 0xD  // trigger interrupt
};

#define OP_NAMES ((char *[]) { "mov", "add", "adc", "sub", "sbb", "and", "or", "nor", "shl", "shr", "cmp", "jnz", "lea", "int" })

enum {
    MODE_PTRIMM = 0x0,
    MODE_PTRREG = 0x1,
    MODE_REGIMM = 0x2,
    MODE_REGPTR = 0x3,
    MODE_REGREG = 0x4,
    MODE_IMMIMM = 0x5,
    MODE_IMM    = 0x6
};

enum {
    PTR_8BIT        = 0x0,
    PTR_16BIT       = 0x1,
    PTR_32BIT       = 0x2,
    PTR_8BITREG     = 0x3,
    PTR_16BITREG    = 0x4,
    PTR_32BITREG    = 0x5
};

typedef struct {
    uint32_t start;
    uint32_t end;
} mmapentry_t;

#define MMAP_CR     ((mmapentry_t) { .start = 0x0,      .end = 0x40 })
#define MMAP_IO     ((mmapentry_t) { .start = 0x40,     .end = 0x440 })
#define MMAP_ROM    ((mmapentry_t) { .start = 0x440,    .end = 0x80440 })
#define MMAP_RAM    ((mmapentry_t) { .start = 0x80440,  .end = 0xFFFFFFFF })

#define ROM_SIZE    (0x80000)

#define CR_PTA      0x0
#define CR_ITA      0x4
#define CR_FLAGS    0x8
#define CR_EXCE     0x9
#define CR_BSTR     0xA

#define FLAG_ZF     0x0 // Zero
#define FLAG_CF     0x1 // Carry
#define FLAG_OF     0x2 // Overflow
#define FLAG_SF     0x3 // Sign
#define FLAG_IF     0x4 // Interrupts
#define FLAG_CXF    0x5 // Context
#define FLAG_HF     0x6 // Halt

#define EMU_SETFLAG(inst, flagn, value) ({ inst->flag ^= (-value ^ inst->flag) & (0x1 << flagn); (inst->flag >> flagn) & 0x1; })
#define EMU_GETFLAG(inst, flagn) ((inst->flag >> flagn) & 0x1)

#endif
