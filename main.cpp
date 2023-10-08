#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    std::vector<uint8_t> vec = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                                0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00};


    uint32_t src[4];
    for (int i = 0; i < 4; ++i) {
        src[i] = (static_cast<uint32_t>(vec[i * 4]) << 24) |
                 (static_cast<uint32_t>(vec[i * 4 + 1]) << 16) |
                 (static_cast<uint32_t>(vec[i * 4 + 2]) << 8) |
                 static_cast<uint32_t>(vec[i * 4 + 3]);
    }

    for (int i = 0; i < 4; i++) std::cout << std::hex << std::uppercase << src[i] << " ";
}