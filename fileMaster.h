#pragma once
#include <fstream>
#include <bitset>
#include <list>
#include <string>
#include <iostream>
#define MESSAGE_SIZE 64

#define BUFFER_SIZE 40
#define BYTE_SIZE 8

using namespace std;

enum Mode{
    encryption,
    decryption
};

class FileMaster{
private:
    string inputFilename;
    string outputFilename;
    string filenameExtension;

    ifstream* inFile;
    ofstream* outFile;

    list<bitset<MESSAGE_SIZE>> inputBuffer;

    list<bitset<MESSAGE_SIZE>> outputBuffer;

    int extraBytes;
public:
    FileMaster(string filename, Mode mode) {
        string outputFilename = "";
        for (const auto &item: filename) {
            if (item == '.') {
                break;
            }
            outputFilename += item;
        }
        outputFilename += "_output";
        if (mode == 0) {
            outputFilename += ".des";
        } else {
            outputFilename += ".txt";
        }
        inFile = new ifstream(filename, std::ifstream::in);
        outFile = new ofstream(outputFilename, std::ofstream::out);

        if (mode == 1) {
            char* size = new char;
            inFile->read(size, 1);
            extraBytes = (int) size[0];
            extraBytes++;
        } else {
            inFile->seekg (0, inFile->end);
            int originSize = inFile->tellg();
            inFile->seekg (0, inFile->beg);
            int full = originSize % BYTE_SIZE;

            extraBytes = BYTE_SIZE - full;
        }
    }
    ~FileMaster() {
        if (inFile) {
            inFile->close();
        }
        if (outFile) {
            outFile->close();
        }
    }

    bitset<MESSAGE_SIZE> getBlock();


    bool setBlock(bitset<MESSAGE_SIZE>& block);

    void static createFile(string text) {
        std::ofstream out;
        out.open ("message.txt", std::ofstream::out);

        out << text;

        out.close();
    }

    void read();

    void saveEncrypted();

    void save();
};
