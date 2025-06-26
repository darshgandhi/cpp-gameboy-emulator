#include "cart.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>


int main(int argc, char* argv[]) {
    // Handling Rom Setup
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_rom>" << std::endl;
        return 1;
    }

    // Load ROM data
    std::vector<uint8_t> rom_data = load_rom(argv[1]);
    if (rom_data.empty()) {
        std::cerr << "Error: Could not load ROM file." << std::endl;
        return 1;
    }

    std::cout << "ROM file loaded successfully." << std::endl;

    // Parse ROM header
    RomHeader header;
    try {
        header = parse_rom_header(rom_data);
    } catch (const std::runtime_error& e) {
        std::cerr << "Header Error: " << e.what() << std::endl;
        return 1;
    }

    // CPU emulation loop
    uint16_t PC = 0x0100;
    int instruction_count = 0;
    bool game_running = true;
    const int MAX_INSTRUCTIONS = 10;  // For testing

    while (game_running) {
        // Check bounds before accessing ROM
        if (PC >= rom_data.size()) {
            std::cerr << "PC out of ROM bounds: 0x" << std::hex << PC << std::endl;
            break;
        }

        uint8_t opcode = rom_data[PC];
        std::cout << "Rom Data: " << std::hex << PC << " : 0x" 
                << std::setfill('0') << std::setw(2) << static_cast<int>(opcode) << std::endl;

        PC += 1;
        instruction_count++;
        
        if (instruction_count >= MAX_INSTRUCTIONS) {
            game_running = false;
        }
    }

    std::cout << "Execution finished" << std::endl;
    return 0;
}