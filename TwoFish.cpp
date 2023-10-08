#include "TwoFish.h"

const unsigned charMDR[] = {
        0x01, 0xEF, 0x5B, 0x5B,
        0x5B, 0xEF, 0xEF, 0x01,
        0xEF, 0x5B, 0x01, 0xEF,
        0xEF, 0x01, 0xEF, 0x5B
};

TwoFish::TwoFish(const std::string& newMode, const std::string& key) {
    if (key.length() < 16){
        std::cout << "TwoFish::TwoFish(): keyString.length() < 16";
        exit(-1);
    }


    // Writing keyString to class fields
    if (key.length() >= 32){
        for (int i = 0; i < 32; i++) masterKey.push_back(static_cast<uint8_t>(key[i]));
        keySize = 256;
    }
    else if (key.length() >= 24){
        for (int i = 0; i < 24; i++) masterKey.push_back(static_cast<uint8_t>(key[i]));
        keySize = 192;
    }
    else if (key.length() > 16){
        for (int i = 0; i < 16; i++) masterKey.push_back(static_cast<uint8_t>(key[i]));
        keySize = 128;
    }
    std::cout << "Key size is " << keySize << std::endl;

    // Writing mode to class fields
    if (newMode == "ECB"){
        mode = Mode::CBC;
        return;
    }
    if (newMode == "CBC"){
        mode = Mode::CBC;
        return;
    }
    if (newMode == "CFB"){
        mode = Mode::CBC;
        return;
    }
    if (newMode == "OFB"){
        mode = Mode::CBC;
        return;
    }

    std::cerr << "Error newMode: choose 'ECB', 'CBC', 'CFB' or 'OFB'";
    exit(-1);
}

void TwoFish::decodeStreamECB(const std::string& inputPath, const std::string& outputPath) {

}

///
/// Encoding 128-bit array
///
std::vector<unsigned char> TwoFish::encodeStream(const std::vector<unsigned char>& vec) {
    std::vector<unsigned char> result;
    std::vector<uint32_t> dst;

    // Information block -> 4 x uint32_t
    uint32_t src[4];
    for (int i = 0; i < 4; ++i) {
        src[i] = (static_cast<uint32_t>(vec[i * 4]) << 24) |
                 (static_cast<uint32_t>(vec[i * 4 + 1]) << 16) |
                 (static_cast<uint32_t>(vec[i * 4 + 2]) << 8) |
                  static_cast<uint32_t>(vec[i * 4 + 3]);
    }

    // src[4] (+ mod 2) K_i
    src[0] = src[0] ^ tf_K[0];
    src[1] = src[1] ^ tf_K[1];
    src[2] = src[2] ^ tf_K[2];
    src[3] = src[3] ^ tf_K[3];

    for (int round = 0; round < 16; round++) {
        uint32_t F0, F1, R0, R1;

        //Функция F
        R0 = functionG(src[0], tf_S);

        R1 = functionG(ROL32(src[1], 8), tf_S);

        // Pseudo-Hadamard transform + keys
        F0 = R0 + R1 + tf_K[round * 2 + 8];
        F1 = R0 + (R1 << 1) + tf_K[round * 2 + 9];

        src[2] ^= F0;
        src[2] = ROR32(src[2], 1);
        src[3] = ROL32(src[3], 1) ^ F1;

        // Exchange values for next round
        F0 = src[0];
        F1 = src[1];
        src[0] = src[2];
        src[1] = src[3];
        src[2] = F0;
        src[3] = F1;
    }

    //Заключительное преобразование
    dst.push_back(src[2] ^ tf_K[4]);
    dst.push_back(src[3] ^ tf_K[5]);
    dst.push_back(src[0] ^ tf_K[6]);
    dst.push_back(src[1] ^ tf_K[7]);

    for (int i = 0; i < 4; ++i) {
        result[i * 4] = static_cast<uint8_t>((src[i] >> 24) & 0xFF);
        result[i * 4 + 1] = static_cast<uint8_t>((src[i] >> 16) & 0xFF);
        result[i * 4 + 2] = static_cast<uint8_t>((src[i] >> 8) & 0xFF);
        result[i * 4 + 3] = static_cast<uint8_t>(src[i] & 0xFF);
    }

    return result;
}

void TwoFish::encodeFile(const std::string& inputPath, const std::string& outputPath) {
    // Carefully file opening
    std::ifstream inputFile = openInputFile(inputPath);
    std::ofstream outputFile = openOutputFile(outputPath);

    // Check if source  is image
    int dotFinder = (int)inputPath.length();
    while (inputPath[dotFinder] != '.') dotFinder--;
    std::string substringInputPath = inputPath.substr(dotFinder, inputPath.length()-dotFinder);
    if ((substringInputPath == ".bmp") || (substringInputPath == ".BMP")) inputFile.seekg(54);

    ///
    /// Writing encoding method + initialize key (masterKey)
    ///
    // ECB = 0
    // CBC = 1
    // CFB = 2
    // OFB = 3
    switch (mode) {
        case Mode::ECB: outputFile.put(0); break;
        case Mode::CBC: outputFile.put(1); break;
        case Mode::CFB: outputFile.put(2); break;
        case Mode::OFB: outputFile.put(3); break;
    }
    // Writing keySize (how many bytes we need to read in decoding process)
    outputFile.put(keySize/8);
    // Writing masterKey
    for (unsigned char i : masterKey){
        outputFile.put(i);
    }

    ///
    /// Reading 128-bit arrays from file; then encoding them
    ///
    std::vector<unsigned char> src;
    unsigned char byte;
    while (inputFile.read(reinterpret_cast<char *>(&byte), 1)){
        if (src.size() == 16){
            std::vector<unsigned char> encodedVec = encodeStream(src); // Encode 128-bit (16-bytes) array from file
            outputFile.write(reinterpret_cast<const char *>(&encodedVec[0]), (int)(encodedVec.size() * sizeof(unsigned char))); // Write encoded array

            // Output to console
            for (unsigned char i : src) std::cout << std::hex << std::uppercase << (int)i;
            std::cout << " -> ";
            for (unsigned char i : encodedVec) std::cout << std::hex << std::uppercase << (int)i;

            src.clear();
        }
        src.push_back(byte);
    }
    // Add (0x00) bytes if (file.size() % 128 != 0)
    if (!src.empty()){
        while (src.size() < 16) src.push_back(0);
        std::vector<unsigned char> encodedVec = encodeStream(src); // Encode 128-bit (16-bytes) array from file
        outputFile.write(reinterpret_cast<const char *>(&encodedVec[0]), (int)(encodedVec.size() * sizeof(unsigned char))); // Write encoded array

        // Output to console
        for (unsigned char i : src) std::cout << std::hex << std::uppercase << (int)i;
        std::cout << " -> ";
        for (unsigned char i : encodedVec) std::cout << std::hex << std::uppercase << (int)i;

        src.clear();
    }

    inputFile.close();
    outputFile.close();
}

void TwoFish::generateRandomKey(uint16_t keySize) {
    srand(time(nullptr));
    switch (keySize) {
        case 128: for (int i = 0; i < 16; i++) masterKey.push_back(rand() % 256); break;
        case 192: for (int i = 0; i < 24; i++) masterKey.push_back(rand() % 256); break;
        case 256: for (int i = 0; i < 32; i++) masterKey.push_back(rand() % 256); break;
        default:{
            std::cout << "TwoFish::generateRandomKey(): keySize != 128, 192 or 256. Generating 128-bit key." << std::endl;
            for (int i = 0; i < 16; i++) masterKey.push_back(rand() % 256);
        }
    }
}

TwoFish::~TwoFish()= default;