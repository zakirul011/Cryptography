#include <iostream>
#include <string>
using namespace std;

// functions prototypes
string generate_cipher(string &plaintext, string &key);
string generate_decipher(string &ciphertext);
void generate_key_matrix(string &key);
string text_preparation(string &plaintext);
void findPosition(char ch, int &r, int &c);

char matrix[5][5];

// main function
int main() {
    string plaintext, key;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    cout << "Enter the key: ";
    getline(cin, key);

    if (key.length() > 26)
    {
        cout << "Key must not be greater than 26 letters" << endl;
        return 1;
    }

    string cipher = generate_cipher(plaintext, key);
    string deccipher = generate_decipher(cipher);

    cout << endl;
    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    cout << "Ciphertext: " << cipher << endl;
    cout << "Deciphertext: " << deccipher << endl;
}

// generate_cipher
string generate_cipher(string &plaintext, string &key)
{
    generate_key_matrix(key);
    string result = text_preparation(plaintext);

    cout << "Prepared plaintext: " << result << endl;

    string cipher;

    for (int i = 0, n = result.length(); i < n; i += 2)
    {
        char ch1 = result[i];
        char ch2 = result[i + 1];

        int r1, c1, r2, c2;

        findPosition(ch1, r1, c1);
        findPosition(ch2, r2, c2);

        if (r1 == r2)
        {
            cipher += matrix[r1][(c1 + 1) % 5];
            cipher += matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            cipher += matrix[(r1 + 1) % 5][c1];
            cipher += matrix[(r2 + 1) % 5][c2];
        }
        else
        {
            cipher += matrix[r1][c2];
            cipher += matrix[r2][c1];
        }
    }

    return cipher;
}

// generate_decipher
string generate_decipher(string &ciphertext)
{    
    string decipher;

    for (int i = 0, n = ciphertext.length(); i < n; i += 2)
    {
        char ch1 = ciphertext[i];
        char ch2 = ciphertext[i + 1];

        int r1, c1, r2, c2;

        findPosition(ch1, r1, c1);
        findPosition(ch2, r2, c2);

        if (r1 == r2)
        {
            decipher += matrix[r1][(c1 + 4) % 5];
            decipher += matrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            decipher += matrix[(r1 + 4) % 5][c1];
            decipher += matrix[(r2 + 4) % 5][c2];
        }
        else
        {
            decipher += matrix[r1][c2];
            decipher += matrix[r2][c1];
        }
    }

    return decipher;
}


// generate key matrix
void generate_key_matrix(string &key)
{
    // key genration
    string used;
    int k = 0;

    for (char c : key)
    {
        c = toupper(c);
        if (c == 'J')
            c = 'I';

        if (used.find(c) == string::npos)
        {
            matrix[k / 5][k % 5] = c;
            used += c;
            k++;
        }
    }

    for (char c = 'A'; c >= 'A' && c <= 'Z'; c++)
    {
        if (c == 'J')
            continue;

        if (used.find(c) == string::npos)
        {
            matrix[k / 5][k % 5] = c;
            used += c;
            k++;
        }        
    }

    // print the generated key matrix
    cout << "\nGenerated key matrix" << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// plain text preparation
string text_preparation(string &plaintext)
{
    string result;

    for (char c : plaintext)
    {
        if (c != ' ')
        {
            c = toupper(c);

            if (c == 'J')
                c = 'I';

            result += c;
        }

    }

    for (int i = 0, n = result.length(); i < n; i += 2)
    {
        if (i + 1 == n)
        {
            result += 'X';
            break;
        }

        if (result[i] == result[i + 1])
        {
            result.insert(i + 1, 1, 'X');
            n++;
        }
    }

    return result;
}


// find position of the charecter in matrix
void findPosition(char ch, int &r, int &c)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                r = i;
                c = j;
                break;
            }
        }
    }
}