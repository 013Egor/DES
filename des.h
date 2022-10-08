/*DES algorithm
from https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
*/
#include <iostream>
#include <fstream>
#include <bitset>

#define EXTENDED_KEY_SIZE 64
#define KEY_SIZE 56
#define SUBKEY_SIZE 48
#define ROUNDS 16

#define MESSAGE_SIZE 64

#define PC1_ROWS 8
#define PC1_COLUMNS 7

#define PC2_ROWS 8
#define PC2_COLUMNS 6

#define IP_ROWS 8
#define IP_COLUMNS 8

#define E_ROWS 8
#define E_COLUMNS 6

#define S_BOX_NUMBER 8
#define S_BOX_ROWS 4
#define S_BOX_COLUMNS 16

#define F_FUNCTION_ROUNDS 8
#define F_FUNCTION_BLOCKS 6 //example: 100100 

//F_FUNCTION_BLOCKS = S_BOX_ROW_POSITION + S_BOX_COLUMN_POSITION

#define S_BOX_ROW_POSITION 2 //[1]0010[O] ---> 10
#define S_BOX_COLUMN_POSITION 4 //1[0][0][1][0]0 ---> 0010
#define S_BOX_RESULT_SIZE 4

#define P_ROWS 8
#define P_COLUMNS 4

using namespace std;

class Des{

private:
    bitset<EXTENDED_KEY_SIZE> extendedKey;
    bitset<SUBKEY_SIZE> subkey[ROUNDS];
    bitset<MESSAGE_SIZE> message;

    //for subkey initialization
    bitset<KEY_SIZE> key;
    bitset<KEY_SIZE/2> leftKeyHalf; // left half of key
    bitset<KEY_SIZE/2> rightKeyHalf; // right half of key

    //for feistel cipher
    bitset<MESSAGE_SIZE/2> leftMessageHalf;
    bitset<MESSAGE_SIZE/2> rightMessageHalf;

    //for subkey initialization
    void createKeys();
    void initialKeyPermutation();
    void splitKey();
    void subkeyInitialization();

    //for feistel cipher
    bitset<MESSAGE_SIZE> feistelСipher();
    bitset<MESSAGE_SIZE/2> functionF(bitset<MESSAGE_SIZE/2> rightHalf, bitset<SUBKEY_SIZE> key);

public:
    Des(bitset<EXTENDED_KEY_SIZE>&);
    void test();

    bitset<MESSAGE_SIZE> encryption();
    void decryption();
    
};