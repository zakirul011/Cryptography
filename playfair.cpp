#include <iostream>
#include <string>
using namespace std;

// functions
string encrypt(string &plaintext, string &key);
string decrypt(string &ciphertext);
void generateKeyMatrix(string &key);
string prepareText(string &plaintext);
void findPosition(char ch, int &r, int &c);

char matrix[5][5];

// main
int main() {
    string plaintext;
    string key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter key: ";
    getline(cin, key);

    if (key.length() > 26)
    {
        cout << "Invalid key! Must be less than or equal 26 letters" << endl;
        return 1;
    }

    string ciphertext = encrypt(plaintext, key);
    string deciphertext = decrypt(ciphertext);

    cout << endl;
    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Deciphertext: " << deciphertext << endl;
}

// Encrypt
string encrypt(string &plaintext, string &key)
{
    generateKeyMatrix(key);
    string result = prepareText(plaintext);

    cout << "Pre: " << result << endl;

    string ciphertext;

    for (int i = 0, n = result.length(); i < n; i += 2)
    {
        char ch1 = result[i];
        char ch2 = result[i + 1];

        int r1, c1, r2, c2;

        findPosition(ch1, r1, c1);
        findPosition(ch2, r2, c2);

        if (r1 == r2)
        {
            ciphertext += matrix[r1][(c1 + 1) % 5];
            ciphertext += matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            ciphertext += matrix[(r1 + 1) % 5][c1];
            ciphertext += matrix[(r2 + 1) % 5][c2];
        }
        else
        {
            ciphertext += matrix[r1][c2];
            ciphertext += matrix[r2][c1];
        }
    }

    return ciphertext;
}

// Decrypt
string decrypt(string &ciphertext)
{    
    string deciphertext;

    for (int i = 0, n = ciphertext.length(); i < n; i += 2)
    {
        char ch1 = ciphertext[i];
        char ch2 = ciphertext[i + 1];

        int r1, c1, r2, c2;

        findPosition(ch1, r1, c1);
        findPosition(ch2, r2, c2);

        if (r1 == r2)
        {
            deciphertext += matrix[r1][(c1 + 4) % 5];
            deciphertext += matrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            deciphertext += matrix[(r1 + 4) % 5][c1];
            deciphertext += matrix[(r2 + 4) % 5][c2];
        }
        else
        {
            deciphertext += matrix[r1][c2];
            deciphertext += matrix[r2][c1];
        }
    }

    return deciphertext;
}


// generate key matrix
void generateKeyMatrix(string &key)
{
    // key genration
    string used;
    int k = 0;

    for (char c : key)
    {
        c = toupper(c);
        if (c == 'J')
        {
            c = 'I';
        }        

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
        {
            continue;
        }

        if (used.find(c) == string::npos)
        {
            matrix[k / 5][k % 5] = c;
            used += c;
            k++;
        }        
    }

    // print the generated key matrix
    cout << endl;
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
string prepareText(string &plaintext)
{
    string result;

    for (char c : plaintext)
    {
        if (c != ' ')
        {
            c = toupper(c);

            if (c == 'J')
            {
                c = 'I';
            }

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