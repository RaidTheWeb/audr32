#include <stdio.h>
#include <string.h>

#include "emu.h"

static void usage(void) {
    printf("Usage: %s [-rom bootrom] [-ramsize size] [-smp cpus]\n", CBINNAME);
    printf("        -ramsize size      RAM (MB) to allocate.\n");
    printf("        -rom bootrom       Select ROM image.\n");
    printf("        -smp cpus          CPU count for multi-processing.\n");
    exit(1);
}

int main(int argc, char **argv) {

    char *bootrom = NULL;
    uint64_t ramsize = 8 * 1024 * 1024; // 8MB
    int cpucount = 1;

    if(argc < 2) usage();

    for(uint32_t i = 1; i < argc; i++) {
        if(*argv[i] != '-') break;
        switch(argv[i][1]) {
            case 'r':
                if(!strcmp(argv[i], "-ramsize")) { ramsize = strtol(argv[++i], NULL, 10) * 1024 * 1024; break; } // ram size (MBs)
                if(!strcmp(argv[i], "-rom")) { bootrom = strdup(argv[++i]); break; }
            case 's':
                if(!strcmp(argv[i], "-smp")) { cpucount = strtol(argv[++i], NULL, 10); break; }
            default: usage();
        }
    }


    emu_init(bootrom, ramsize, cpucount);
    return 0;
}
