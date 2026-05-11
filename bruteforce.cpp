#include <iostream>
#include <string>
using namespace std;

string encrypt(string &plaintext, int key);
string decrypt(string &ciphertext, int key);
void bruteforce(string &ciphertext);

int main() {
    string ciphertext;

    cout << "Enter Ciphertext: ";
    getline(cin, ciphertext);

    bruteforce(ciphertext);
}


void bruteforce(string &ciphertext)
{   
    int key = 1;

    while (key < 26)
    {
        cout << "key " << key << ": " << decrypt(ciphertext, key) << endl;
        key++;
    }
}

string encrypt(string &plaintext, int key)
{
    key = key % 26;

    string ciphertext;

    for (char ch : plaintext)
    {
        if (isupper(ch))
        {
            ciphertext += ( ch - 'A' + key ) % 26 + 'A';
        }
        else if (islower(ch))
        {
            ciphertext += ( ch - 'a' + key ) % 26 + 'a';
        }
        else
        {
            ciphertext += ch;
        }
    }

    return ciphertext;
}

string decrypt(string &ciphertext, int key)
{    
    return encrypt(ciphertext, 26 - key);
}