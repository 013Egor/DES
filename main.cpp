#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include <string>

#include "des.h"
#include "fileMaster.h"

using namespace std;

// Convert string of chars to its representative string of hex numbers
void stream2hex(const std::string str, std::string& hexstr, bool capital = false)
{
    hexstr.resize(str.size() * 2);
    const size_t a = capital ? 'A' - 1 : 'a' - 1;

    for (size_t i = 0, c = str[0] & 0xFF; i < hexstr.size(); c = str[i / 2] & 0xFF)
    {
        hexstr[i++] = c > 0x9F ? (c / 16 - 9) | a : c / 16 | '0';
        hexstr[i++] = (c & 0xF) > 9 ? (c % 16 - 9) | a : c % 16 | '0';
    }
}

// Convert string of hex numbers to its equivalent char-stream
void hex2stream(const std::string hexstr, std::string& str)
{
    str.resize((hexstr.size() + 1) / 2);

    for (size_t i = 0, j = 0; i < str.size(); i++, j++)
    {
        str[i] = (hexstr[j] & '@' ? hexstr[j] + 9 : hexstr[j]) << 4, j++;
        str[i] |= (hexstr[j] & '@' ? hexstr[j] + 9 : hexstr[j]) & 0xF;
    }
}
const char* hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

std::string hex_str_to_bin_str(const std::string& hex)
{
    // TODO use a loop from <algorithm> or smth
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
       bin += hex_char_to_bin(hex[i]);
    return bin;
}

int main(){
    string keyStr("0001001100110100010101110111100110011011101111001101111111110001");
    reverse(keyStr.begin(), keyStr.end());
    
    

    bitset<EXTENDED_KEY_SIZE> myKey(keyStr);

    cout << "testKey: 0001001100110100010101110111100110011011101111001101111111110001 <---> " << myKey.to_string() << "\n" << endl;
    
    Des* d = new Des(myKey, encryption);
    //ввести из консоли в переменную str
    m:
    cout << "text (8 symbols) ---> " << endl;
    string text;
    cin >> text;
    if(text.size() != 8){
        cout << "error" << "\n\n";
        goto m;
    }
    
    stream2hex(text, text);
    string messageStr = hex_str_to_bin_str(text);

    cout << messageStr.size();
    //reverse(messageStr.begin(), messageStr.end());
    bitset<MESSAGE_SIZE> res = d->testMessage(messageStr);
    string strResult = res.to_string();
    Des* e = new Des(myKey, decryption);
    bitset<MESSAGE_SIZE> res1 = d->testMessage(strResult);
    cout << "result: " << res1.to_string();

}