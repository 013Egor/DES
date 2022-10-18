#include "des.h"
#include "fileMaster.h"

void decipher(string keyStr);
void encrypt(string keyStr);
int getNumber(int min, int max);
void showMenu();
void menuSelection();
Mode getMode();
string getKey();

string key;
char inputType;

int main(){
    Mode encryptionType = getMode();
    key = getKey();

    menuSelection();

    if (encryptionType == encryption) {
        encrypt(key);
    } else {
        decipher(key);
    }

    menuSelection();

    return 0;
}

char getInputType() {
    string trash;
    cout << "What you want? (f - read from file, m - write message)\n";
    cout << "Input: ";

    cin >> inputType;
    while (inputType != 'f' && inputType != 'm') {
        cin.putback(inputType);
        cin >> trash;
        cout << "Tell me what you want!!! (f - read from file, m - write message)\n";
        cout << "Input: ";
        cin >> inputType;
    }

    return inputType;
}

void encrypt(string keyStr) {
    char answer = getInputType();

    FileMaster* file;
    string input;
    if (answer == 'f') {
        cout << "Enter file name: ";
        cin >> ws;
        cin >> input;
        file = new FileMaster(input, encryption);
    } else {
        cout << "Enter message: ";
        cin >> ws;
        getline(cin, input);

        ofstream outFile("message", std::ofstream::out);
        outFile << input;
        outFile.close();
        file = new FileMaster("message", encryption);
    }


    reverse(keyStr.begin(), keyStr.end());
    bitset<EXTENDED_KEY_SIZE> myKey(keyStr);

    bitset<64> origin;

    cout << '\n' << "Encrypted message: \n";
    file->printExtraBytes();
    while(file->isReadable()) {
        file->read();
        while ((origin = file->getBlock()) != NULL) {

            Des* encryptor = new Des(myKey, origin, encryption);

            bitset<64> encrypt = encryptor->run();
            file->setBlock(encrypt);
            file->saveEncrypted(inputType == 'm');
        }

    }
    cout << '\n' << endl;
    delete file;
}

void decipher(string keyStr) {
    char answer = getInputType();

    FileMaster* file;
    string input;
    if (answer == 'f') {
        cout << "Enter file name: ";
        cin >> ws;
        cin >> input;
        file = new FileMaster(input, decryption);
    } else {
        cout << "Enter message: ";
        cin >> ws >> input;
        ofstream outFile("message", std::ofstream::out);
        outFile << input;
        outFile.close();
        file = new FileMaster("message_output.des", decryption);
    }

    reverse(keyStr.begin(), keyStr.end());
    bitset<EXTENDED_KEY_SIZE> myKey(keyStr);

    bitset<64> encrypt;

    cout << '\n' << "Deciphered message: \n";
    while(file->isReadable()) {

        file->read();

        while ((encrypt = file->getBlock()) != NULL) {

            Des* decryptor = new Des(myKey, encrypt, decryption);

            bitset<64> origin = decryptor->run();
            file->setBlock(origin);
            file->save(inputType == 'm');
        }

    }
    cout << '\n' << endl;
    delete file;
}



string getKey() {
    char answer;
    string trash;
    cout << "You want use default key or custom key? (n - now, y - yes)\n";
    cout << "Input: ";

    cin >> answer;
    while (answer != 'y' && answer != 'n') {
        cin.putback(answer);
        cin >> trash;
        cout << "Tell me what you want!!! (n - now, y - yes)\n";
        cout << "Input: ";
        cin >> answer;
    }
    string keyStr("0001001100110100010101110111100110011011101111001101111111110001");

    if (answer == 'y') {
        cout << "Enter key: ";
        cin >> keyStr;
        bool isKeyCorrect = true;
        for (const auto &item: keyStr) {
            if (item != '0' && item != '1') {
                isKeyCorrect = false;
            }
        }
        while (keyStr.length() != 64  || isKeyCorrect == false) {
            cin.putback(answer);
            cin >> trash;
            cout << "Enter valid key!!!\n";
            cout << "Enter key: ";
            cin >> keyStr;
            isKeyCorrect = true;
            for (const auto &item: keyStr) {
                if (item != '0' && item != '1') {
                    isKeyCorrect = false;
                }
            }
        }
    }

    return keyStr;
}

Mode getMode() {
    char answer;
    string trash;
    cout << "What you want? (e - encrypt, d - decipher)\n";
    cout << "Input: ";

    cin >> answer;
    while (answer != 'e' && answer != 'd') {
        cin.putback(answer);
        cin >> trash;
        cout << "Tell me what you want!!! (e - encrypt, d - decipher)\n";
        cout << "Input: ";
        cin >> answer;
    }
    return answer == 'e' ? encryption : decryption;
}

