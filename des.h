/*DES algorithm
from https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
*/
#pragma once
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "fileMaster.h"

#define EXTENDED_KEY_SIZE 64
#define KEY_SIZE 56
#define SUBKEY_SIZE 48


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

#define MAX_ROUNDS 1000

//F_FUNCTION_BLOCKS = S_BOX_ROW_POSITION + S_BOX_COLUMN_POSITION

#define S_BOX_ROW_POSITION 2 //[1]0010[O] ---> 10
#define S_BOX_COLUMN_POSITION 4 //1[0][0][1][0]0 ---> 0010
#define S_BOX_RESULT_SIZE 4

#define P_ROWS 8
#define P_COLUMNS 4

using namespace std;

static int ROUNDS = 16;

class Des{

private:
    Mode mode;

    bitset<EXTENDED_KEY_SIZE> extendedKey;
    bitset<SUBKEY_SIZE> subkey[MAX_ROUNDS];
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
    bitset<MESSAGE_SIZE> feistelCipher();
    bitset<MESSAGE_SIZE/2> functionF(bitset<MESSAGE_SIZE/2> rightHalf, bitset<SUBKEY_SIZE> key);

public:
    Des(bitset<EXTENDED_KEY_SIZE>& key, bitset<MESSAGE_SIZE>& new_message, Mode m);
    bitset<MESSAGE_SIZE> run();
    static void showPC_1();
    static void showPC_2();
    static void showIP();
    static void showE();
    static void showP();
    static void showIP_r();
    static void showS_box(int id);
    static void changeROUNDS(int value);
    static void changePC_1(int row, int column, int value);
    static void changePC_2(int row, int column, int value);
    static void changeIP(int row, int column, int value);
    static void changeE(int row, int column, int value);
    static void changeP(int row, int column, int value);
    static void changeIP_r(int row, int column, int value);
    static void changeS_box(int id, int row, int column, int value);

};

//cout << "| 9) Change PC-1 table                |\n"; //TODO 9
//cout << "| 10) Change PC-2 table               |\n"; //TODO 10
//cout << "| 11) Change IP table                 |\n"; //TODO 11
//cout << "| 12) Change E table                  |\n"; //TODO 12
//cout << "| 13) Change P table                  |\n"; //TODO 13
//cout << "| 14) Change IP~ table                |\n"; //TODO 14