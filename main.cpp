#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>

#include "des.h"
#include "fileMaster.h"

using namespace std;


int main(){
    
    FileMaster* file = new FileMaster("test.txt", encryption);
    file->read();
    
    string keyStr("0001001100110100010101110111100110011011101111001101111111110001");
    reverse(keyStr.begin(), keyStr.end());
    bitset<EXTENDED_KEY_SIZE> myKey(keyStr);

    bitset<64> origin = file->getBlock();
    Des* encryptor = new Des(myKey, origin, encryption);
    cout << "origin message ---> " << origin.to_string() << '\n' << endl;
    
    bitset<64> encrypt = encryptor->run();
    cout << "encrypt message ---> " << encrypt.to_string()  << '\n' << endl;

    Des* decryptor = new Des(myKey, encrypt, decryption);
    bitset<64> result = decryptor->run();
    cout << "result message ---> " << result.to_string() << '\n' << endl;

    return 0;
}