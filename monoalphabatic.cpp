#include <iostream>
#include <string>
using namespace std;

string encrypt(string &plaintext, string &key);
string decrypt(string &ciphertext, string &key);

int main() {
    string plaintext;
    string key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter key: ";
    getline(cin, key); // QWERTYUIOPASDFGHJKLZXCVBNM

    if (key.length() != 26)
    {
        cout << "Invalid key! Must be 26 letters" << endl;
        return 1;
    }

    string ciphertext = encrypt(plaintext, key);
    string deciphertext = decrypt(ciphertext, key);

    cout << endl;
    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Deciphertext: " << deciphertext << endl;
}

string encrypt(string &plaintext, string &key)
{
    string ciphertext;    
    
    for (char ch : plaintext)
    {
        if (isupper(ch))
        {
            ciphertext += toupper(key[ch - 'A']);
        }
        else if (islower(ch))
        {
            ciphertext += tolower(key[ch - 'a']);
        }
        else
        {
            ciphertext += ch;
        }
    }

    return ciphertext;
}

string decrypt(string &ciphertext, string &key)
{    
    string deciphertext;

    for (char ch : ciphertext)
    {
        for (int i = 0; i < 26; i++)
        {
            if (toupper(ch) == key[i])
            {

                if (isupper(ch))
                {
                    deciphertext += char(i + 'A');
                }
                else if (islower(ch))
                {
                    deciphertext += char(i + 'a');
                }
                else
                {
                    deciphertext += ch;
                }

                break;

            }
        }
    }

    return deciphertext;
}