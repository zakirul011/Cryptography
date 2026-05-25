#include <iostream>
#include <cstdint>
using namespace std;

// multiplication
uint8_t gfMul(uint8_t a, uint8_t b)
{
    uint8_t result = 0;

    while (b)
    {
        if (b & 1)
            result ^= a;

        bool hiBitSet = a & 0x80;
        a <<= 1;

        if (hiBitSet)
            a ^= 0x1B;

        b >>= 1;
    }

    return result;
}

// Multiplicative inverse
uint8_t gfInverse(uint8_t x)
{
    if (x == 0) return 0;

    for (int i = 1; i < 256; i++)
    {
        if (gfMul(x, i) == 1)
            return i;
    }

    return 0;
}

// AES affine transformation
uint8_t affineTransform(uint8_t x)
{
    uint8_t result = 0;
    uint8_t c = 0x63;

    for (int i = 0; i < 8; i++)
    {
        uint8_t bit = (x >> i) & 1;

        uint8_t transformedBit =
            bit ^
            ((x >> ((i + 4) % 8)) & 1) ^
            ((x >> ((i + 5) % 8)) & 1) ^
            ((x >> ((i + 6) % 8)) & 1) ^
            ((x >> ((i + 7) % 8)) & 1) ^
            ((c >> i) & 1);

        result |= (transformedBit << i);
    }

    return result;
}

int main()
{
    string hexInput;
    cout << "Enter byte in hex: ";
    cin >> hexInput;

    // Convert hex string to integer
    uint8_t input = (uint8_t)stoi(hexInput, nullptr, 16);

    // multiplicative inverse
    uint8_t inv = gfInverse(input);

    // affine transformation
    uint8_t sboxValue = affineTransform(inv);

    // Output
    cout << "AES S-Box value = 0x"
         << hex
         << uppercase
         << (int)sboxValue
         << endl;

    return 0;
}