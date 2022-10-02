/*DES algorithm
from https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
*/

#include <iostream>
#include <fstream>
#include <bitset>
#include <bit>
#include <string>
#include <algorithm>

#define EXTENDED_KEY_SIZE 64
#define KEY_SIZE 56
#define SUBKEY_SIZE 48
#define SUBKEY_INITIALIZATION_ROUNDS 16

#define PC1_ROWS 8
#define PC1_COLUMNS 7

#define PC2_ROWS 8
#define PC2_COLUMNS 6

using namespace std;


int PC1[PC1_ROWS][PC1_COLUMNS] = 
                {{57, 49, 41, 33, 25, 17, 9},
                 {1, 58, 50, 42, 34, 26, 18},
                 {10, 2, 59, 51, 43, 35, 27},
                 {19, 11, 3, 60, 52, 44, 36},
                 {63, 55, 47, 39, 31, 23, 15},
                 {7, 62, 54, 46, 38, 30, 22},
                 {14, 6, 61, 53, 45, 37, 29},
                 {21, 13, 5, 28, 20, 12, 4}};

int PC2[PC2_ROWS][PC2_COLUMNS] =
                {{14, 17, 11, 24, 1, 5},
                 {3, 28, 15, 6, 21, 10},
                 {23, 19, 12, 4, 26, 8},
                 {16, 7, 27, 20, 13, 2},
                 {41, 52, 31, 37, 47, 55},
                 {30, 40, 51, 45, 33, 48},
                 {44, 49, 39, 56, 34, 53},
                 {46, 42, 50, 36, 29, 32}};

int LEFT_SHIFTS_NUMBER[SUBKEY_INITIALIZATION_ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

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


int main(){
    string keyStr("0001001100110100010101110111100110011011101111001101111111110001");
    reverse(keyStr.begin(), keyStr.end());
    
    cout << "testKey: 0001001100110100010101110111100110011011101111001101111111110001" << "\n" << endl;

    bitset<EXTENDED_KEY_SIZE> myKey(keyStr);
    Des* d = new Des(myKey);
    d->test();
}


Des::Des(bitset<EXTENDED_KEY_SIZE>& exKey){
    extendedKey = exKey;
}

Des::Des(bitset<EXTENDED_KEY_SIZE>& exKey, ifstream in, ofstream out){
    extendedKey = exKey;
    inputFile = &in;
    outputFile = &out;
}

void Des::encryption(){
    //1. Написать блок для разбивки ключа на 16 подключей (complete)
    createKeys();
    //2. Написать блок работы функции f (главной функции)
    //3. Написать блок работы сети Файстеля
}

void Des::test(){
    createKeys();

    cout << "subkeys for testKey:\n\n";
    for(int i = 0; i < SUBKEY_INITIALIZATION_ROUNDS; i++){
        cout << "subkey " << i + 1 << " ---> " << subkey[i].to_string() << "\n" << endl;
    }
}



void Des::decryption(){

}

void Des::createKeys(){
    initialKeyPermutation();
    splitKey();
    subkeyInitialization();
}

void Des::initialKeyPermutation(){
    int keyIterator = 0;
    for(int row = 0; row < PC1_ROWS; row++){
        for(int column = 0; column < PC1_COLUMNS; column++){
            key[keyIterator++] = extendedKey[PC1[row][column] - 1];
        }
    }
}

void Des::splitKey(){
    int keyIterator = 0;
    int halfIterator = 0;

    while(keyIterator < KEY_SIZE/2) leftHalf[halfIterator++] = key[keyIterator++];
    halfIterator = 0;
    while(keyIterator < KEY_SIZE) rightHalf[halfIterator++] = key[keyIterator++];
}

void Des::subkeyInitialization(){

    for(int roundСounter = 1; roundСounter <= SUBKEY_INITIALIZATION_ROUNDS; roundСounter++){
        
        bool lostValue;

        bitset<KEY_SIZE> concatenated;
        int concatenatedCounter = 0; 

        //shift halfs
        for(int shiftCounter = 0; shiftCounter < LEFT_SHIFTS_NUMBER[roundСounter - 1]; shiftCounter++){

            lostValue = leftHalf[0];
            leftHalf >>= 1; 
            leftHalf[KEY_SIZE/2 - 1] = lostValue;             
            
            lostValue = rightHalf[0];
            rightHalf >>= 1;
            rightHalf[KEY_SIZE/2 - 1] = lostValue;

        }

        //concatenated two halfs = leftHalf + rightHalf
        for(int leftCounter = 0; leftCounter < KEY_SIZE/2; leftCounter++)
            concatenated[concatenatedCounter++] = leftHalf[leftCounter];
        for(int rightCounter = 0; rightCounter < KEY_SIZE/2; rightCounter++)
            concatenated[concatenatedCounter++] = rightHalf[rightCounter];

        //permutation. concatenated key(56 bits) --(to)--> subkey(48 bits) 
        int subkeyIterator = 0;
        for(int row = 0; row < PC2_ROWS; row++){
            for(int column = 0; column < PC2_COLUMNS; column++){
                subkey[roundСounter - 1][subkeyIterator++] = concatenated[PC2[row][column] - 1];
            }
        }
    }   
}

















