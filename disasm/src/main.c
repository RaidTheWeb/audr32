#include <stdio.h>

#include "disasm.h"

void printpointer(disasmstate_t *state) {
    uint8_t data = *((uint8_t *)(state->program + (state->ip++)));
    uint32_t addr = *((uint32_t *)(state->program + ((state->ip += 4) - 4)));
    int16_t offset = *((int16_t *)(state->program + ((state->ip += 2) - 2)));
    switch((data & 0xF0) >> 4) {
        case PTR_8BIT:
        case PTR_8BITREG: printf("[byte:"); break;
        case PTR_16BIT:
        case PTR_16BITREG: printf("[word:"); break;
        case PTR_32BIT:
        case PTR_32BITREG: printf("[dword:"); break;
    }

    if((data & 0xF0) >> 4) printf("%s", REG_NAMES[data & 0x0F]);
    else printf("0x%08x", addr);

    if(offset != 0) printf(":%d]", offset);
    else printf("]");
}

void printimm(disasmstate_t *state) {
    uint32_t imm = *((uint32_t *)(state->program + ((state->ip += 4) - 4)));
    printf("0x%08x", imm);
}

void printreg(disasmstate_t *state) {
    uint8_t reg = *((uint8_t *)(state->program + (state->ip++)));
    printf("%s", REG_NAMES[reg]); 
}

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Usage: %s: [file]\n", CBINNAME);
        return 1;
    }

    disasmstate_t state = (disasmstate_t) { .ip = 0, .program = NULL };

    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        printf("Error: Failed to open input binary.\n");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    uint64_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    state.program = (uint8_t *)malloc(size);
    fread(state.program, size, 1, f);
    fclose(f);

    while(state.ip < size) {
        printf("0x%08x: ", state.ip);
        uint8_t opdata = *((uint8_t *)(state.program + (state.ip++)));
        printf("%s ", OP_NAMES[(opdata & 0xF0) >> 4]); 

        switch(opdata & 0x0F) {
            case MODE_PTRIMM:
                printpointer(&state);
                printf(", ");
                printimm(&state);
                break;
            case MODE_PTRREG:
                printpointer(&state);
                printf(", ");
                printreg(&state);
                break;
            case MODE_REGIMM:
                printreg(&state);
                printf(", ");
                printimm(&state);
                break;
            case MODE_REGPTR:
                printreg(&state);
                printf(", ");
                printpointer(&state);
                break;
            case MODE_REGREG:
                printreg(&state);
                printf(", ");
                printreg(&state);
                break;
            case MODE_IMMIMM:
                printimm(&state);
                printf(", ");
                printimm(&state);
                break;
            case MODE_IMM:
                printimm(&state);
                break;
        }
        printf("\n");
    }

    return 0;
}
