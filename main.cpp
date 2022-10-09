#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include <string>

#include "des.h"
#include "fileMaster.h"

using namespace std;


int main(){
    FileMaster* file = new FileMaster("test.txt", encryption);
    string keyStr("0001001100110100010101110111100110011011101111001101111111110001");
    reverse(keyStr.begin(), keyStr.end());

    bitset<EXTENDED_KEY_SIZE> myKey(keyStr);
    Des* encryptor = new Des(myKey, encryption);
    encryptor->setMessage(file->getBlock());

    file->saveEncrypted(encryptor.encryption());

}