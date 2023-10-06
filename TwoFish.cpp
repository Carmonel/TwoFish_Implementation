#include "TwoFish.h"

const unsigned charMDR[] = {
        0x01, 0xEF, 0x5B, 0x5B,
        0x5B, 0xEF, 0xEF, 0x01,
        0xEF, 0x5B, 0x01, 0xEF,
        0xEF, 0x01, 0xEF, 0x5B
};

void TwoFish::ECB(const std::ifstream& inputPath, const std::ofstream& outputPath) {

}
void TwoFish::CBC(const std::ifstream &inputPath, const std::ofstream &outputPath) {

}

void TwoFish::CFB(const std::ifstream &inputPath, const std::ofstream &outputPath) {

}

void TwoFish::OFB(const std::ifstream &inputPath, const std::ofstream &outputPath) {

}

TwoFish::TwoFish(std::string mode, __int128 masterKey) {
    this->masterKey = masterKey;
    if (mode == "ECB"){
        this->mode = Mode::CBC;
        return;
    }
    if (mode == "CBC"){
        this->mode = Mode::CBC;
        return;
    }
    if (mode == "CFB"){
        this->mode = Mode::CBC;
        return;
    }
    if (mode == "OFB"){
        this->mode = Mode::CBC;
        return;
    }

    std::cerr << "Error mode: choose 'ECB', 'CBC', 'CFB' or 'OFB'";
    exit(-1);
}

std::vector<unsigned char> TwoFish::encodeStream(const std::vector<unsigned char>& vec) {

}

void TwoFish::decodeStream(std::string inputPath, std::string outputPath) {

}

void TwoFish::encodeFile(std::string inputPath, std::string outputPath) {
    std::ifstream inputFile;
    try{
        inputFile.open(inputPath, std::ios::binary | std::ios::in);
    }
    catch(std::exception& e){
        std::cerr << "TwoFish::encodeStream() error: inputFile.open() throwed exception." << std::endl << e.what();
        exit(-1);
    }
    if (!inputFile.is_open()){
        std::cerr << "TwoFish::encodeStream() error: !inputFile.is_open() returned false.";
        exit(-1);
    }

    std::ofstream outputFile;
    try{
        outputFile.open(outputPath, std::ios::binary | std::ios::out);
    }
    catch(std::exception& e){
        std::cerr << "TwoFish::encodeStream() error: outputFile.open() throwed exception." << std::endl << e.what();
        exit(-1);
    }
    if (!outputFile.is_open()){
        std::cerr << "TwoFish::encodeStream() error: !outputFile.is_open() returned false.";
        exit(-1);
    }

    switch (mode) {
        case (Mode::ECB):{
            ECB(inputFile, outputFile);
            break;
        }
        case Mode::CBC:
            CBC(inputFile, outputFile);
            break;
        case Mode::CFB:
            CFB(inputFile, outputFile);
            break;
        case Mode::OFB:
            OFB(inputFile, outputFile);
            break;
    }


    std::vector<unsigned char> src;
    unsigned char byte;
    while (inputFile.read(reinterpret_cast<char *>(&byte), 1)){
        if (src.size() == 16){
            std::vector<unsigned char> encodedVec = encodeStream(src); // Encode 128-bit (16-bytes) array from file
            outputFile.write(reinterpret_cast<const char *>(&encodedVec[0]), encodedVec.size() * sizeof(unsigned char)); // Write encoded array
            // Debug
            for (unsigned char i : src) std::cout << std::hex << std::uppercase << (int)i;
            std::cout << " -> ";
            for (unsigned char i : encodedVec) std::cout << std::hex << std::uppercase << (int)i;
            // Debug
            src.clear();
        }
        src.push_back(byte);
    }
    // Add 0 bytes if (file.size() % 128 != 0)
    if (!src.empty()){
        while (src.size() < 16) src.push_back(0);
        std::vector<unsigned char> encodedVec = encodeStream(src); // Encode 128-bit (16-bytes) array from file
        outputFile.write(reinterpret_cast<const char *>(&encodedVec[0]), encodedVec.size() * sizeof(unsigned char)); // Write encoded array
        // Debug
        for (unsigned char i : src) std::cout << std::hex << std::uppercase << (int)i;
        std::cout << " -> ";
        for (unsigned char i : encodedVec) std::cout << std::hex << std::uppercase << (int)i;
        // Debug
        src.clear();
    }

    inputFile.close();
    outputFile.close();
}

TwoFish::~TwoFish()= default;
