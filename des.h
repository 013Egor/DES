/*DES algorithm
from https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
*/
#include <iostream>
#include <fstream>
#include <bitset>

#define EXTENDED_KEY_SIZE 64
#define KEY_SIZE 56
#define SUBKEY_SIZE 48
#define SUBKEY_INITIALIZATION_ROUNDS 16

#define PC1_ROWS 8
#define PC1_COLUMNS 7

#define PC2_ROWS 8
#define PC2_COLUMNS 6

using namespace std;

class Des{

private:
    ifstream* inputFile;
    ofstream* outputFile;

    bitset<EXTENDED_KEY_SIZE> extendedKey;
    bitset<KEY_SIZE> key;
    bitset<KEY_SIZE/2> leftHalf; // left half of key
    bitset<KEY_SIZE/2> rightHalf; // right half of key
    bitset<SUBKEY_SIZE> subkey[SUBKEY_INITIALIZATION_ROUNDS];

    void createKeys();
    void initialKeyPermutation();
    void splitKey();
    void subkeyInitialization();

public:
    Des(bitset<EXTENDED_KEY_SIZE>&);
    Des(bitset<EXTENDED_KEY_SIZE>&, ifstream, ofstream);

    void test();

    void encryption();
    void decryption();
};