# Audr32

Audr32 is a 32-bit little-endian computer architecture that takes inspiration from RISC design choices, whilst very much remaining a CISC at heart. Audr32 is designed to run on real hardware and implements its entire instruction set in just 16 opcodes (4 bits).

## ISA

Please read the [ISA documentation](isa.txt) for information regarding the function of the CPU, Assembler, and other various relevant tidbits.

## Project Structure

- `emu/` Fully featured SDL2 powered emulator aiming for hardware parity.
- `common/` Common files, such as: ISA specifications, helper functions, and whatever else is needed to be common between subprojects.
- `disasm/` Disassembler that will automatically conform to the standards defined in [isa.h](common/include/isa.h).

## Building

To build a copy of the Audr32 toolchain, simply go through each subproject (excluding `common/`) and run `make`.
