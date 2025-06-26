#pragma once
#include "cart.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iomanip>

// Parsing the ROM header data
RomHeader parse_rom_header(const std::vector<uint8_t>& rom_data) {
    if (rom_data.size() < 0x150) {
    throw std::runtime_error("ROM too small to contain header");
}

    RomHeader header;
    std::memcpy(header.title, &rom_data[0x0134], 16);
    header.cgb_flag =  rom_data[0x0143];
    header.new_licensee_code =  (rom_data[0x0144] << 8) | rom_data[0x0145];
    header.sgb_flag =  rom_data[0x0146];
    header.cartridge_type =  rom_data[0x0147];
    header.rom_size =  rom_data[0x0148];
    header.ram_size =  rom_data[0x0149];
    header.dest_code =  rom_data[0x014A];
    header.old_licensee_code =  rom_data[0x014B];
    header.rom_version =  rom_data[0x014C];
    header.header_checksum =  rom_data[0x014D];
    header.global_checksum = (rom_data[0x014E] << 8) | rom_data[0x014F];

    // Print header info
    std::cout << "Header Data" << std::endl;
    std::cout << "Title: " << header.title << std::endl;

    std::cout << "CGB Flag: $" << std::hex << (int)header.cgb_flag << std::endl;
    std::cout << "New Licensee Code: " << std::hex << std::setfill('0') << std::setw(2) << header.new_licensee_code << std::endl;
    std::cout << "SGB Flag: $" << std::hex << std::setfill('0') << std::setw(2) << (int)header.sgb_flag << std::endl;
    std::cout << "Cartridge Type: $" << std::hex << std::setfill('0') << std::setw(2) << (int)header.cartridge_type << std::endl;
    std::cout << "ROM Size: $" << std::hex << std::setfill('0') << std::setw(2) << (int)header.rom_size << std::endl;
    std::cout << "RAM Size: $" << std::hex << std::setfill('0') << std::setw(2) << (int)header.ram_size << std::endl;
    std::cout << "Destination Code: $" << std::hex << std::setfill('0') << std::setw(2) << (int)header.dest_code << std::endl;
    std::cout << "Old Licensee Code: " << std::hex << std::setfill('0') << std::setw(2) << (int)header.old_licensee_code << std::endl;
    std::cout << "ROM Version: $" << std::hex << std::setfill('0') << std::setw(2) << (int)header.rom_version << std::endl;
    std::cout << "Header checksum: " << std::hex << std::setfill('0') << std::setw(2) << (int)header.header_checksum << std::endl;
    std::cout << "Global checksum: " << std::hex << std::setfill('0') << std::setw(2) << header.global_checksum << std::endl;

    return header;
};

// Function to load the ROM file into a vector
std::vector<uint8_t> load_rom(const std::string& path) {
    
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        return {}; // Return empty vector on failure
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(size);
    file.read((char*)buffer.data(), size);
    return buffer;
}