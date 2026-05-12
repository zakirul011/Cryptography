#include <iostream>
#include <string>
using namespace std;

string encrypt(string &plaintext, int key);
string decrypt(string &ciphertext, int key);
void bruteforce(string &ciphertext);

int main() {
    string ciphertext;

    cout << "Enter the Ciphertext: ";
    getline(cin, ciphertext);

    bruteforce(ciphertext);
}


void bruteforce(string &ciphertext)
{   
    int key = 1;

    while (key < 26)
    {
        cout << "For key " << key << ", plaintext: " << decrypt(ciphertext, key) << endl;
        key++;
    }
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