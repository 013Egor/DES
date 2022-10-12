#include "des.h"

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

int P[P_ROWS][P_COLUMNS] =
        {{16, 7, 20, 21},
         {29, 12, 28, 17},
         {1, 15, 23, 26},
         {5, 18, 31, 10},
         {2, 8, 24, 14},
         {32, 27, 3, 9},
         {19, 13, 30, 6},
         {22, 11, 4, 25}};

int IP_REVERSE[IP_ROWS][IP_COLUMNS] =
        {{40, 8, 48, 16, 56, 24, 64, 32},
         {39, 7, 47, 15, 55, 23, 63, 31},
         {38, 6, 46, 14, 54, 22, 62, 30},
         {37, 5, 45, 13, 53, 21, 61, 29},
         {36, 4, 44, 12, 52, 20, 60, 28},
         {35, 3, 43, 11, 51, 19, 59, 27},
         {34, 2, 42, 10, 50, 18, 58, 26},
         {33, 1, 41, 9, 49, 17, 57, 25}};

int E_BIT_SELECTION_TABLE[E_ROWS][E_COLUMNS] =
        {{32, 1, 2, 3, 4, 5},
         {4, 5, 6, 7, 8, 9},
         {8, 9, 10, 11, 12, 13},
         {12, 13, 14, 15, 16, 17},
         {16, 17, 18, 19, 20, 21},
         {20, 21, 22, 23, 24, 25},
         {24, 25, 26, 27, 28, 29},
         {28, 29, 30, 31, 32, 1}};

