#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emu.h"

sharedemu_t *shared = NULL;

static void emu_fde(cpuinstance_t *us) {
    printf(us->cid == 0 ? "hello from base core!\n" : "hello!\n");

    
}

void emu_init(char *bootrom, uint64_t ramsize, int cpucount) {
    shared = (sharedemu_t *)malloc(sizeof(sharedemu_t));

    FILE *bootptr = fopen(bootrom, "r");

    if(bootptr == NULL) {
        printf("Failed to open boot rom.\n");
        exit(1);
    }

    fseek(bootptr, 0, SEEK_END);
    uint64_t romimagesize = ftell(bootptr);
    fseek(bootptr, 0, SEEK_SET);

    fread(shared->rom, romimagesize, 1, bootptr); // read data into ROM
    fclose(bootptr);

    shared->cpus = (typeof(shared->cpus))LIST_INIT;
    shared->ram = (uint8_t *)malloc(ramsize);
    
    for(int i = 0; i < cpucount; i++) {
        cpuinstance_t *inst = (cpuinstance_t *)malloc(sizeof(cpuinstance_t));
        memset(inst->regs, 0, sizeof(inst->regs)); // zero out registers

        inst->cid = i;
        inst->ita = 0;
        inst->pta = 0;
        inst->exec = -1;
        inst->flag = 0;
        EMU_SETFLAG(inst, FLAG_IF, 1); // enable interrupts by default
        LIST_PUSHBACK(&shared->cpus, inst);

        pthread_create(&inst->tid, NULL, (void *)emu_fde, inst);
    }

    while(shared->running);
    LIST_FOR_EACH(&shared->cpus, cpu,
        pthread_join((*cpu)->tid, NULL);
    );
}
