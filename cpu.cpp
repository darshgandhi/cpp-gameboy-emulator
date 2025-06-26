#include "cpu.h"
#include <iostream>

// Helper functions
namespace {
    void nop(CPUState& state, const uint8_t*) {
        // Do nothing
    }
    
    void ld_a_d8(CPUState& state, const uint8_t* mem) {
        state.a = mem[state.pc + 1];
    }
}

// Opcode dispatch table
const OpcodeHandler opcode_table[256] = {
    [0x00] = nop,
    [0x01] = ld_a_d8,
    
};

void execute_opcode(CPUState& state, const uint8_t* memory) {
    uint8_t opcode = memory[state.pc];
    opcode_table[opcode](state, memory + state.pc);
}
