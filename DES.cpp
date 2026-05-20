#include <iostream>
#include <bitset>
#include <string>
using namespace std;

// Initial Permutation Table (first few enough for demo)
int IP[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

// Expansion Permutation Table
int E[48] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

// Simple S-Box (S1 only)
int S1[4][16] = {
    {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
};

string permute(string input, int table[], int size)
{
    string output = "";

    for (int i = 0; i < size; i++)
    {
        output += input[table[i] - 1];
    }

    return output;
}

string XOR(string a, string b)
{
    string result = "";

    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == b[i])
            result += '0';
        else
            result += '1';
    }

    return result;
}

string decimalToBinary(int num)
{
    bitset<4> b(num);
    return b.to_string();
}

int main()
{
    // Example plaintext (64-bit)
    string plaintext ="0001001000110100010101100111100010011010101111001101111011110001";

    // Example round key (48-bit)
    string roundKey = "000110110000001011101111111111000111000001110010";

    cout << "Original Plaintext:\n";
    cout << plaintext << endl << endl;

    // Step 1: Initial Permutation
    string ip = permute(plaintext, IP, 64);

    cout << "After Initial Permutation:\n";
    cout << ip << endl << endl;

    // Step 2: Split into Left and Right halves
    string L = ip.substr(0, 32);
    string R = ip.substr(32, 32);

    cout << "Left Half (L):\n";
    cout << L << endl << endl;

    cout << "Right Half (R):\n";
    cout << R << endl << endl;

    // Step 3: Expansion Permutation
    string expandedR = permute(R, E, 48);

    cout << "Expanded Right Half:\n";
    cout << expandedR << endl << endl;

    // Step 4: XOR with Round Key
    string xorResult = XOR(expandedR, roundKey);

    cout << "After XOR with Round Key:\n";
    cout << xorResult << endl << endl;

    // Step 5: S-Box Substitution
    // Using only first 6 bits for demo

    string sixBits = xorResult.substr(0, 6);

    string rowBits = "";
    rowBits += sixBits[0];
    rowBits += sixBits[5];

    string colBits = sixBits.substr(1, 4);

    int row = stoi(rowBits, 0, 2);
    int col = stoi(colBits, 0, 2);

    int sboxValue = S1[row][col];

    string sboxBinary = decimalToBinary(sboxValue);

    cout << "First 6 bits for S-Box:\n";
    cout << sixBits << endl << endl;

    cout << "S-Box Output:\n";
    cout << sboxBinary << endl;

    return 0;
}