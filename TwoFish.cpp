#include "TwoFish.h"

void TwoFish::ECB(std::ifstream inputPath, std::ofstream outputPath) {

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

void TwoFish::encode(std::string inputPath, std::string outputPath) {
    std::ifstream inputFile;
    try{
        inputFile.open(inputPath, std::ios::binary | std::ios::in);
    }
    catch(std::exception& e){
        std::cerr << "TwoFish::encode() error: inputFile.open() throwed exception." << std::endl << e.what();
        exit(-1);
    }
    if (!inputFile.is_open()){
        std::cerr << "TwoFish::encode() error: !inputFile.is_open() returned false.";
        exit(-1);
    }

    std::ifstream outputFile;
    try{
        outputFile.open(outputPath, std::ios::binary | std::ios::out);
    }
    catch(std::exception& e){
        std::cerr << "TwoFish::encode() error: outputFile.open() throwed exception." << std::endl << e.what();
        exit(-1);
    }
    if (!outputFile.is_open()){
        std::cerr << "TwoFish::encode() error: !outputFile.is_open() returned false.";
        exit(-1);
    }

    switch (mode) {
        case (Mode::ECB):{
            ECB(inputFile, outputFile);
        }
        case Mode::CBC:
            break;
        case Mode::CFB:
            break;
        case Mode::OFB:
            break;
    }
}

void TwoFish::decode(std::string inputPath, std::string outputPath) {

}

TwoFish::~TwoFish() {

}
