#include <iostream>
#include <fstream>
#include <bitset>

#define EXTENDED_KEY_SIZE 64
#define KEY_SIZE 56
#define SUBKEY_SIZE 48
#define ROUNDS 16

using namespace std;

class Des{

private:
    ifstream* inputFile;
    ofstream* outputFile;

    bitset<EXTENDED_KEY_SIZE> extendedKey;
    bitset<KEY_SIZE> key;
    bitset<SUBKEY_SIZE> subkey[ROUNDS];

    void reducedKey();

public:
    Des(bitset<EXTENDED_KEY_SIZE>&);
    Des(bitset<EXTENDED_KEY_SIZE>&, ifstream, ofstream);

    void test();

    void encryption();
    void decryption();
};


int main(){
    bitset<EXTENDED_KEY_SIZE> myKey;

    srand(time(0));
    int randomValue = 0;
    for(int i = 0; i < EXTENDED_KEY_SIZE; i++){
        //randomValue = rand() % 2;
        randomValue = ++randomValue % 2;
        myKey[i] = randomValue;
    }
    cout << "key before reduced" << '\n';
    cout << myKey.to_string() << endl;;

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
    //1. Написать блок для разбивки ключа на 16 подключей
    //2. Написать блок работы функции f (главной функции)
    //3. Написать блок работы сети Файстеля
}

void Des::test(){
    reducedKey();

    cout << "key after reduced" << '\n';
    cout << key.to_string() << endl;
}



void Des::decryption(){

}

void Des::reducedKey(){
    int deleteBits = 0;
    for(int exKeyIterator = 0; exKeyIterator < EXTENDED_KEY_SIZE; exKeyIterator++){
        if(exKeyIterator != 0 && (exKeyIterator + 1) % 8 == 0){ //каждый 8ой бит удаляется
            deleteBits++;
            continue;
        }
        key[exKeyIterator - deleteBits] = extendedKey[exKeyIterator];
    }
}