void menuSelection() {
    int numMenu;
    string input;
    while (true) {
        showMenu();
        numMenu = getNumber(0, 17);

        if (numMenu == 1) {
            Des::showPC_1();
        } else if (numMenu == 2) {
            Des::showPC_2();
        } else if (numMenu == 3) {
            Des::showIP();
        } else if (numMenu == 4) {
            Des::showE();
        } else if (numMenu == 5) {
            Des::showP();
        } else if (numMenu == 6) {
            Des::showIP_r();
        } else if (numMenu == 7) {
            cout << "Enter s-box number (from 0 to 7)";
            int id = getNumber(0,S_BOX_NUMBER);
            Des::showS_box(id);
        } else if (numMenu == 8) {
            cout << "Key: " << key << endl;
        } else if (numMenu == 9) {
            cout << "Enter row of table (from 0 to " << PC1_ROWS << ")";
            int row = getNumber(0, PC1_ROWS);
            cout << "Enter row of table (from 0 to " << PC1_COLUMNS << ")";
            int column = getNumber(0, PC1_COLUMNS);
            cout << "Enter value (from 1 to 64)";
            int value = getNumber(1, 65);
            Des::changePC_1(row, column, value);
        } else if (numMenu == 10) {
            cout << "Enter row of table (from 0 to " << PC2_ROWS << ")";
            int row = getNumber(0, PC2_ROWS);
            cout << "Enter row of table (from 0 to " << PC2_COLUMNS << ")";
            int column = getNumber(0, PC2_COLUMNS);
            cout << "Enter value (from 1 to 64)";
            int value = getNumber(1, 65);
            Des::changePC_2(row, column, value);
        } else if (numMenu == 11) {
            cout << "Enter row of table (from 0 to " << IP_ROWS << ")";
            int row = getNumber(0, IP_ROWS);
            cout << "Enter row of table (from 0 to " << IP_COLUMNS << ")";
            int column = getNumber(0, IP_COLUMNS);
            cout << "Enter value (from 1 to 64)";
            int value = getNumber(1, 65);
            Des::changeIP(row, column, value);
        } else if (numMenu == 12) {
            cout << "Enter row of table (from 0 to " << E_ROWS << ")";
            int row = getNumber(0, E_ROWS);
            cout << "Enter row of table (from 0 to " << E_COLUMNS << ")";
            int column = getNumber(0, E_COLUMNS);
            cout << "Enter value (from 1 to 32)";
            int value = getNumber(1, 33);
            Des::changeE(row, column, value);
        } else if (numMenu == 13) {
            cout << "Enter row of table (from 0 to " << P_ROWS << ")";
            int row = getNumber(0, P_ROWS);
            cout << "Enter row of table (from 0 to " << P_COLUMNS << ")";
            int column = getNumber(0, P_COLUMNS);
            cout << "Enter value (from 1 to 32)";
            int value = getNumber(1, 33);
            Des::changeP(row, column, value);
        } else if (numMenu == 14) {
            cout << "Enter row of table (from 0 to " << IP_ROWS << ")";
            int row = getNumber(0, IP_ROWS);
            cout << "Enter row of table (from 0 to " << IP_COLUMNS << ")";
            int column = getNumber(0, IP_COLUMNS);
            cout << "Enter value (from 1 to 64)";
            int value = getNumber(1, 64);
            Des::changeIP_r(row, column, value);
        } else if (numMenu == 15) {
            cout << "Enter s-box number (from 0 to 7)";
            int id = getNumber(0,S_BOX_NUMBER);
            cout << "Enter row of table (from 0 to " << S_BOX_ROWS << ")";
            int row = getNumber(0, S_BOX_ROWS);
            cout << "Enter row of table (from 0 to " << S_BOX_COLUMNS << ")";
            int column = getNumber(0, S_BOX_COLUMNS);
            cout << "Enter value (from 1 to 16)";
            int value = getNumber(1, 17);
            Des::changeS_box(id, row, column, value);
        } else if (numMenu == 16) {
            cout << "Enter number of rounds (from 0 to " << MAX_ROUNDS << "):";
            int rounds = getNumber(0,MAX_ROUNDS);
            Des::changeROUNDS(rounds);
        } else if (numMenu == 0) {
            break;
        }
    }
}

void showMenu() {
    cout << "---------------------------------------\n";
    cout << "|                Menu:                |\n";
    cout << "---------------------------------------\n";
    cout << "| 1) Show PC-1 table                  |\n";
    cout << "| 2) Show PC-2 table                  |\n";
    cout << "| 3) Show IP table                    |\n";
    cout << "| 4) Show E table                     |\n";
    cout << "| 5) Show P table                     |\n";
    cout << "| 6) Show IP~ table                   |\n";
    cout << "| 7) Show S table                     |\n";
    cout << "| 8) Show KEY                         |\n";
    cout << "| 9) Change PC-1 table                |\n";
    cout << "| 10) Change PC-2 table               |\n";
    cout << "| 11) Change IP table                 |\n";
    cout << "| 12) Change E table                  |\n";
    cout << "| 13) Change P table                  |\n";
    cout << "| 14) Change IP~ table                |\n";
    cout << "| 15) Change S-box                    |\n";
    cout << "| 16) Change rounds                   |\n";
    cout << "| 0) Continue                         |\n";
    cout << "---------------------------------------\n";
}

int getNumber(int min, int max) {
    int num;
    string input;
    bool isChoiceIncorrect = true;
    while (isChoiceIncorrect) {
        try {
            cout << "\nYour choice: ";
            cin >> ws;
            cin >> input;
            num = stoi(input);

            isChoiceIncorrect = num >= 0 && num < max ? false : true;
            if (isChoiceIncorrect) {
                cout << "Number must be from 0 to " << max << ".\nTry again.\n";
            }
        } catch(invalid_argument const& ex)
        {
            cout << "That's not a number young man :|\nTry again.";
        }
    }

    return num;
}