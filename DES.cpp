#include <iostream>
#include <bitset>
using namespace std;

// Initial Permutation Table (IP)
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

bitset<64> initialPermutation(bitset<64> &input)
{
    bitset<64> output;

    for (int i = 0; i < 64; i++)
    {
        output[63 - i] = input[64 - IP[i]];
    }

    return output;
}


int main(void)
{
    bitset<64> plaintext(
        "0001001000110100010101100111100010011010101111001101111011110001"
    );

    bitset<64> output = initialPermutation(plaintext);

    cout << output;
}