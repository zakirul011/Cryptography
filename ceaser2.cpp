#include <iostream>
#include <string>
using namespace std;

string encrypt(string &plaintext, int key)
{
    string ciphertext;

    for (int i = 0; i < plaintext.length(); i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            ciphertext += (c - 'A' + key) % 26 + 'A';
        }
        else if (islower(c))
        {           
            ciphertext += (c - 'a' + key) % 26 + 'a';
        }
        else
        {
            ciphertext += c;
        }
    }

    return ciphertext;
}

string decrypt(string &ciphertext, int key)
{
    return encrypt(ciphertext, 26 - key);
}



int main()
{

    string plaintext;
    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    int key;
    cout << "Enter key: ";
    cin >> key;

    string ciphertext = encrypt(plaintext, key);
    string deciphertext = decrypt(ciphertext, key);

    cout << ciphertext << endl;
    cout << deciphertext << endl;
}