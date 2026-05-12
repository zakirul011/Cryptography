#include <iostream>
#include <string>
using namespace std;

string encrypt(string &text, string &key)
{
    string cipher = text;      
      
    for (char &ch : cipher)
    {
        if (isupper(ch))
            ch = toupper(key[ch - 'A']);
        else if (islower(ch))
            ch = tolower(key[ch - 'a']);
    }

    return cipher;
}

string decrypt(string &cipher, string &key)
{    
    string decipher = cipher;

    for (char &ch : decipher)
    {
        if (toupper(ch) >= 'A' && toupper(ch) <= 'Z')
        {
            for (int i = 0; i < 26; i++)
            {
                if (toupper(ch) == key[i])
                {
                    if (isupper(ch))
                        ch = char(i + 'A'); 
                    else               
                        ch = char(i + 'a'); 
                    break;
                }
            }
        }
    }

    return decipher;
}

int main() {
    string plain, key;

    cout << "Enter plaintext: ";
    getline(cin, plain);

    cout << "Enter key: ";
    getline(cin, key); // TVDRQYUMOPASEFGHJKLZXCWBNI

    if (key.length() != 26)
    {
        cout << "Key Must be 26 letters!!" << endl;
        return 1;
    }

    string cipher = encrypt(plain, key);
    string decipher = decrypt(cipher, key);

    cout << endl;
    cout << "Plaintext: " << plain << endl;
    cout << "Key: " << key << endl;
    cout << "Ciphertext: " << cipher << endl;
    cout << "Deciphertext: " << decipher << endl;
}
