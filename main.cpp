#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iomanip>

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

// Parsing the ROM header data
RomHeader parse_rom_header(const std::vector<uint8_t>& rom_data) {
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


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_rom>" << std::endl;
        return 1;
    }

    std::vector<uint8_t> rom_data = load_rom(argv[1]);

    if (rom_data.empty()) {
        std::cerr << "Error: Could not load ROM file." << std::endl;
        return 1;
    }

    std::cout << "ROM file loaded successfully." << std::endl;

    RomHeader header = parse_rom_header(rom_data);
    std::cout << "Header Data" << std::endl;
    std::cout << "Title: " << header.title << std::endl;
    
    // --- Correctly formatted output for single-byte (uint8_t) values ---
    // Use setfill('0') to add leading zeroes and setw(2) for a width of 2.
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
}