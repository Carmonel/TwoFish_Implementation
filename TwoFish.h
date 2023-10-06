#ifndef TWOFISH_TWOFISH_H
#define TWOFISH_TWOFISH_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

enum class Mode{ECB, CBC, CFB, OFB};

class TwoFish {
private:
    __int128 masterKey;
    Mode mode;

    void ECB(const std::ifstream& inputPath, const std::ofstream& outputPath);
    void CBC(const std::ifstream& inputPath, const std::ofstream& outputPath);
    void CFB(const std::ifstream& inputPath, const std::ofstream& outputPath);
    void OFB(const std::ifstream& inputPath, const std::ofstream& outputPath);

    std::vector<unsigned char> encodeStream(const std::vector<unsigned char>& vec);
    void decodeStream(std::string inputPath, std::string outputPath);
public:
    TwoFish(std::string mode, __int128 masterKey);
    void encodeFile(std::string inputPath, std::string outputPath);
    ~TwoFish();
};

#endif //TWOFISH_TWOFISH_H
