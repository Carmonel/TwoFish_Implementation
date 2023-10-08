#include <fstream>
#include <iostream>
#include <cstdint>

std::ifstream openInputFile(const std::string& inputPath){
    std::ifstream inputFile;
    try{
        inputFile.open(inputPath, std::ios::binary | std::ios::in);
    }
    catch(std::exception& e){
        std::cerr << "TwoFish::openInputFile() error: inputFile.open() throw exception." << std::endl << e.what();
        exit(-1);
    }
    if (!inputFile.is_open()){
        std::cerr << "TwoFish::openInputFile() error: !inputFile.is_open() returned false.";
        exit(-1);
    }

    return inputFile;
}
std::ofstream openOutputFile(const std::string& outputPath){
    std::ofstream outputFile;
    try{
        outputFile.open(outputPath, std::ios::binary | std::ios::out);
    }
    catch(std::exception& e){
        std::cerr << "TwoFish::encodeStream() error: outputFile.open() throw exception." << std::endl << e.what();
        exit(-1);
    }
    if (!outputFile.is_open()){
        std::cerr << "TwoFish::encodeStream() error: !outputFile.is_open() returned false.";
        exit(-1);
    }

    return outputFile;
}

// Циклический сдвиг вправо (ROR) для 32-битного числа a на b битов
uint32_t ROR32(uint32_t a, int b) {
    return (a >> b) | (a << (32 - b));
}

// Циклический сдвиг влево (ROL) для 32-битного числа a на b битов
uint32_t ROL32(uint32_t a, int b) {
    return (a << b) | (a >> (32 - b));
}
