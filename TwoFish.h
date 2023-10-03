#ifndef TWOFISH_TWOFISH_H
#define TWOFISH_TWOFISH_H
#include <string>
#include <iostream>
#include <fstream>

enum class Mode{ECB, CBC, CFB, OFB};

class TwoFish {
private:
    __int128 masterKey;
    Mode mode;

    void ECB(std::ifstream inputPath, std::ofstream outputPath);
public:
    TwoFish(std::string mode, __int128 masterKey);
    void encode(std::string inputPath, std::string outputPath);
    void decode(std::string inputPath, std::string outputPath);
    ~TwoFish();
};

#endif //TWOFISH_TWOFISH_H
