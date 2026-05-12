#include <iostream>
#include <string>
using namespace std;

string encrypt(string &plaintext, int key);
string decrypt(string &ciphertext, int key);

int main() {
    string plaintext;
    int key = 0;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
        
    while (key < 1 || key > 25)
    {
        cout << "Enter the key between 1 and 25: ";
        cin >> key;
    }

    string ciphertext = encrypt(plaintext, key);
    string decryptedtext = decrypt(ciphertext, key);

    cout << endl;
    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    cout << "Cipher text: " << ciphertext << endl;
    cout << "Decrypted text: " << decryptedtext << endl;
}

string encrypt(string &text, int key)
{
    string cipher;
    key = key % 26;

    for (char c : text)
    {
        if (isupper(c))
            cipher += ( c - 'A' + key ) % 26 + 'A';
        else if (islower(c))
            cipher += ( c - 'a' + key ) % 26 + 'a';
        else
            cipher += c;
    }

    return cipher;
}

string decrypt(string &text, int key)
{    
    return encrypt(text, 26 - key);
}