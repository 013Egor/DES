#include <fstream>
#include <bitset>
#include <list>
#include <string>
#define MESSAGE_SIZE 64
#define BUFFER_SIZE 4
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

    int originSize;
public:
    FileMaster() {
        inFile = new ifstream("message.txt", std::ifstream::in);
        outFile = new ofstream("message_output.des", std::ofstream::out);

        inFile->seekg (0, inFile->end);
        originSize = inFile->tellg();
        inFile->seekg (0, inFile->beg);
    }
    ~FileMaster() {
        if (inFile) {
            inFile->close();
        }
        if (outFile) {
            outFile->close();
        }
    }

    bitset<MESSAGE_SIZE>& getBlock();

    void createFile(string text);

    void read();

    void saveEncrypted();

    void save();
};