int S_BOX[S_BOX_NUMBER][S_BOX_ROWS][S_BOX_COLUMNS] = {
        {
                { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
                { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
                { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
                { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
        },
        {
                { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
                { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
                { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
                { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
        },
        {
                { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
                { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
                { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
                { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
        },
        {
                { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
                { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
                { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
                { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
        },
        {
                { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
                { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
                { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
                { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
        },
        {
                { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
                { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
                { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
                { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
        },
        {
                { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
                { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
                { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
                { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
        },
        {
                { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
                { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
                { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
                { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
        }
};

int LEFT_SHIFTS_NUMBER[ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
void drawCell(int item) {
    if (item / 10 == 0) {
        cout << "| " << item << "  |";
    } else {
        cout << "| " << item << " |";
    }
}
void drawLine(int item) {
    for (int i = 0; i < item; i++) {
        cout << '-';
    }
    cout << endl;
}

void Des::showPC_1() {
    drawLine(44);
    for (const auto &item: PC1) {
        cout << '|';
        for (const auto &item: item) {
            drawCell(item);
        }
        cout << '|' << endl;
    }
    drawLine(44);
}
void Des::showPC_2() {
    drawLine(38);
    for (const auto &item: PC2) {
        cout << '|';
        for (const auto &item: item) {
            drawCell(item);
        }
        cout << '|' << endl;
    }
    drawLine(38);
}

void Des::showIP() {
    drawLine(50);
    for (const auto &item: IP) {
        cout << '|';
        for (const auto &item: item) {
            drawCell(item);
        }
        cout << '|' << endl;
    }
    drawLine(50);
}


void Des::showE() {
    drawLine(38);
    for (const auto &item: E_BIT_SELECTION_TABLE) {
        cout << '|';
        for (const auto &item: item) {
            drawCell(item);
        }
        cout << '|' << endl;
    }
    drawLine(38);
}


void Des::showP() {
    drawLine(26);
    for (const auto &item: P) {
        cout << '|';
        for (const auto &item: item) {
            drawCell(item);
        }
        cout << '|' << endl;
    }
    drawLine(26);
}

void Des::showIP_r() {
    drawLine(50);
    for (const auto &item: IP_REVERSE) {
        cout << '|';
        for (const auto &item: item) {
            drawCell(item);
        }
        cout << '|' << endl;
    }
    drawLine(50);
}

void Des::showS_box(int id) {
    drawLine(98);
    for (const auto &item: S_BOX[id]) {
        cout << '|';
        for (const auto &item: item) {
            drawCell(item);
        }
        cout << '|' << endl;
    }
    drawLine(98);
}

void Des::changePC_1(int row, int column, int value) {
    PC1[row][column] = value;
}
void Des::changePC_2(int row, int column, int value) {
    PC2[row][column] = value;
}

void Des::changeIP(int row, int column, int value) {
    IP[row][column] = value;
}

void Des::changeE(int row, int column, int value) {
    E_BIT_SELECTION_TABLE[row][column] = value;
}

void Des::changeP(int row, int column, int value) {
    P[row][column] = value;
}

void Des::changeIP_r(int row, int column, int value) {
    IP_REVERSE[row][column] = value;
}

void Des::changeS_box(int id, int row, int column, int value) {
    S_BOX[id][row][column] = value;
}

Des::Des(bitset<EXTENDED_KEY_SIZE>& exKey, bitset<MESSAGE_SIZE>& newMessage, Mode m){
    this->mode = m;
    extendedKey = exKey;
    this->message = newMessage;
}

bitset<MESSAGE_SIZE> Des::run(){
    createKeys();
    return feistelCipher();
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

    for(int roundCounter = 1; roundCounter <= ROUNDS; roundCounter++){
        
        bool lostValue;

        bitset<KEY_SIZE> concatenated;
        int concatenatedCounter = 0; 

        //shift halfs
        for(int shiftCounter = 0; shiftCounter < LEFT_SHIFTS_NUMBER[roundCounter - 1]; shiftCounter++){

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
                subkey[roundCounter - 1][subkeyIterator++] = concatenated[PC2[row][column] - 1];
            }
        }
    }   
}

bitset<MESSAGE_SIZE> Des::feistelCipher(){
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
    
    //Faistel cipher
    bitset<MESSAGE_SIZE/2> nextLeftHalf = leftMessageHalf;
    bitset<MESSAGE_SIZE/2> nextRightHalf = rightMessageHalf;
    for(int roundCounter = 0; roundCounter < ROUNDS; roundCounter++){
        leftMessageHalf = nextLeftHalf;
        rightMessageHalf = nextRightHalf;

        nextLeftHalf = rightMessageHalf;
        nextRightHalf = leftMessageHalf ^ functionF(rightMessageHalf, subkey[(this->mode == 0) ? roundCounter : ROUNDS - 1 - roundCounter]);
        /*error*/
       // cout << "right half: " << nextRightHalf << endl;
    }

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
    bitset<SUBKEY_SIZE> extendedHalf;
    bitset<MESSAGE_SIZE/2> result;
    bitset<MESSAGE_SIZE/2> permutationResult;

    int resultIterator = 0;

    int messageIterator = 0;
    for(int row = 0; row < E_ROWS; row++){
        for(int column = 0; column < E_COLUMNS; column++){
            extendedHalf[messageIterator++] = rightHalf[E_BIT_SELECTION_TABLE[row][column] - 1];
        }
    }

    extendedHalf = extendedHalf ^ key;

    int halfCounter = 0;
    int blockCounter = 0;
    for(int round = 0; round < F_FUNCTION_ROUNDS; round++){
        bitset<F_FUNCTION_BLOCKS> currentBlock;

        for(blockCounter = 0; blockCounter < F_FUNCTION_BLOCKS; blockCounter++) 
            currentBlock[blockCounter] = extendedHalf[halfCounter++];
        
        bitset<S_BOX_ROW_POSITION> reverseSBoxRow;
        reverseSBoxRow[0] = currentBlock[0];
        reverseSBoxRow[1] = currentBlock[F_FUNCTION_BLOCKS - 1];

        bitset<S_BOX_COLUMN_POSITION> reverseSBoxColumn;
        for(int iterator = 0; iterator < S_BOX_COLUMN_POSITION; iterator++)
            reverseSBoxColumn[iterator] = currentBlock[iterator + 1];

        string tmpForReverseRow = reverseSBoxRow.to_string();
        reverse(tmpForReverseRow.begin(), tmpForReverseRow.end());
    
        string tmpForReverseColumn = reverseSBoxColumn.to_string();
        reverse(tmpForReverseColumn.begin(), tmpForReverseColumn.end());
        
        bitset<S_BOX_ROW_POSITION> sBoxRow(tmpForReverseRow);
        bitset<S_BOX_COLUMN_POSITION> sBoxColumn(tmpForReverseColumn);

        //cout << "row: " << sBoxRow.to_ulong() << '\n' << endl;
        //cout << "column: " << sBoxColumn.to_ulong() << '\n' << endl;
        bitset<S_BOX_RESULT_SIZE> reverseResultBlock(S_BOX[round][sBoxRow.to_ulong()][sBoxColumn.to_ulong()]);
        
        string tmpForReverse = reverseResultBlock.to_string();
        reverse(tmpForReverse.begin(), tmpForReverse.end());

        bitset<S_BOX_RESULT_SIZE> resultBlock(tmpForReverse);
        for(int blockCounter = 0; blockCounter < S_BOX_RESULT_SIZE; blockCounter++){
            result[resultIterator++] = resultBlock[blockCounter];
        }
    }
    //cout << "result: " << result << "\n" << endl;
    //final permutation
    resultIterator = 0;
    for(int row = 0; row < P_ROWS; row++){
        for(int column = 0; column < P_COLUMNS; column++){
            permutationResult[resultIterator++] = result[P[row][column] - 1];
        }
    }
    //cout << "permutation result: " << permutationResult << endl;
    return permutationResult;
}