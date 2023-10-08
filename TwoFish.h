#ifndef TWOFISH_TWOFISH_H
#define TWOFISH_TWOFISH_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "Utils.cpp"

enum class Mode{ECB, CBC, CFB, OFB};

class TwoFish {
private:
    std::vector<uint8_t> masterKey;
    uint16_t keySize;
    Mode mode;

    std::vector<unsigned char> encodeStream(const std::vector<unsigned char>& vec);
    void decodeStreamECB(const std::string& inputPath, const std::string& outputPath);
public:
    TwoFish(const std::string& newMode, const std::string& key);
    void generateRandomKey(uint16_t keySize);
    void encodeFile(const std::string& inputPath, const std::string& outputPath);
    ~TwoFish();
};

#endif //TWOFISH_TWOFISH_H