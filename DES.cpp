#include <iostream>
#include <bitset>
using namespace std;

// IP
int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// E-box
int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// One S-box
int S1[4][16] = {
    {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
};

// P-box
int P[32] = {
    16,7,20,21,
    29,12,28,17,
    1,15,23,26,
    5,18,31,10,
    2,8,24,14,
    32,27,3,9,
    19,13,30,6,
    22,11,4,25
};

// Initial Permutation
bitset<64> initialPermutation(bitset<64> input)
{
    bitset<64> output;

    for (int i = 0; i < 64; i++)
    {
        output[63 - i] = input[64 - IP[i]];
    }

    return output;
}

// Expansion Permutation
bitset<48> expansion(bitset<32> R)
{
    bitset<48> res;

    for (int i = 0; i < 48; i++)
    {
        res[47 - i] = R[32 - E[i]];
    }

    return res;
}

// S-box substitution
bitset<32> sboxSubstitution(bitset<48> input)
{
    bitset<32> output;

    for (int i = 0; i < 8; i++)
    {
        int row =
            input[47 - (i * 6)] * 2 +
            input[47 - (i * 6 + 5)];

        int col = 0;

        for (int j = 1; j <= 4; j++)
        {
            col = col * 2 +
                  input[47 - (i * 6 + j)];
        }

        int val = S1[row][col];

        for (int j = 0; j < 4; j++)
        {
            output[31 - (i * 4 + j)] =
                (val >> (3 - j)) & 1;
        }
    }

    return output;
}

// P-box permutation
bitset<32> permutation(bitset<32> input)
{
    bitset<32> output;

    for (int i = 0; i < 32; i++)
    {
        output[31 - i] = input[32 - P[i]];
    }

    return output;
}

int main()
{
    // 64-bit plaintext
    bitset<64> plaintext(
        "0001001000110100010101100111100010011010101111001101111011110001"
    );

    // 48-bit round key
    bitset<48> subkey(
        "000110110000001011101111111111000111000001110010"
    );

    cout << "Original Plaintext:\n"
         << plaintext << endl;


    // Initial Permutation
    bitset<64> IP_output = initialPermutation(plaintext);

    cout << "\nAfter Initial Permutation:\n"
         << IP_output << endl;

    // Split into L and R
    bitset<32> L, R;

    for (int i = 0; i < 32; i++)
    {
        L[31 - i] = IP_output[63 - i];
        R[31 - i] = IP_output[31 - i];
    }

    cout << "\nLeft Half:\n"
         << L << endl;

    cout << "\nRight Half:\n"
         << R << endl;

    // Expansion Permutation
    bitset<48> R_expanded = expansion(R);

    cout << "\nExpanded R:\n"
         << R_expanded << endl;

    // XOR with Round Key
    bitset<48> R_xor_key = R_expanded ^ subkey;

    cout << "\nAfter XOR with Round Key:\n"
         << R_xor_key << endl;

    // S-box Substitution
    bitset<32> S_output = sboxSubstitution(R_xor_key);

    cout << "\nAfter S-box Substitution:\n"
         << S_output << endl;

    // P-box Permutation
    bitset<32> P_output = permutation(S_output);

    cout << "\nAfter P-box Permutation:\n"
         << P_output << endl;
         
    // Final Round Result
    bitset<32> newR = L ^ P_output;
    bitset<32> newL = R;

    cout << "\nNew Left:\n"
         << newL << endl;

    cout << "\nNew Right:\n"
         << newR << endl;
}