#pragma once
#include <cstdint>

struct CPUState {
    // Registers
    uint8_t a, b, c, d, e, h, l;
    uint16_t pc, sp;
    
    // Flags (F register)
    struct {
        uint8_t z:1;  // Zero flag
        uint8_t n:1;  // Subtract flag
        uint8_t h:1;  // Half Carry flag
        uint8_t c:1;  // Carry flag
    } flags;
};

// Opcode handler type
using OpcodeHandler = void (*)(CPUState&, const uint8_t*);

// Decoder function
void execute_opcode(CPUState& state, const uint8_t* memory);
