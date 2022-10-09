#include <fstream>
#include <bitset>
#include <list>
#include <string>
#define BUFFER_SIZE 1024
#define MESSAGE_SIZE 64

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

    Mode fileMasterMode;
public:

    // FileMaster(Mode fileMasterMode);


    // bitset<MESSAGE_SIZE>& FileMaster::getBlock(){
    //     bitset<MESSAGE_SIZE> temp = inputBuffer.front();
    //     inputBuffer.pop_front();
    //     return temp;
    //  }

    void read(string filename);

    void save(string filename);

    void createFile(string text);
};
