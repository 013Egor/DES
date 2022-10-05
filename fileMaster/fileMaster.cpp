#include <iostream>
#include "fileMaster.h"

void FileMaster::createFile(string text) {
    std::ofstream out;
    out.open ("message.txt", std::ofstream::out | std::ofstream::app);

    out << text;

    out.close();
}

void FileMaster::read(string filename) {
    inFile = new ifstream(filename, std::ifstream::in);
    inFile->seekg (0, inFile->end);
    int length = inFile->tellg();
    inFile->seekg (0, inFile->beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... ";

    inFile->read (buffer,length);

    if (inFile)
      std::cout << "all characters read successfully.";
    else
      std::cout << "error: only " << inFile->gcount() << " could be read";
    inFile->close();

    delete[] buffer;
}