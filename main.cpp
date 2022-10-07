#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>

#include "des.h"
#include "fileMaster.h"

using namespace std;


int main(){
    string keyStr("0001001100110100010101110111100110011011101111001101111111110001");
    reverse(keyStr.begin(), keyStr.end());
    
    cout << "testKey: 0001001100110100010101110111100110011011101111001101111111110001" << "\n" << endl;

    bitset<EXTENDED_KEY_SIZE> myKey(keyStr);
    Des* d = new Des(myKey);
    d->test();

    return 0;
}