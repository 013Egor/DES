#include <iostream>
#include <bitset>
#include "fileMaster.h"

int getIterationAmount(ifstream* stream) {
    int pos = stream->tellg();
    stream->seekg (0, stream->end);
    int size = stream->tellg();
    stream->seekg (pos, stream->beg);
    int iteration = (size - pos) / BYTE_SIZE;
    if (iteration * BYTE_SIZE != (size - pos)) {
        iteration++;
    }

    return iteration;
}

bitset<MESSAGE_SIZE> getBitset(char* buffer) {
    bitset<MESSAGE_SIZE> bits = bitset<MESSAGE_SIZE>();



    for (int i = 0; i < BYTE_SIZE; ++i) {
        char c = buffer[i];
        for (int j = 0; j < BYTE_SIZE && c; j++) {
            if (c & 0x1) {
                bits.set(BYTE_SIZE * i + j);
            }
            c >>= 1;
        }
    }
}
void FileMaster::createFile(string text) {
    std::ofstream out;
    out.open ("message.txt", std::ofstream::out | std::ofstream::app);

    out << text;

    out.close();
}

void FileMaster::read() {
    inputBuffer.clear();
    int iteration = getIterationAmount(inFile);

    for (int t = 0; t < iteration && inputBuffer.size() < BUFFER_SIZE; t++) {
        char * buffer = new char [BYTE_SIZE];
        inFile->read (buffer,BYTE_SIZE);

        bitset<MESSAGE_SIZE> bits = getBitset(buffer);

        inputBuffer.push_back(bits);
        delete[] buffer;
    }
}

void FileMaster::saveEncrypted() {
    int bytesAmount = MESSAGE_SIZE / BYTE_SIZE;

    for (const auto &item: outputBuffer) {
        char* buffer = new char [BYTE_SIZE];

        for (int i = 0; i < bytesAmount; i++) {
            bitset<BYTE_SIZE> tempBitset = bitset<BYTE_SIZE>();
            for (int j = 0; j < BYTE_SIZE; j++) {
                tempBitset.set(j, item[i * BYTE_SIZE + j]);
            }

            buffer[i] = static_cast<unsigned char>( tempBitset.to_ullong() );
        }
        outFile->write(buffer, BYTE_SIZE);
        delete[] buffer;
    }
}

void FileMaster::save() {
    int bytesAmount = MESSAGE_SIZE / BYTE_SIZE;
    for (const auto &item: outputBuffer) {
        int cap = originSize - outFile->tellp();
        int sizeBuffer = (cap >= bytesAmount) ? bytesAmount : cap;
        char * buffer = new char [sizeBuffer];

        for (int i = 0; i < sizeBuffer; i++) {

            bitset<BYTE_SIZE> tempBitset = bitset<BYTE_SIZE>();
            for (int j = 0; j < BYTE_SIZE; j++) {
                tempBitset.set(j, item[i * BYTE_SIZE + j]);
            }
            buffer[i] = static_cast<unsigned char>( tempBitset.to_ullong() );
        }

        outFile->write(buffer, sizeBuffer);
        delete[] buffer;
    }
}
bitset<MESSAGE_SIZE>& FileMaster::getBlock(){
    bitset<MESSAGE_SIZE> temp = inputBuffer.front();
    inputBuffer.pop_front();
    return temp;
}
