#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <algorithm>

#include "des.h"

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

int IP[IP_ROWS][IP_COLUMNS] =
                {{58, 50, 42, 34, 26, 18, 10, 2},
                 {60, 52, 44, 36, 28, 20, 12, 4},
                 {62, 54, 46, 38, 30, 22, 14, 6},
                 {64, 56, 48, 40, 32, 24, 16, 8},
                 {57, 49, 41, 33, 25, 17, 9, 1},
                 {59, 51, 43, 35, 27, 19, 11, 3},
                 {61, 53, 45, 37, 29, 21, 13, 5},
                 {63, 55, 47, 39, 31, 23, 15, 7}};

int IP_REVERSE[IP_ROWS][IP_COLUMNS] =
                {{40, 8, 48, 16, 56, 24, 64, 32},
                 {39, 7, 47, 15, 55, 23, 63, 31},
                 {38, 6, 46, 14, 54, 22, 62, 30},
                 {37, 5, 45, 13, 53, 21, 61, 29},
                 {36, 4, 44, 12, 52, 20, 60, 28},
                 {35, 3, 43, 11, 51, 19, 59, 27},
                 {34, 2, 42, 10, 50, 18, 58, 26},
                 {33, 1, 41, 9, 49, 17, 57, 25}};
                


int LEFT_SHIFTS_NUMBER[ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

Des::Des(bitset<EXTENDED_KEY_SIZE>& exKey){
    extendedKey = exKey;
}

void Des::encryption(){
    //1. Написать блок для разбивки ключа на 16 подключей (complete)
    createKeys();
    //2. Написать блок работы функции f (главной функции)
    //3. Написать блок работы сети Файстеля (complete)
}

void Des::test(){
    this->createKeys();

    cout << "subkeys for testKey:\n\n";
    for(int i = 0; i < ROUNDS; i++){
        cout << "subkey " << i + 1 << " ---> " << subkey[i].to_string() << "\n" << endl;
    }

    string messageStr("0000000100100011010001010110011110001001101010111100110111101111");
    reverse(messageStr.begin(), messageStr.end());
    bitset<MESSAGE_SIZE> messageTmp(messageStr);
    this->message = messageTmp;
    this->feistelСipher();
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

    while(keyIterator < KEY_SIZE/2) leftKeyHalf[halfIterator++] = key[keyIterator++];
    halfIterator = 0;
    while(keyIterator < KEY_SIZE) rightKeyHalf[halfIterator++] = key[keyIterator++];
}

void Des::subkeyInitialization(){

    for(int roundСounter = 1; roundСounter <= ROUNDS; roundСounter++){
        
        bool lostValue;

        bitset<KEY_SIZE> concatenated;
        int concatenatedCounter = 0; 

        //shift halfs
        for(int shiftCounter = 0; shiftCounter < LEFT_SHIFTS_NUMBER[roundСounter - 1]; shiftCounter++){

            lostValue = leftKeyHalf[0];
            leftKeyHalf >>= 1; 
            leftKeyHalf[KEY_SIZE/2 - 1] = lostValue;             
            
            lostValue = rightKeyHalf[0];
            rightKeyHalf >>= 1;
            rightKeyHalf[KEY_SIZE/2 - 1] = lostValue;

        }

        //concatenated two halfs = leftHalf + rightHalf
        for(int leftCounter = 0; leftCounter < KEY_SIZE/2; leftCounter++)
            concatenated[concatenatedCounter++] = leftKeyHalf[leftCounter];
        for(int rightCounter = 0; rightCounter < KEY_SIZE/2; rightCounter++)
            concatenated[concatenatedCounter++] = rightKeyHalf[rightCounter];

        //permutation. concatenated key(56 bits) --(to)--> subkey(48 bits) 
        int subkeyIterator = 0;
        for(int row = 0; row < PC2_ROWS; row++){
            for(int column = 0; column < PC2_COLUMNS; column++){
                subkey[roundСounter - 1][subkeyIterator++] = concatenated[PC2[row][column] - 1];
            }
        }
    }   
}

bitset<MESSAGE_SIZE> Des::feistelСipher(){
    bitset<MESSAGE_SIZE> encryptedMessage;

    //initial message permutation
    bitset<MESSAGE_SIZE> permutationMessage;
    int messageIterator = 0;
    for(int row = 0; row < IP_ROWS; row++){
        for(int column = 0; column < IP_COLUMNS; column++){
            permutationMessage[messageIterator++] = message[IP[row][column] - 1];
        }
    }

    //split permutation message
    messageIterator = 0;
    int halfIterator = 0;

    while(messageIterator < MESSAGE_SIZE/2) leftMessageHalf[halfIterator++] = permutationMessage[messageIterator++];
    halfIterator = 0;
    while(messageIterator < MESSAGE_SIZE) rightMessageHalf[halfIterator++] = permutationMessage[messageIterator++];
    cout << leftMessageHalf << "\n" << rightMessageHalf << endl;
    
    //Faistel cipher
    bitset<MESSAGE_SIZE/2> nextLeftHalf = leftMessageHalf;
    bitset<MESSAGE_SIZE/2> nextRightHalf = rightMessageHalf;
    for(int roundCounter; roundCounter < ROUNDS; roundCounter++){
        leftMessageHalf = nextLeftHalf;
        rightMessageHalf = nextRightHalf;

        nextLeftHalf = rightMessageHalf;
        nextRightHalf = leftMessageHalf ^ functionF(rightMessageHalf, subkey[roundCounter]);
    }
/*
    //test
    string l1("01000011010000100011001000110100");
    reverse(l1.begin(), l1.end());
    bitset<MESSAGE_SIZE/2> lh(l1);
    

    string r1("00001010010011001101100110010101");
    reverse(r1.begin(), r1.end());
    bitset<MESSAGE_SIZE/2> rh(r1);

    nextLeftHalf = lh;
    nextRightHalf = rh;
    //test end
*/
    //concatenated two halfs = rightHalf + leftHalf
    int permutationCounter = 0;
    for(int rightCounter = 0; rightCounter < MESSAGE_SIZE/2; rightCounter++)
        permutationMessage[permutationCounter++] = nextRightHalf[rightCounter];
    for(int leftCounter = 0; leftCounter < MESSAGE_SIZE/2; leftCounter++)
        permutationMessage[permutationCounter++] = nextLeftHalf[leftCounter];

    //finish message permutation
    messageIterator = 0;
    for(int row = 0; row < IP_ROWS; row++){
        for(int column = 0; column < IP_COLUMNS; column++){
            encryptedMessage[messageIterator++] = permutationMessage[IP_REVERSE[row][column] - 1];
        }
    }

    return encryptedMessage;
}

bitset<MESSAGE_SIZE/2> Des::functionF(bitset<MESSAGE_SIZE/2> rightHalf, bitset<SUBKEY_SIZE> key){
    return rightHalf;
}
















