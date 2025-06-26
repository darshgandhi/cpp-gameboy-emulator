#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct RomHeader {
    char title[16];           // 0x0134 - 0x0143
    uint8_t cgb_flag;         // 0x0143 - CGB flag (part of title area)
    uint16_t new_licensee_code; // 0x0144 - 0x0145
    uint8_t sgb_flag;         // 0x0146 - SGB flag
    uint8_t cartridge_type;   // 0x0147 - Cartridge Type
    uint8_t rom_size;         // 0x0148 - ROM Size
    uint8_t ram_size;         // 0x0149 - RAM Size
    uint8_t dest_code;        // 0x014A - Destination Code
    uint8_t old_licensee_code;// 0x014B - Old Licensee Code
    uint8_t rom_version;      // 0x014C - Mask ROM Version number
    uint8_t header_checksum;  // 0x014D - Header Checksum
    uint16_t global_checksum; // 0x014E - 0x014F - Global Checksum
};

RomHeader parse_rom_header(const std::vector<uint8_t>& rom_data);
std::vector<uint8_t> load_rom(const std::string& path);